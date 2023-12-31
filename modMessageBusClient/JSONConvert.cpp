#include "JSONConvert.h"

void to_json(nlohmann::json& j, const PitCell& object)
{
	j = nlohmann::json{ {"x", object.x}, {"y", object.y} };
}

void from_json(const nlohmann::json& j, PitCell& object)
{
	j.at("x").get_to(object.x);
	j.at("y").get_to(object.y);
}

void to_json(nlohmann::json& j, const Pit& object)
{
	j = nlohmann::json{ {"cells", object.cells} };
}

void from_json(const nlohmann::json& j, Pit& object) 
{
	j.at("cells").get_to(object.cells);
}

void to_json(nlohmann::json& j, const AppleCell& object)
{
	j = nlohmann::json{ {"reward", object.reward}, {"x", object.x}, {"y", object.y} };
}

void from_json(const nlohmann::json& j, AppleCell& object)
{
	j.at("reward").get_to(object.reward);
	j.at("x").get_to(object.x);
	j.at("y").get_to(object.y);
}

void to_json(nlohmann::json& j, const AppleSet& object)
{
	j = nlohmann::json{ {"cells", object.cells} };
}

void from_json(const nlohmann::json& j, AppleSet& object)
{
	j.at("cells").get_to(object.cells);
}

void to_json(nlohmann::json& j, const WorldInitialState& object)
{
	j = nlohmann::json{ {"apple_set", object.appleSet}, {"pit", object.pit}, {"start_x", object.startX}, {"start_y", object.startY} };
}

void from_json(const nlohmann::json& j, WorldInitialState& object) 
{
	j.at("apple_set").get_to(object.appleSet);
	j.at("pit").get_to(object.pit);
	j.at("start_x").get_to(object.startX);
	j.at("start_y").get_to(object.startY);
}

void to_json(nlohmann::json& j, const QFunction& object)
{
	j = nlohmann::json{ {"left", object.left}, {"right", object.right}, {"top", object.top}, {"bottom", object.bottom} };
}

void from_json(const nlohmann::json& j, QFunction& object)
{
	j.at("left").get_to(object.left);
	j.at("right").get_to(object.right);
	j.at("top").get_to(object.top);
	j.at("bottom").get_to(object.bottom);
}

void to_json(nlohmann::json& j, const AgentState& object)
{
	j = nlohmann::json{ {"x", object.x}, {"y", object.y}, {"accumulated_reward", object.accumulatedReward}, {"q_function", object.qFunction} };
}

void from_json(const nlohmann::json& j, AgentState& object)
{
	j.at("x").get_to(object.x);
	j.at("y").get_to(object.y);
	j.at("accumulated_reward").get_to(object.accumulatedReward);
	j.at("q_function").get_to(object.qFunction);
}

void to_json(nlohmann::json& j, const Epoch& object)
{
	j = nlohmann::json{ {"number", object.number}, {"agent_states", object.agentStates}, {"success", object.success} };
}

void from_json(const nlohmann::json& j, Epoch& object)
{
	j.at("number").get_to(object.number);
	j.at("agent_states").get_to(object.agentStates);
	j.at("success").get_to(object.success);
}