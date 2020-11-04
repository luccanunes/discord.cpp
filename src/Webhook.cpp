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
		if (name.length() != 0) body["username"] = name;
		if (avatar_url.length() != 0) body["avatar_url"] = avatar_url;
		if (tts) body["tts"] = tts;

		return post(cpr::Body{ body.dump() });
	}
	std::string Webhook::send(const std::string& message) const {
		json body = { {"content", message} };
		if (name.length() != 0) body["username"] = name;
		if (avatar_url.length() != 0) body["avatar_url"] = avatar_url;
		if (tts) body["tts"] = tts;

		return post(cpr::Body{ body.dump() });
	}
	std::string Webhook::send(const std::string& message, const std::vector<Embed>& embeds) const {
		std::vector<json> embedArray;
		for (Embed e : embeds)
			embedArray.push_back(e.json());
		json body = { {"content", message}, {"embeds", embedArray} };
		if (name.length() != 0) body["username"] = name;
		if (avatar_url.length() != 0) body["avatar_url"] = avatar_url;
		if (tts) body["tts"] = tts;

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

	void Webhook::setName(const std::string& name) {
		this->name = name;
	}
	void Webhook::setAvatarUrl(const std::string& avatar_url) {
		this->avatar_url = avatar_url;
	}
	void Webhook::setTts(const bool& tts) {
		this->tts = tts;
	}
}