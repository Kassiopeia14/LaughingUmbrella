#include "UmbrellaPainter.h"

UmbrellaPainter::UmbrellaPainter(WorldPresenter& _worldPresenter):
	worldPresenter(_worldPresenter),
	paintRect(),
	consoleRect(),
	memoryDC(),
	bitmap0(0), 
	bitmap1(0),
	frontIndex(0),
	width(0), 
	height(0),
	worldLightBrush(CreateSolidBrush(RGB(8, 8, 8))),
	pitBrush(CreateSolidBrush(RGB(8, 8, 128))),
	appleBrush(CreateSolidBrush(RGB(8, 128, 8))),
	agentBrush(CreateSolidBrush(RGB(128, 8, 8))),
	consoleBrush(CreateSolidBrush(RGB(0, 0, 32)))
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
	
	paintRect.left = rect.left;
	paintRect.right = rect.left + 80 * 10;
	paintRect.top = rect.top;
	paintRect.bottom = rect.top + 80 * 10;

	consoleRect.left = paintRect.right;
	consoleRect.right = width;
	consoleRect.top = rect.top;
	consoleRect.bottom = height;
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

	SetTextColor(dc, RGB(200, 200, 200));

	TextOut(dc, left, top, lQValue.c_str(), lQValue.length());
	top += 14;
	TextOut(dc, left, top, rQValue.c_str(), rQValue.length());
	top += 14;
	TextOut(dc, left, top, tQValue.c_str(), tQValue.length());
	top += 14;
	TextOut(dc, left, top, bQValue.c_str(), bQValue.length());
}

void UmbrellaPainter::drawAccumulatedReward(HDC dc, int x, int y, double accumulatedReward)
{
	std::wstring accumulatedRewardValue(toString(accumulatedReward));

	int left = x * cellSize + 16,
		top = y * cellSize + 6 + 4*14;

	SetTextColor(dc, RGB(250, 200, 0));

	TextOut(dc, left, top, accumulatedRewardValue.c_str(), accumulatedRewardValue.length());
}

void UmbrellaPainter::drawConsole(HDC dc)
{
	FillRect(dc, &consoleRect, consoleBrush);

	AgentState agentState = worldPresenter.getCurrentAgentState();

	std::wstring 
		epochNumberValue(L"Epoch " + std::to_wstring(worldPresenter.getEpochNumber())),
		stepNumberValue(L"Step " + std::to_wstring(worldPresenter.getStepNumber())),
		accumulatedRewardValue(L"Accumulated Reward " + toString(agentState.accumulatedReward));

	int left = consoleRect.left + 16,
		top = consoleRect.top + 16;

	SetTextColor(dc, RGB(51, 255, 255));

	TextOut(dc, left, top, epochNumberValue.c_str(), epochNumberValue.length());

	top += 14;
	TextOut(dc, left, top, stepNumberValue.c_str(), stepNumberValue.length());

	top += 14;
	TextOut(dc, left, top, accumulatedRewardValue.c_str(), accumulatedRewardValue.length());
}

void UmbrellaPainter::draw()
{
	int index = frontIndex.load() % 2;
	HDC dc = memoryDC[index];

	drawField(dc);
	drawConsole(dc);

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

	drawAccumulatedReward(dc, agentState.x, agentState.y, agentState.accumulatedReward);
}