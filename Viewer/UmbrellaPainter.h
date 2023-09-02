#pragma once

#include <Windows.h>
#include <atomic>

#include "../modMessageBusClient/WorldInitialState.h"
#include "../modMessageBusClient/MessageBusClient.h"
#include "WorldPresenter.h"

class UmbrellaPainter
{
private:

	static const int cellSize = 80;

	WorldPresenter& worldPresenter;

	RECT 
		paintRect,
		consoleRect;

	HDC memoryDC[2];
	HBITMAP bitmap0, bitmap1;

	std::atomic<int> frontIndex;

	int width, height;

	HBRUSH 
		worldLightBrush,
		pitBrush,
		appleBrush,
		startPositionBrush,
		agentBrush,
		consoleBrush;

	void drawCell(HDC dc, int x, int y, HBRUSH brush);

	void drawCellQFunction(HDC dc, int x, int y, QTableCell qTableCell);

	void drawAccumulatedReward(HDC dc, int x, int y, double accumulatedReward);

	void drawField(HDC dc);

	void drawWorldInitialState(HDC dc);

	void drawCurrentState(HDC dc);

	void drawConsole(HDC dc);

public:

	UmbrellaPainter(WorldPresenter& _worldPresenter);
	~UmbrellaPainter();

	void initialize(HWND windowHandle);

	void paint(HDC destinationDC);

	void draw();
};