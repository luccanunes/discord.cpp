#include <iostream>
#include "dpp.h"

dpp::Client client;

int main()
{
	std::string TOKEN = "NzY5MjIwMjEyODA4ODc2MDMz.X5L2Jg.To8C4xQog1OeDdeCTdT9b6lW86o";

	client.onReady = []() {
		std::cout << "hello, c++!" << std::endl;
		std::cout << client.user.id << "\n\n";
	};

	client.onMessage = [](dpp::Message message) {
		std::cout << "its a message!!" << std::endl;
		if (message.content == "jaaj?") {
			client.send("jooj.", message.channel_id);
		}
	};
	client.run(TOKEN);
}