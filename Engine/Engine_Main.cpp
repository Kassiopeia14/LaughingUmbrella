#include <iostream>
#include "../modHTTP/POST_HTTPRequest.h"
#include "../modMessageBusClient/MessageBusClient.h"

void test()
{
	std::wstring url(L"/api/some");

	std::string data("{ \"name\":\"John\", \"age\":23 }");

	POST_HTTPRequest request;

	std::string result = request.send(url, data);

	std::cout << result << std::endl;
}

int main()
{
	MessageBusClient MessageBusClient;

	WorldInitialState worldInitialState
	{
		.apple = {.x = 5, .y = 9},
		.pit =
		{
			.cells = { {.x = 7, .y = 1}, {.x = 7, .y = 2}, {.x = 7, .y = 3} }
		}
	};

	std::string postResult = MessageBusClient.sendWorldInitialState(worldInitialState);

	std::cout << "POST: " << postResult << std::endl;

	WorldInitialState getResult = MessageBusClient.getWorldInitialState();

	std::cout << "GET: apple " << getResult.apple.x << ", " << getResult.apple.y << std::endl;

	system("pause");
}