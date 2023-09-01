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
	SelectObject(memoryDC[0], bitmap0);
	SelectObject(memoryDC[1], bitmap1);

	ReleaseDC(windowHandle, dc);
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
		.left = x * 80,
		.top = y * 80,
		.right = x * 80 + 80,
		.bottom = y * 80 + 80
	};
	FillRect(dc, &r, brush);
}

void UmbrellaPainter::draw()
{
	int index = frontIndex.load() % 2;
	HDC dc = memoryDC[index];

	drawField(dc);
	drawWorldInitialState(dc);

	drawCurrentState(dc);

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