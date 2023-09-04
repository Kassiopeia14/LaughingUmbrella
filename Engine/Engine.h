#pragma once

#include <random>
#include <list>
#include <iostream>
#include <limits>
#include <algorithm>
#include<array>

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

	double gradientRate;

	int startX, startY;

	WorldInitialState worldInitialState;

	QGrid qGrid;

	int epochNumber;

	std::random_device rd;

	bool goldenAppleReached;

	WorldInitialState makeWorldInitialState();

	bool positionInPit(int x, int y);

	bool positionIsApple(int x, int y, double& reward);
	
	double getReward(int x, int y);

	double getQFunctionMax(QFunction qFunction);

	QFunction calculateQFunction(int x, int y, Direction direction, int newX, int newY);

	Direction getQFunctionDirection(QFunction qFunction);
};
