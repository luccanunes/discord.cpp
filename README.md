# discord.cpp
 A Discord API wrapper for creating BOT's 
 
## About
Inspired by the simplicity of [discord.py](https://github.com/Rapptz/discord.py) and [discord.js](https://github.com/discordjs/discord.js), discord.cpp tries to make the process of interacting with the [Discord API](https://discord.com/developers/docs/intro) easier, so you can worry less about all the socket connections under the hood, and focus on making your bot better.

## Example

```cpp
#include <iostream>
#include <dpp.h>

dpp::Client client;

int main()
{
 client.onReady = []() {
  std::cout << "hello, c++!\n";
  std::cout << client.user.id << "\n\n";
 };

 client.onMessage = [](dpp::Message message) {
  if (message.content == "jaaj?") {
   client.send("jooj", message.channel_id);
  }
 };
 
 client.run(TOKEN);
}
```

## Contributing
discord.cpp is really just a small project right now, so, if you feel like it, please consider helping us out!
