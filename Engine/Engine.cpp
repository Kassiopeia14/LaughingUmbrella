#include "Engine.h"

Engine::Engine()
{
}

Engine::~Engine()
{
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
