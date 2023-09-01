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
		.left = .0,
		.right = .0,
		.top = .0,
		.bottom = .0
	};
}
