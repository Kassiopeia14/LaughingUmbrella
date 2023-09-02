#include "Engine.h"

Engine::Engine():
	startX(2),
	startY(4),
	worldInitialState(makeWorldInitialState()),
	qGrid(),
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

double Engine::getReward(int x, int y)
{
	if(positionIsApple(x, y))
	{
		return 10.;
	}
	else if (positionInPit(x, y))
	{
		return -100.;
	}
	else
	{
		return -1.;
	}
}

double Engine::getQFunctionMax(QFunction qFunction)
{
	double result = qFunction.left;

	if (qFunction.right > result)
	{
		result = qFunction.right;
	}
	if (qFunction.top > result)
	{
		result = qFunction.top;
	}
	if (qFunction.bottom > result)
	{
		result = qFunction.bottom;
	}

	return result;
}

QFunction Engine::calculateQFunction(int x, int y)
{
	int leftX = add(x, -1),
		leftY = y,
		rightX = add(x, 1),
		rightY = y,
		topX = x,
		topY = add(y, -1),
		bottomX = x,
		bottomY = add(y, 1);

	QFunction
		qFunction = qGrid.getQFunction(x, y),
		leftQFunction = qGrid.getQFunction(leftX, leftY),
		rightQFunction = qGrid.getQFunction(rightX, rightY),
		topQFunction = qGrid.getQFunction(topX, topY),
		bottomQFunction = qGrid.getQFunction(bottomX, bottomY);

	double
		leftEstimation = getReward(leftX, leftY) + getQFunctionMax(leftQFunction),
		rightEstimation = getReward(rightX, rightY) + getQFunctionMax(rightQFunction),
		topEstimation = getReward(topX, topY) + getQFunctionMax(topQFunction),
		bottomEstimation = getReward(bottomX, bottomY) + getQFunctionMax(bottomQFunction),
		leftDelta = leftEstimation - qFunction.left,
		rightDelta = rightEstimation - qFunction.right,
		topDelta = topEstimation - qFunction.top,
		bottomDelta = bottomEstimation - qFunction.bottom;

	return QFunction
	{
		.left = qFunction.left + 0.1 * leftDelta,
		.right = qFunction.right + 0.1 * rightDelta,
		.top = qFunction.top + 0.1 * topDelta,
		.bottom = qFunction.bottom + 0.1 * bottomDelta
	};
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
		QFunction qFunction = calculateQFunction(x, y);

		qGrid.setQFunction(x, y, qFunction);

		agentStates.emplace_back(x, y, accumulatedReward, qFunction);

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

