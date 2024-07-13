#include "GameClient.hpp"

#include <thread>
#include <iostream>
#include <conio.hpp>
#include <algorithm>

namespace ConsoleGame
{
  GameClient::GameClient(std::string host, int port) : client(host, port)
  {
    playerId = addPlayer();

    if (playerId == -1)
    {
      std::cerr << "Failed to add player" << std::endl;
      return;
    }

    std::thread renderThread(&GameClient::renderLoop, this);
    std::thread inputThread(&GameClient::inputLoop, this);

    renderThread.join();
    inputThread.join();
  }

  void GameClient::renderLoop()
  {
    std::cout << "\033[2J"; // Clear the screen

    while (running)
    {
      auto res = client.call("draw", {});

      // replace all "|" with newline
      std::replace(res.begin(), res.end(), '|', '\n');

      std::cout << "\033[H" << res << std::endl;

      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
  }

  void GameClient::inputLoop()
  {
    while (running)
    {
      char input = conio::getch();
      client.call("handleInput", {std::to_string(playerId), std::string(1, input)});

      if (input == 'q')
      {
        running = false;
      }
    }
  }

  int GameClient::addPlayer()
  {
    auto res = client.call("addPlayer", {});
    return std::stoi(res);
  }

  void GameClient::removePlayer()
  {
    client.call("removePlayer", {std::to_string(playerId)});
  }
}