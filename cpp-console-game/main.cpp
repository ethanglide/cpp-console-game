#include "GameState.hpp"

#include <unistd.h>
#include <thread>
#include <conio.hpp>
#include <Server.hpp>
#include <Client.hpp>
#include <iostream>

ConsoleGame::GameState gameState(20, 10);

void inputLoop(int playerId)
{
  while (gameState.isRunning())
  {
    char c = conio::getch();
    auto position = gameState.getPlayerPosition(playerId);

    switch (c)
    {
    case 'w':
      gameState.movePlayer(playerId, {position.first, position.second - 1});
      break;
    case 'a':
      gameState.movePlayer(playerId, {position.first - 1, position.second});
      break;
    case 's':
      gameState.movePlayer(playerId, {position.first, position.second + 1});
      break;
    case 'd':
      gameState.movePlayer(playerId, {position.first + 1, position.second});
      break;
    case 'q':
      gameState.stop();
      break;
    case 'p':
      gameState.addPlayer();
      break;
    }
  }
}

void renderLoop()
{
  std::cout << "\033[2J"; // Clear the screen

  while (gameState.isRunning())
  {
    gameState.draw();
    usleep(100000); // Sleep for 100ms
  }
}

std::pair<bool, std::string> movePlayer(std::vector<std::string> args)
{
  int playerId = std::stoi(args[0]);
  int x = std::stoi(args[1]);
  int y = std::stoi(args[2]);

  //gameState.movePlayer(playerId, {x, y});
  std::cout << "Player " << playerId << " moved to (" << x << ", " << y << ")" << std::endl;

  return {true, "Move Successful"};
}

std::pair<bool, std::string> echo(std::vector<std::string> args)
{
  for (auto arg : args)
  {
    std::cout << arg << " ";
  }

  std::cout << std::endl;

  return {true, "Echo Successful"};
}

int main(int argc, char **argv)
{
  if (argc < 4)
  {
    std::cerr << "Usage: " << argv[0] << "<client/server> <port> <host>" << std::endl;
    return EXIT_FAILURE;
  }

  std::string mode = argv[1];
  int port = std::stoi(argv[2]);
  std::string host = argv[3];

  if (mode == "server")
  {
    eRPC::Server server(port);
    server.bindMethod("movePlayer", movePlayer);
    server.bindMethod("echo", echo);
    server.start();
  }
  else if (mode == "client")
  {
    eRPC::Client client(host, port);
    
    client.call("echo", {"Hello", "World"});
    client.call("movePlayer", {"1", "5", "5"});
    client.call("movePlayer", {"1", "6", "6"});
    auto ret = client.call("echol", {"Goodbye", "World"});

    std::cout << "Result: " << ret << std::endl;
  }
  else
  {
    std::cerr << "Invalid mode" << std::endl;
    return EXIT_FAILURE;
  }

  // int playerId = gameState.addPlayer();

  // std::thread inputThread(inputLoop, playerId);
  // std::thread renderThread(renderLoop);

  // inputThread.join();
  // renderThread.join();

  return EXIT_SUCCESS;
}