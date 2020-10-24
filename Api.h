#pragma once

#include <nlohmann/json.hpp>
#include <cpr/cpr.h>

namespace Api {
	nlohmann::json get(const std::string URL, const std::string token);
	nlohmann::json post(const std::string URL, cpr::Body body, const std::string token);
}