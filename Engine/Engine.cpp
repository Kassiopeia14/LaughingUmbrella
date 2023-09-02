#include "Engine.h"

Engine::Engine():
	startX(2),
	startY(4),
	worldInitialState(makeWorldInitialState()),
	epochNumber(0)
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
		},
		.startX = startX,
		.startY = startY
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

	double accumulatedReward = 0.;

	std::list<AgentState> agentStates;

	while (!gameOver)
	{
		agentStates.emplace_back(x, y, accumulatedReward, getQFunction());

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

		accumulatedReward -= 1.;

		if (positionIsApple(x, y))
		{
			gameOver = true;
			success = true;

			accumulatedReward += 10.;
		}
		else if (positionInPit(x, y))
		{
			gameOver = true;	

			accumulatedReward -= 100.;
		}
	}

	agentStates.emplace_back(x, y, accumulatedReward, QFunction{.left=0., .right=0., .top=0., .bottom=0.});

	Epoch epoch
	{
		.number = epochNumber,
		.agentStates = std::vector<AgentState>(agentStates.begin(), agentStates.end()),
		.success = success
	};

	epochNumber++;

	return epoch;
}

