#pragma once

#include <Windows.h>
#include <atomic>

#include "../modMessageBusClient/WorldInitialState.h"
#include "../modMessageBusClient/MessageBusClient.h"
#include "WorldPresenter.h"

class UmbrellaPainter
{
private:

	WorldPresenter& worldPresenter;

	RECT paintRect;

	HDC memoryDC[2];
	HBITMAP bitmap0, bitmap1;

	std::atomic<int> frontIndex;

	int width, height;

	HBRUSH 
		worldLightBrush,
		pitBrush,
		appleBrush;

	void drawField(HDC dc);

	void drawWorldInitialState(HDC dc);

public:

	UmbrellaPainter(WorldPresenter& _worldPresenter);
	~UmbrellaPainter();

	void initialize(HWND windowHandle);

	void paint(HDC destinationDC);

	void draw();
};