#pragma once

#include <random>
#include <list>

#include "../modMessageBusClient/QFunction.h"
#include "../modMessageBusClient/Epoch.h"
#include "../modMessageBusClient/WorldInitialState.h"

class Engine
{
public:
	Engine();
	~Engine();

	int add(int currentValue, int increment);

	WorldInitialState getWorldInitialState();

	QFunction getQFunction();

	double getAccumulatedReward();

	Epoch processEpoch();

private:

	WorldInitialState worldInitialState;

	int epochNumber;

	int startX, startY;

	WorldInitialState makeWorldInitialState();

	bool positionInPit(int x, int y);

	bool positionIsApple(int x, int y);
};
