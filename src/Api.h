#pragma once

#include <nlohmann/json.hpp>
#include <cpr/cpr.h>

namespace Api {
	extern std::string baseURL;
	extern std::string TOKEN;
	nlohmann::json get(const std::string& path);
	nlohmann::json post(const std::string& path, const cpr::Body& body);
}