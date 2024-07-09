#ifndef GAME_SERVER_HPP
#define GAME_SERVER_HPP

#include "GameState.hpp"
#include <Server.hpp>

namespace ConsoleGame
{
  class GameServer
  {
  public:
    /**
     * Create and start new game server. This is a blocking call.
     */
    GameServer(int port, int width, int height, std::string fill = "#");

  private:
    GameState state;
    eRPC::Server server;

    void handleInput(int playerId, char input);

    // RPC method bindings

    std::pair<bool, std::string> rpc_handleInput(std::vector<std::string> args);
    std::pair<bool, std::string> rpc_draw(std::vector<std::string> args);
    std::pair<bool, std::string> rpc_addPlayer(std::vector<std::string> args);
    std::pair<bool, std::string> rpc_removePlayer(std::vector<std::string> args);
  };
}

#endif // GAME_SERVER_HPP