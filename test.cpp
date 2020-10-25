#include <iostream>
#include "dpp.h"


int main()
{
	dpp::Client client;
	std::string TOKEN = "NzY5MjIwMjEyODA4ODc2MDMz.X5L2Jg.To8C4xQog1OeDdeCTdT9b6lW86o";

	client.onReady = [&]() {
		std::cout << "ready to go boiiis\n";
		std::cout << "hello, c++\n";
		std::cout << client.user.id << "\n";
	};

	client.onMessage = [&](dpp::Message message) {
		std::cout << "NEW MESSAGE: " << message.content << std::endl;
	};

	client.run(TOKEN);
}