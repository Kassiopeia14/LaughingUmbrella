#pragma once

#include <random>

#include "../modMessageBusClient/QFunction.h"
#include "../modMessageBusClient/Epoch.h"

class Engine
{
public:
	Engine();
	~Engine();

	int add(int currentValue, int increment);

	QFunction getQFunction();

	double getAccumulatedReward();

	Epoch processEpoch();

private:

	int epochNumber;

	int startX, startY;
};
