#include <iostream>
#include "dpp.h"

dpp::Client client;

int main()
{
	std::string TOKEN = "NzY5MjIwMjEyODA4ODc2MDMz.X5L2Jg.To8C4xQog1OeDdeCTdT9b6lW86o";

	client.onMessage = [](dpp::Message message) {
		std::cout << "its a message!!" << std::endl;
		if (message.content == "eae") {
			client.send("jooj", message.channel_id);
			std::cout << client.user.id << std::endl;
		}
	};
	client.run(TOKEN);
}