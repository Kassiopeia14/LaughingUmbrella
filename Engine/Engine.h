#pragma once

#include <random>
#include <list>

#include "../modMessageBusClient/Epoch.h"
#include "../modMessageBusClient/WorldInitialState.h"
#include "QGrid.h"

class Engine
{
public:
	Engine();
	~Engine();

	int add(int currentValue, int increment);

	WorldInitialState getWorldInitialState();

	Epoch processEpoch();

private:

	enum Direction
	{
		Left,
		Right,
		Top,
		Bottom
	};

	int startX, startY;

	WorldInitialState worldInitialState;

	QGrid qGrid;

	int epochNumber, qEpochCount, qSuccessCount;
	double successRate;

	WorldInitialState makeWorldInitialState();

	bool positionInPit(int x, int y);

	bool positionIsApple(int x, int y);
	
	double getReward(int x, int y);

	double getQFunctionMax(QFunction qFunction);

	QFunction calculateQFunction(int x, int y);

	Direction getQFunctionDirection(QFunction qFunction);
};
