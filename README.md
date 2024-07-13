# cpp-console-game

A very simple multiplayer terminal game where you can explore the world with your friends!

![demo image](/images/party.png)

What you are seeing here is about the extend of "the world" that you are able to explore, but with a little bit of imagination this can represent anything you could ever want it to.

You play as a `@` in a world full of `#`s. Use the WASD keys to move around the area, and press Q when you are ready to leave. Your friends will be able to observe your movements in real time, as you will be able to do for them.

## Why?

This project was created as an introductory project for learning C++ as well as some basic networking using RPC. The source code is written in C++, compiled using CMake, and includes a basic custom RPC library (see the `eRPC` directory) that is done through C's sockets API.

## Build Instructions

The build system is CMake, so it can be compiled in the standard way. The following instructions are for Unix-based systems.

```sh
# from project root
mkdir build
cd build
cmake ..
cmake --build .
```

## Usage

Once the build is complete, you can play the game by first starting a server then joining as a client.

To start a server:
```sh
# from build directory
./cpp-console-game/cpp-console-game server <port>
```

To start a client:
```sh
# from build directory
./cpp-console-game/cpp-console-game client <port> <host>
```

You can have up to 200 players, but then it will be real crowded!

## eRPC

I created a custom RPC library for this project. It is very basic, and may not have all of the features necessary to be considered RPC, but it was created for my personal learning. The API is very simple. The server binds methods, and the clients can call those bound methods as though they were regular client functions in the code.

You can find the usage of this library in `cpp-console-game/GameClient.cpp` and `cpp-console-game/GameServer.cpp`.

### Protocol: Request
```
eRPC 1.0
<msgid>
<method>
<param1>
<param2>
...
<paramN>
```

`msgid` - integer ID of the message, this will be the same in the server response. If this value is `-1` then then the request will be considered a notification and the server will send back no response.

`method` - string name of the method to be called.

`param*` - list of parameters on each line to be fed into the function.

### Protocol: Response
```
eRPC 1.0
<msgid>
<ok?>
<result>
```

`msgid` - integer ID of the message, same as what was received in the request

`ok?` - `OK` if all is well, `ERROR` if there is an error

`result` - return value of the method, or string value describing the error if there was one
