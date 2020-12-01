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
	void Embed::setColour(const int& r, const int& g, const int& b) {
		colour = (r * 65536) + (g * 256) + b;
	}
	void Embed::setColour(std::string hex) {
		if (hex.at(0) == '#')
			hex = hex.substr(1);
		std::cout << hex << std::endl;
		colour = std::stoul(hex, nullptr, 16);
	}
	void Embed::setUrl(const std::string& url) {
		this->url = url;
	}
	void Embed::setTitle(const std::string& title) {
		this->title = title;
	}
	void Embed::setFooter(const std::string& text, const std::string& iconUrl) {
		nlohmann::json footer;
		footer["text"] = text;
		if (!iconUrl.empty())
			footer["icon_url"] = iconUrl;
		this->footer = footer;
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
			j["color"] = colour;
		if (!url.empty())
			j["url"] = url;
		if (!title.empty())
			j["title"] = title;
		if (!footer.is_null())
			j["footer"] = footer;
		if (!timestamp.empty())
			j["timestamp"] = timestamp;
		if (!description.empty())
			j["description"] = description;
		return j;
	}
}