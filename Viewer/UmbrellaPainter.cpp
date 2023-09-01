#include "UmbrellaPainter.h"

UmbrellaPainter::UmbrellaPainter(WorldPresenter& _worldPresenter):
	worldPresenter(_worldPresenter),
	paintRect(),
	memoryDC(),
	bitmap0(0), 
	bitmap1(0),
	frontIndex(0),
	width(0), 
	height(0),
	worldLightBrush(CreateSolidBrush(RGB(8, 8, 8))),
	pitBrush(CreateSolidBrush(RGB(8, 8, 128))),
	appleBrush(CreateSolidBrush(RGB(8, 128, 8))),
	agentBrush(CreateSolidBrush(RGB(128, 8, 8)))
{

}

UmbrellaPainter::~UmbrellaPainter()
{
	DeleteObject(worldLightBrush);
}

void UmbrellaPainter::initialize(HWND windowHandle)
{
	HDC dc = GetDC(windowHandle);

	RECT rect;
	GetClientRect(windowHandle, &rect);

	paintRect.left = rect.left;
	paintRect.right = rect.right;
	paintRect.top = rect.top;
	paintRect.bottom = rect.bottom;

	width = rect.right - rect.left;
	height = rect.bottom - rect.top;

	memoryDC[0] = CreateCompatibleDC(dc);
	memoryDC[1] = CreateCompatibleDC(dc);
	bitmap0 = CreateCompatibleBitmap(dc, width, height);
	bitmap1 = CreateCompatibleBitmap(dc, width, height);

	ReleaseDC(windowHandle, dc);

	SelectObject(memoryDC[0], bitmap0);
	SelectObject(memoryDC[1], bitmap1);

	SetBkMode(memoryDC[0], TRANSPARENT);
	SetBkMode(memoryDC[1], TRANSPARENT);

	SetTextColor(memoryDC[0], RGB(200, 200, 200));
	SetTextColor(memoryDC[1], RGB(200, 200, 200));
}

void UmbrellaPainter::paint(HDC destinationDC)
{
	int index = (frontIndex.load() + 1) % 2;
	HDC dc = memoryDC[index];

	BitBlt(destinationDC, 0, 0, width, height, dc, 0, 0, SRCCOPY);
}

void UmbrellaPainter::drawCell(HDC dc, int x, int y, HBRUSH brush)
{
	RECT r
	{
		.left = x * cellSize,
		.top = y * cellSize,
		.right = x * cellSize + cellSize,
		.bottom = y * cellSize + cellSize
	};
	FillRect(dc, &r, brush);
}

std::wstring toString(double d)
{
	std::ostringstream stream;

	stream << std::fixed;

	stream << std::setprecision(4);

	stream << d;

	std::string string = stream.str();

	return std::wstring(string.begin(), string.end());
}

void UmbrellaPainter::drawCellQFunction(HDC dc, int x, int y, QTableCell qTableCell)
{
	std::wstring 
		lQValue(L"L: " + toString(qTableCell.left)),
		rQValue(L"R: " + toString(qTableCell.right)),
		tQValue(L"T: " + toString(qTableCell.top)),
		bQValue(L"B: " + toString(qTableCell.bottom));

	int left = x * cellSize + 8,
		top = y * cellSize + 4;

	TextOut(dc, left, top, lQValue.c_str(), lQValue.length());
	top += 14;
	TextOut(dc, left, top, rQValue.c_str(), rQValue.length());
	top += 14;
	TextOut(dc, left, top, tQValue.c_str(), tQValue.length());
	top += 14;
	TextOut(dc, left, top, bQValue.c_str(), bQValue.length());
}

void UmbrellaPainter::draw()
{
	int index = frontIndex.load() % 2;
	HDC dc = memoryDC[index];

	drawField(dc);
	drawWorldInitialState(dc);

	drawCurrentState(dc);

	for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 10; y++)
		{
			QTableCell qTableCell = worldPresenter.getQFunction(x, y);

			if (qTableCell.calculated)
			{
				drawCellQFunction(dc, x, y, qTableCell);
			}
		}
	}

	frontIndex.fetch_add(1);
}

void UmbrellaPainter::drawField(HDC dc)
{
	FillRect(dc, &paintRect, (HBRUSH)GetStockObject(BLACK_BRUSH));

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if ((i + j) % 2 == 0)
			{
				drawCell(dc, i, j, worldLightBrush);
			}
		}
	}
}

void UmbrellaPainter::drawWorldInitialState(HDC dc)
{
	WorldInitialState worldInitialState = worldPresenter.getWorldInitialState();

	for (auto cell = worldInitialState.pit.cells.begin(); cell != worldInitialState.pit.cells.end(); cell++)
	{
		drawCell(dc, cell->x, cell->y, pitBrush);
	}

	Apple& apple(worldInitialState.apple);

	drawCell(dc, apple.x, apple.y, appleBrush);
}

void UmbrellaPainter::drawCurrentState(HDC dc)
{
	AgentState agentState = worldPresenter.getCurrentAgentState();

	drawCell(dc, agentState.x, agentState.y, agentBrush);
}