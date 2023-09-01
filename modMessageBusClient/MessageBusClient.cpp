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

std::string MessageBusClient::sendEpoch(Epoch epoch)
{
	std::wstring url(L"/api/Epoch");

	nlohmann::json j(epoch);

	std::string data(j.dump());

	POST_HTTPRequest request;

	std::string result = request.send(url, data);

	return result;
}

Epoch MessageBusClient::getEpoch(int epochNumber)
{
	std::wstring url(L"/api/Epoch/" + std::to_wstring(epochNumber));

	GET_HTTPRequest request;

	std::string data = request.get(url);

	auto j = nlohmann::json::parse(data.c_str());

	Epoch result = j.get<Epoch>();

	return result;
}
