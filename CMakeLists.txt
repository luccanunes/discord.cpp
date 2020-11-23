cmake_minimum_required(VERSION 3.0.0)
project(discord_cpp VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

# cpr
include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/whoshuu/cpr.git GIT_TAG c8d33915dbd88ad6c92b258869b03aba06587ff9) # the commit hash for 1.5.0
FetchContent_MakeAvailable(cpr)

include(FetchContent)
FetchContent_Declare(ixwebsocket GIT_REPOSITORY https://github.com/machinezone/IXWebSocket.git GIT_TAG 75e9c84388879262d924e0582f094b38550093dc) # the commit hash for 1.5.0
FetchContent_MakeAvailable(ixwebsocket)

find_package(nlohmann_json REQUIRED)

add_library(discord_cpp
    "src/Api.cpp"
    "src/Channel.cpp"
    "src/Client.h"
    "src/Command.cpp"
    "src/Embed.cpp"
    "src/Guild.cpp"
    "src/Message.cpp"
    "src/Role.cpp"
    "src/urlEncode.cpp"
    "src/User.cpp"
    "src/Webhook.cpp"
)

target_link_libraries(${PROJECT_NAME} PRIVATE cpr::cpr)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/libs/cpr/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/libs/IXWebSocket)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/libs/json/include)