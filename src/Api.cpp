#include "Api.h"

using json = nlohmann::json;

namespace Api {
	std::string baseURL = "https://discord.com/api";
	std::string auth = "Bot TOKEN_HERE";
	void initialize(const std::string& token) {
		auth = "Bot " + token;
	}
	json get(const std::string& path) {
		cpr::Response res = cpr::Get(cpr::Url{ baseURL + path }, cpr::Header{ {"authorization", auth} });
		return json::parse(res.text);
	}
	json post(const std::string& path, const cpr::Body& body) {
		cpr::Response res = cpr::Post(
			cpr::Url{ baseURL + path },
			body,
			cpr::Header{ {"authorization", auth}, {"Content-Type", "application/json"} }
		);
		if (res.text.length() == 0)
			return json::parse("No body returned for response");
		return json::parse(res.text);
	}
	json put(const std::string& path) {
		cpr::Response res = cpr::Put(
			cpr::Url{ baseURL + path },
			cpr::Header{ {"authorization", auth}, {"Content-length", "0"} }
		);
		json result;
		if (res.text.length() != 0)
			result = json::parse(res.text);
		else
			result = json::parse("{}");
		return result;
	}
	json del(const std::string& path) {
		cpr::Response res = cpr::Delete(cpr::Url{ baseURL + path }, cpr::Header{ {"authorization", auth} });
		json result;
		if (res.text.length() != 0)
			result = json::parse(res.text);
		else
			result = json::parse("{}");
		return result;
	}
}
