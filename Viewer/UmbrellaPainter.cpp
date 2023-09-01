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
	appleBrush(CreateSolidBrush(RGB(8, 128, 8)))
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

void UmbrellaPainter::draw()
{
	int index = frontIndex.load() % 2;
	HDC dc = memoryDC[index];

	drawField(dc);
	drawWorldInitialState(dc);

	frontIndex.fetch_add(1);
}

void UmbrellaPainter::drawField(HDC dc)
{
	FillRect(dc, &paintRect, (HBRUSH)GetStockObject(BLACK_BRUSH));

	for (int i = 0; i < 10; i++)
	{
		int x = i * 80;

		for (int j = 0; j < 10; j++)
		{
			int y = j * 80;

			if ((i + j) % 2 == 0)
			{
				RECT r
				{
					.left = x,
					.top = y,
					.right = x + 80,
					.bottom = y + 80
				};
				FillRect(dc, &r, worldLightBrush);
			}
		}
	}
}

void UmbrellaPainter::drawWorldInitialState(HDC dc)
{
	WorldInitialState worldInitialState = worldPresenter.getWorldInitialState();

	for (auto cell = worldInitialState.pit.cells.begin(); cell != worldInitialState.pit.cells.end(); cell++)
	{
		int x = cell->x * 80,
			y = cell->y * 80;

		RECT r
		{
			.left = x,
			.top = y,
			.right = x + 80,
			.bottom = y + 80
		};
		FillRect(dc, &r, pitBrush);
	}

	Apple& apple(worldInitialState.apple);

	int x = apple.x * 80,
		y = apple.y * 80;

	RECT r
	{
		.left = x,
		.top = y,
		.right = x + 80,
		.bottom = y + 80
	};
	FillRect(dc, &r, appleBrush);
}