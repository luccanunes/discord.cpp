#pragma once

#include <nlohmann/json.hpp>
#include <cpr/cpr.h>

namespace Api {
	extern std::string baseURL;
	extern std::string auth;
	void initialize(const std::string& token);
	nlohmann::json get(const std::string& path);
	nlohmann::json post(const std::string& path, const cpr::Body& body);
	nlohmann::json put(const std::string& path);
	nlohmann::json del(const std::string& path);
}