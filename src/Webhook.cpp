#include "Webhook.h"

using json = nlohmann::json;

namespace dpp {
	Webhook::Webhook(const std::string url) {
		this->url = url;
	}
	Webhook::Webhook(const std::string id, const std::string token) {
		this->url = "https://discord.com/api/webhooks/" + id + "/" + token;
	}

	std::string Webhook::send(const std::vector<Embed>& embeds) const {
		std::vector<json> embedArray;
		for (Embed e : embeds)
			embedArray.push_back(e.json());
		json body = { {"embeds", embedArray} };
		return post(cpr::Body{ body.dump() });
	}
	std::string Webhook::send(const std::string& message) const {
		const std::string body = "{\"content\": \"" + message + "\"}";
		return post(cpr::Body{ body });
	}
	std::string Webhook::send(const std::string& message, const std::vector<Embed>& embeds) const {
		std::vector<json> embedArray;
		for (Embed e : embeds)
			embedArray.push_back(e.json());
		json body = { {"content", message}, {"embeds", embedArray} };
		return post(cpr::Body{ body.dump() });
	}

	std::string Webhook::post(const cpr::Body& body) const {
		cpr::Response res = cpr::Post(
			cpr::Url{ url },
			body,
			cpr::Header{ {"Content-Type", "application/json"} }
		);
		return res.text;
	}
}