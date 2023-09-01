#pragma once

#include <string>
#include <Windows.h>
#include <winhttp.h>

class POST_HTTPRequest
{
public:

	POST_HTTPRequest();
	~POST_HTTPRequest();

	std::string send(std::wstring url, std::string data);

private:

};

