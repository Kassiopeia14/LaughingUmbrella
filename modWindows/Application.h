#pragma once

#include <functional>
#include <chrono>
#include <thread>
#include <Windows.h>

class Application
{
public:
	Application(const HINSTANCE _instance);
	~Application();

	ATOM registerMainWindowClass(WNDPROC mainWindowProcedure);

	WPARAM run(std::function<void()> task);

private:

	const HINSTANCE instance;

};
