#include <json.hpp>
#include <iostream>
#include <vector>
#include <string>

struct MainData
{
	int number;
	std::string description;
};

void to_json(nlohmann::json& j, const MainData& p)
{
	j = nlohmann::json{ {"number", p.number}, {"description", p.description} };
}

void from_json(const nlohmann::json& j, MainData& p) {
	j.at("number").get_to(p.number);
	j.at("description").get_to(p.description);
}

struct SomeItem
{
	double x, y;
	std::string name;
};

void to_json(nlohmann::json& j, const SomeItem& p)
{
	j = nlohmann::json{ {"x", p.x}, {"y", p.y}, {"name", p.name} };
}

void from_json(const nlohmann::json& j, SomeItem& p) {
	j.at("x").get_to(p.x);
	j.at("y").get_to(p.y);
	j.at("name").get_to(p.name);
}

struct ExmpleData
{
	MainData mainData;
	std::vector<SomeItem> someItems;
};

void to_json(nlohmann::json& j, const ExmpleData& p)
{
	j = nlohmann::json{ {"mainData", p.mainData}, {"someItems", p.someItems} };
}

void from_json(const nlohmann::json& j, ExmpleData& p) {
	j.at("mainData").get_to(p.mainData);
	j.at("someItems").get_to(p.someItems);
}


int main()
{
	ExmpleData ed
	{
		.mainData = {.number = -7, .description = "abc"},
		.someItems = { { .x = 0.5, .y = -11.2, .name = "item1" }, {.x = 88.73, .y = 0.0, .name = "item2" }, {.x = -99.5, .y = 3141.72, .name = "item3" }, }
	};

	nlohmann::json j(ed);

	std::string s(j.dump());

	std::cout << s << std::endl;

	auto ed_copy = j.get<ExmpleData>();

	std::cout << ed_copy.someItems[1].x << std::endl;
}
