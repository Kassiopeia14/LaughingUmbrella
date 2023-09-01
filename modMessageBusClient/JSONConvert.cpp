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

void to_json(nlohmann::json& j, const Apple& object)
{
	j = nlohmann::json{ {"x", object.x}, {"y", object.y} };
}

void from_json(const nlohmann::json& j, Apple& object) 
{
	j.at("x").get_to(object.x);
	j.at("y").get_to(object.y);
}

void to_json(nlohmann::json& j, const WorldInitialState& object)
{
	j = nlohmann::json{ {"apple", object.apple}, {"pit", object.pit} };
}

void from_json(const nlohmann::json& j, WorldInitialState& object) 
{
	j.at("apple").get_to(object.apple);
	j.at("pit").get_to(object.pit);
}