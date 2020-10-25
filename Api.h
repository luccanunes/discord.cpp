#pragma once

#include <nlohmann/json.hpp>
#include <cpr/cpr.h>

namespace Api {
	extern std::string baseURL;
	nlohmann::json get(const std::string path, const std::string token);
	nlohmann::json post(const std::string path, cpr::Body body, const std::string token);
}