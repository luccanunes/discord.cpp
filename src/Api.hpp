#pragma once

#include <nlohmann/json.hpp>
#include <cpr/cpr.h>

namespace Api {
	std::string baseURL = "https://discord.com/api";
	std::string auth = "";

	inline void initialize(const std::string& token) {
		auth = "Bot " + token;
	}
	inline nlohmann::json get(const std::string& path) {
		cpr::Response res = cpr::Get(cpr::Url{ baseURL + path }, cpr::Header{ {"authorization", auth} });
		return nlohmann::json::parse(res.text);
	}
	inline nlohmann::json post(const std::string& path, const cpr::Body& body) {
		cpr::Response res = cpr::Post(
			cpr::Url{ baseURL + path },
			body,
			cpr::Header{ {"authorization", auth}, {"Content-Type", "application/json"} }
		);
		if (res.text.length() == 0)
			return nlohmann::json::parse("No body returned for response");
		return nlohmann::json::parse(res.text);
	}
	inline nlohmann::json put(const std::string& path) {
		cpr::Response res = cpr::Put(
			cpr::Url{ baseURL + path },
			cpr::Header{ {"authorization", auth}, {"Content-length", "0"} }
		);
		nlohmann::json result;
		if (res.text.length() != 0)
			result = nlohmann::json::parse(res.text);
		else
			result = nlohmann::json::parse("{}");
		return result;
	}
	inline nlohmann::json del(const std::string& path) {
		cpr::Response res = cpr::Delete(cpr::Url{ baseURL + path }, cpr::Header{ {"authorization", auth} });
		nlohmann::json result;
		if (res.text.length() != 0)
			result = nlohmann::json::parse(res.text);
		else
			result = nlohmann::json::parse("{}");
		return result;
	}
}