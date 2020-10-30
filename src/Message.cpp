#include "Message.h"
#include "Api.h"
#include "urlEncode.h"

using json = nlohmann::json;

namespace dpp {
	Message::Message(json& props) {
		tts = props["tts"];
		timestamp = props["timestamp"];
		pinned = props["pinned"];
		mention_roles = props["mention_roles"];
		embeds = props["embeds"];
		attachments = props["attachments"];
		mention_everyone = props["mention_everyone"];
		member = props["member"];
		id = props["id"];
		content = props["content"];
		channel_id = props["channel_id"];
		if (!props["flags"].is_null())
			flags = props["flags"];
		if (!props["mentions"].is_null())
			mentions = props["mentions"];
		if (!props["guild_id"].is_null())
			guild_id = props["guild_id"];
		if (!props["reactions"].is_null())
			reactions = props["reactions"];

		author.initialize(props["author"]);
		json res = Api::get("/channels/" + channel_id);
		channel.initialize(res);
	}
	std::string Message::reply(const std::string& message) {
		const std::string path = "/channels/" + channel_id + "/messages";
		json body = {
			{"content", "<@" + author.id + "> " + message},
			{"allowed_mentions", {
				{"users", {author.id}}
			}}
		};
		return Api::post(path, cpr::Body{ body.dump() }).dump();
	}
	std::string Message::add_mention(const std::string& emoji) {
		return Api::put("/channels/" + channel_id + "/messages/" + id + "/reactions/" + urlEncode(emoji) + "/@me").dump();
	}
	bool Message::startsWith(const std::string& s) {
		return content.find(s) == 0;
	}
}