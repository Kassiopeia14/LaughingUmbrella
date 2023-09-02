#include "Engine.h"

Engine::Engine():
	epochNumber(0),
	startX(5), 
	startY(5)
{
}

Engine::~Engine()
{
}

int Engine::add(int currentValue, int increment)
{
	int result = currentValue + increment;

	if (result < 0)
	{
 		result = 10 - (-result) % 10;
	}

	if (result > 10 - 1)
	{
		result = result % 10;
	}

	return result;
}

QFunction Engine::getQFunction()
{
	return
	{
		.left = (double)(rand() % 10000) / 1000,
		.right = (double)(rand() % 10000) / 1000,
		.top = (double)(rand() % 10000) / 1000,
		.bottom = (double)(rand() % 10000) / 1000
	};
}

double Engine::getAccumulatedReward()
{
	return (double)(rand() % 10000) / 1000;
}

Epoch Engine::processEpoch()
{
	const size_t stateCount = 1 + rand() % 32;

	int x = startX,
		y = startY;

	std::vector<AgentState> agentStates(stateCount);

	for (auto stateItem = agentStates.begin(); stateItem != agentStates.end(); stateItem++)
	{
		stateItem->x = x;
		stateItem->y = y;
		stateItem->accumulatedReward = getAccumulatedReward();
		stateItem->qFunction = getQFunction();

		bool direction = rand() % 2;

		int delta = (rand() % 2) * 2 - 1;

		if (direction)
		{
			x = add(x, delta);
		}
		else
		{
			y = add(y, delta);
		}
	}

	Epoch epoch
	{
		.number = epochNumber,
		.agentStates = agentStates
	};

	epochNumber++;

	return epoch;
}

