#include "Embed.h"

#include <iostream>

namespace dpp {
	Embed::Embed() {
		colour = -1;
		url = "";
		title = "";
		timestamp = "";
		description = "";
	}
	void Embed::setColour(const int& colour) {
		this->colour = colour;
	}
	void Embed::setUrl(const std::string& url) {
		this->url = url;
	}
	void Embed::setTitle(const std::string& title) {
		this->title = title;
	}
	void Embed::setTimestamp(const std::string& timestamp) {
		this->timestamp = timestamp;
	}
	void Embed::setDescription(const std::string& description) {
		this->description = description;
	}
	nlohmann::json Embed::json() const {
		nlohmann::json j;
		if (colour >= 0)
			j["colour"] = colour;
		if (!url.empty())
			j["url"] = url;
		if (!title.empty())
			j["title"] = title;
		if (!timestamp.empty())
			j["timestamp"] = timestamp;
		if (!description.empty())
			j["description"] = description;
		return j;
	}
}