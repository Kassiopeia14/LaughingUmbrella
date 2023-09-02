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

	Epoch processEpoch();

private:

	int startX, startY;

	WorldInitialState worldInitialState;

	int epochNumber;

	WorldInitialState makeWorldInitialState();

	bool positionInPit(int x, int y);

	bool positionIsApple(int x, int y);
};
