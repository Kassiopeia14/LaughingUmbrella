#include "Engine.h"

Engine::Engine():
	worldInitialState(makeWorldInitialState()),
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

WorldInitialState Engine::makeWorldInitialState()
{
	return WorldInitialState
	{
		.apple = {.x = 5, .y = 9},
		.pit =
		{
			.cells = { {.x = 7, .y = 1}, {.x = 7, .y = 2}, {.x = 7, .y = 3} }
		}
	};
}

WorldInitialState Engine::getWorldInitialState()
{
	return worldInitialState;
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

bool Engine::positionInPit(int x, int y)
{
	auto pitCell = worldInitialState.pit.cells.begin();

	while (pitCell != worldInitialState.pit.cells.end() && !(pitCell->x == x && pitCell->y == y))
	{
		pitCell++;
	}

	return (pitCell != worldInitialState.pit.cells.end());
}

bool Engine::positionIsApple(int x, int y)
{
	return (x == worldInitialState.apple.x && y == worldInitialState.apple.y);
}

Epoch Engine::processEpoch()
{
	bool 
		gameOver = false,
		success = false;

	int x = startX,
		y = startY;

	std::list<AgentState> agentStates;

	while (!gameOver)
	{
		agentStates.emplace_back(x, y, getAccumulatedReward(), getQFunction());

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

		if (positionIsApple(x, y))
		{
			gameOver = true;
			success = true;
		}
		else if (positionInPit(x, y))
		{
			gameOver = true;			
		}
	}

	Epoch epoch
	{
		.number = epochNumber,
		.agentStates = std::vector<AgentState>(agentStates.begin(), agentStates.end()),
		.success = success
	};

	epochNumber++;

	return epoch;
}

