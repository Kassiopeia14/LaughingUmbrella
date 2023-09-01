#pragma once

#include <string>
#include <Windows.h>
#include <winhttp.h>

class GET_HTTPRequest
{
public:

	GET_HTTPRequest();
	~GET_HTTPRequest();

	std::string get(std::wstring url);

private:

};
