﻿#include "Api.h"
#include <iostream>

using json = nlohmann::json;

namespace Api {
	std::string baseURL = "https://discord.com/api";
	std::string auth = "Bot TOKEN_HERE";
	void initialize(const std::string& token) {
		auth = "Bot " + token;
	}
	json get(const std::string& path) {
		const std::string URL = baseURL + path;
		cpr::Response res = cpr::Get(cpr::Url{ URL }, cpr::Header{ {"authorization", auth} });
		return json::parse(res.text);
	}
	json post(const std::string& path, const cpr::Body& body) {
		const std::string URL = baseURL + path;
		cpr::Response res = cpr::Post(
			cpr::Url{ URL },
			body,
			cpr::Header{ {"authorization", auth}, {"Content-Type", "application/json"} }
		);
		return json::parse(res.text);
	}
	json put(const std::string& path) {
		const std::string URL = baseURL + path;
		std::cout << "URL: " << URL << std::endl;
		cpr::Response res = cpr::Put(
			cpr::Url{ URL },
			cpr::Header{ {"authorization", auth}, {"Content-length", "0"} }
		);
		std::cout << "Response: " << res.text << std::endl;
		json result;
		if (res.text.length() != 0)
			result = json::parse(res.text);
		else
			result = json::parse("{}");
		return result;
	}
}
