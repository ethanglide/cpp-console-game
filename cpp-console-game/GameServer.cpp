#include "GameServer.hpp"

namespace ConsoleGame
{
  GameServer::GameServer(int port, int width, int height, std::string fill) : server(port), state(width, height, fill)
  {
    server.bindMethod("handleInput", std::bind(&GameServer::rpc_handleInput, this, std::placeholders::_1));
    server.bindMethod("draw", std::bind(&GameServer::rpc_draw, this, std::placeholders::_1));
    server.bindMethod("addPlayer", std::bind(&GameServer::rpc_addPlayer, this, std::placeholders::_1));
    server.bindMethod("removePlayer", std::bind(&GameServer::rpc_removePlayer, this, std::placeholders::_1));

    server.start();
  }

  void GameServer::handleInput(int playerId, char input)
  {
    std::pair<int, int> playerPos = state.getPlayerPosition(playerId);

    switch (input)
    {
    case 'w':
      playerPos.second--;
      break;
    case 's':
      playerPos.second++;
      break;
    case 'a':
      playerPos.first--;
      break;
    case 'd':
      playerPos.first++;
      break;
    case 'q':
      state.removePlayer(playerId);
      return;
    default:
      return;
    }

    state.movePlayer(playerId, playerPos);
  }

  std::pair<bool, std::string> GameServer::rpc_handleInput(std::vector<std::string> args)
  {
    if (args.size() != 2)
    {
      return {false, "Invalid number of arguments"};
    }

    int playerId = std::stoi(args[0]);
    char input = args[1][0];

    handleInput(playerId, input);

    return {true, ""};
  }

  std::pair<bool, std::string> GameServer::rpc_draw(std::vector<std::string> args)
  {
    return {true, state.draw()};
  }

  std::pair<bool, std::string> GameServer::rpc_addPlayer(std::vector<std::string> args)
  {
    return {true, std::to_string(state.addPlayer())};
  }

  std::pair<bool, std::string> GameServer::rpc_removePlayer(std::vector<std::string> args)
  {
    if (args.size() != 1)
    {
      return {false, "Invalid number of arguments"};
    }

    state.removePlayer(std::stoi(args[0]));

    return {true, ""};
  }
}