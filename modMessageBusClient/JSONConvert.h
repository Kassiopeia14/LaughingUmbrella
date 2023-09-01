#pragma once

#include "WorldInitialState.h"
#include "../include/json.hpp"
#include "Epoch.h"

void to_json(nlohmann::json& j, const PitCell& object);

void from_json(const nlohmann::json& j, PitCell& object);

void to_json(nlohmann::json& j, const Pit& object);

void from_json(const nlohmann::json& j, Pit& object);

void to_json(nlohmann::json& j, const Apple& object);

void from_json(const nlohmann::json& j, Apple& object);

void to_json(nlohmann::json& j, const WorldInitialState& object);

void from_json(const nlohmann::json& j, WorldInitialState& object);

void to_json(nlohmann::json& j, const QFunction& object);

void from_json(const nlohmann::json& j, QFunction& object);

void to_json(nlohmann::json& j, const AgentState& object);

void from_json(const nlohmann::json& j, AgentState& object);

void to_json(nlohmann::json& j, const Epoch& object);

void from_json(const nlohmann::json& j, Epoch& object);