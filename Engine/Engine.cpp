#include "Engine.h"

Engine::Engine():
	gradientRate(1.),
	startX(8),
	startY(8),
	worldInitialState(makeWorldInitialState()),
	qGrid(),
	epochNumber(0),
	rd(),
	goldenAppleReached(false)
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
		.appleSet = 
		{ .cells =
			{
				{.reward = 5., .x = 6, .y = 4},
				{.reward = 4., .x = 3, .y = 2}
			}
		},
		.pit =
		{
			.cells =
			{				
				{.x = 3, .y = 3}, {.x = 3, .y = 4}, {.x = 3, .y = 5}, {.x = 3, .y = 6}, {.x = 3, .y = 7}, {.x = 3, .y = 8},
				{.x = 4, .y = 8}, {.x = 5, .y = 8}, {.x = 6, .y = 8},
				{.x = 8, .y = 6}, {.x = 8, .y = 5}, {.x = 8, .y = 4}, {.x = 8, .y = 3},
				{.x = 6, .y = 3}, {.x = 5, .y = 3}, {.x = 4, .y = 3}, {.x = 7, .y = 3},
				{.x = 7, .y = 6},  {.x = 6, .y = 6}
			}
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

	while ((pitCell != worldInitialState.pit.cells.end()) && !((pitCell->x == x) && (pitCell->y == y)))
	{
		pitCell++;
	}

	return (pitCell != worldInitialState.pit.cells.end());
}

bool Engine::positionIsApple(int x, int y, double& reward)
{
	auto appleCell = worldInitialState.appleSet.cells.begin();

	while ((appleCell != worldInitialState.appleSet.cells.end()) && !((appleCell->x == x) && (appleCell->y == y)))
	{
		appleCell++;
	}

	if (appleCell != worldInitialState.appleSet.cells.end())
	{
		reward = appleCell->reward;
		return true;
	}

	return false;
}

double Engine::getReward(int x, int y)
{
	double reward;

	if(positionIsApple(x, y, reward))
	{
		return reward - 1.;
	}
	else if (positionInPit(x, y))
	{
		return -100. - 1.;
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

QFunction Engine::calculateQFunction(int x, int y, Direction direction, int newX, int newY)
{	
	QFunction
		qFunction = qGrid.getQFunction(x, y),
		newPositionQFunction = qGrid.getQFunction(newX, newY);

	double
		newPositionEstimation = getReward(newX, newY) + getQFunctionMax(newPositionQFunction),
		leftDelta = (direction == Direction::Left ? newPositionEstimation - qFunction.left : 0.),
		rightDelta = (direction == Direction::Right ? newPositionEstimation - qFunction.right : 0.),
		topDelta = (direction == Direction::Top ? newPositionEstimation - qFunction.top : 0.),
		bottomDelta = (direction == Direction::Bottom ? newPositionEstimation - qFunction.bottom : 0.);

	return QFunction
	{
		.left = qFunction.left + gradientRate * leftDelta,
		.right = qFunction.right + gradientRate * rightDelta,
		.top = qFunction.top + gradientRate * topDelta,
		.bottom = qFunction.bottom + gradientRate * bottomDelta
	};
}

double qByIndex(QFunction qFunction, int index)
{
	switch (index)
	{
	case 0:
		return qFunction.left;
		break;
	case 1:
		return qFunction.right;
		break;
	case 2:
		return qFunction.top;
		break;
	case 3:
		return qFunction.bottom;
		break;
	default:
		throw;
	}
}

Engine::Direction Engine::getQFunctionDirection(QFunction qFunction)
{
	std::array<int, 4> indexes{ 0, 1, 2, 3 };

	std::mt19937 gen{ rd()};

	std::ranges::shuffle(indexes, gen);

	double max = - std::numeric_limits<double>::infinity();

	Direction result = (Direction)indexes[0];

	for (int i = 0; i < 4; i++)
	{
		double value = qByIndex(qFunction, indexes[i]);
		if (value > max)
		{
			max = value;
			result = (Direction)indexes[i];
		}
	}

	return result;
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

	double randomDecisionProbability = .1;

	while (!gameOver)
	{
		int
			xOld = x,
			yOld = y;

		QFunction qFunction = qGrid.getQFunction(x, y);
				
		bool randomDecision = randomDecision = rand() % 1000 < randomDecisionProbability * 1000;
		
		bool horizontal;
		int delta;

		Direction direction;

		if (randomDecision)
		{
			horizontal = rand() % 2;

			delta = (rand() % 2) * 2 - 1;

			direction = (horizontal ? (delta < 0 ? Engine::Left : Engine::Right) : (delta < 0 ? Engine::Top : Engine::Bottom));
		}
		else
		{
			direction = getQFunctionDirection(qFunction);

			switch (direction)
			{
			case Engine::Left:
				horizontal = true;
				delta = -1;
				break;
			case Engine::Right:
				horizontal = true;
				delta = 1;
				break;
			case Engine::Top:
				horizontal = false;
				delta = -1;
				break;
			case Engine::Bottom:
				horizontal = false;
				delta = 1;
				break;
			default:
				break;
			}
		}

		if (horizontal)
		{
			x = add(x, delta);
		}
		else
		{
			y = add(y, delta);
		}

		accumulatedReward -= 1.;

		double appleReward;

		if (positionInPit(x, y))
		{
			gameOver = true;
			accumulatedReward -= 100.;
		}
		else if (positionIsApple(x, y, appleReward))
		{
			gameOver = true;
			success = true;

			accumulatedReward += appleReward;

			if (appleReward == worldInitialState.appleSet.cells[0].reward)
			{
				goldenAppleReached = true;
			}
		} 

		QFunction newQFunction = calculateQFunction(xOld, yOld, direction, x, y);
		qGrid.setQFunction(xOld, yOld, newQFunction);
		agentStates.emplace_back(xOld, yOld, accumulatedReward, newQFunction);

	}

	agentStates.emplace_back(x, y, accumulatedReward, QFunction{ .left = 0., .right = 0., .top = 0., .bottom = 0. });

	Epoch epoch
	{
		.number = epochNumber,
		.agentStates = std::vector<AgentState>(agentStates.begin(), agentStates.end()),
		.success = success
	};

	if (goldenAppleReached)
	{
		std::cout << goldenAppleReached << ", epoch" << epochNumber << std::endl;
		goldenAppleReached = false;
	}
	epochNumber++;

	return epoch;
}

