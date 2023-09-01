#include "MessageBusClient.h"

MessageBusClient::MessageBusClient()
{

}

MessageBusClient::~MessageBusClient()
{

}

std::string MessageBusClient::sendWorldInitialState(WorldInitialState worldInitialState)
{
	std::wstring url(L"/api/WorldInitialState");

	nlohmann::json j(worldInitialState);

	std::string data(j.dump());

	//std::cout << data << std::endl;

	POST_HTTPRequest request;

	std::string result = request.send(url, data);

	return result;
}

WorldInitialState MessageBusClient::getWorldInitialState()
{
	std::wstring url(L"/api/WorldInitialState");
	
	GET_HTTPRequest request;

	std::string data = request.get(url);

	auto j = nlohmann::json::parse(data.c_str());

	WorldInitialState result = j.get<WorldInitialState>();

	return result;
}