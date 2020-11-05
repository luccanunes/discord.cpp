<div align="center">
  <img src="https://i.imgur.com/FvKs4Hr.png">
  <p>A Discord API wrapper for creating C++ BOT's</p>
</div>

---
 
## <img align="center" src="https://img.icons8.com/plasticine/2x/new.png" width="50" /> Features

- Embed & Webhook support!

 
## About
Inspired by the simplicity of [discord.py](https://github.com/Rapptz/discord.py) and [discord.js](https://github.com/discordjs/discord.js), discord.cpp tries to make the process of interacting with the [Discord API](https://discord.com/developers/docs/intro) easier, so you can worry less about all the socket connections under the hood, and focus on making your bot better.

## Example

```cpp
#include <iostream>
#include <dpp.h>

int main()
{
 const std::string token = "BOT_TOKEN_HERE";
 dpp::Client client;

 client.onReady = [&]() {
  std::cout << "hello, c++!\n";
  std::cout << client.user.id << "\n\n";
 };

 client.onMessage = [&](const dpp::Message& message) {
  if (message.content == "jaaj?") {
   message.channel().send("jooj"); // or message.reply("jooj"), which mentions the message author
  }
 };
 
 client.run(token);
 
 return 0;
}
```

## Installation and set up
First of all, clone the repository to your machine in a directory of your choice (make sure you're cloning the `main` branch, not the `development` one).

To create your own project using discord.cpp you have to follow these steps, for this example I'll use Visual Studio, but the steps should be the same. Just google the specifics for your IDE of choice.

#### Create your solution
#### Add a source file and paste the example code
#### Add the compiler include path:
To starting using discord.cpp and all its features, you first have to tell your IDE/compiler where you're importing it from.
Here's how to do it in Visual Studio:
1. Right click your *project* name and select properties <br/> <img width='350' src="https://user-images.githubusercontent.com/68504851/97646641-f66ba680-1a2e-11eb-809b-b263b8428130.png">
2. Select "C/C++" 
3. Click "Additional Include Directories", selected the small arrow on the right and click "Edit" <br/> <img width='550' src="https://user-images.githubusercontent.com/68504851/97646811-67ab5980-1a2f-11eb-8667-ec9e1b6b135e.png">
4. Click the new folder icon and then the three dots to starting browsing your file explorer. <br/> <img width='450' src="https://user-images.githubusercontent.com/68504851/97646868-9cb7ac00-1a2f-11eb-9527-26ea2df19536.png">
5. Select the "/src" folder in the directory that you installed discord.cpp
6. Click "Ok" and "Apply".
#### Add the linker path:
Now that you've added the include path, the compiler is able to find all the classes and functions declarations, but not really their definitions. For that, we need to include an additional depencie to the linker.
Here's how to do it in Visual Studio:
1. Follow step 1 of "Add the compiler include path"
2. Select "Linker"
3. Click "Additional Library Directories", selected the small arrow on the right and click "Edit" <br/> <img width='450' src="https://user-images.githubusercontent.com/68504851/97648131-c32b1680-1a32-11eb-9dfb-ff97f34e4ff4.png">
4. Click the new folder icon and then the three dots to starting browsing your file explorer. <br/> <img width='450' src="https://user-images.githubusercontent.com/68504851/97648199-ebb31080-1a32-11eb-9218-9ed4a5e83a98.png">
5. Select the "/src/Release" folder in the directory that you installed discord.cpp
6. Click "Ok" and "Apply".
7. Now, go to the "Input" tab, still in the linker properties
8. Select "Additional Dependencies", and edit the text string by adding "discord-cpp.lib;" to its beginning <br/> <img width='450' src="https://user-images.githubusercontent.com/68504851/97648393-62500e00-1a33-11eb-8eba-45eed1fcd837.png">
9. Hit "Apply" and "Ok" and you should be good to go.

## Documentation
We're still working on the library documentation, you can follow the updates by checking it's [github repository](https://github.com/luccanunes/discord.cpp-docs/blob/master/README.md) or just checking the actual [docs website](https://discord-cpp-lib.github.io/documentation/)

## Special thanks
- [IXWebSocket](https://github.com/machinezone/IXWebSocket)
- [nlohmann json](https://github.com/nlohmann/json)
- [cpr (C++ requests)](https://github.com/whoshuu/cpr)

Maintaining discord.cpp is only possible thanks to these incredible and easy to use libraries.

## Contributing
discord.cpp is really just a small project right now, so, if you feel like it, please consider helping us out!
