#ifndef GAME_CLIENT_HPP
#define GAME_CLIENT_HPP

#include <Client.hpp>

namespace ConsoleGame
{
  class GameClient
  {
  public:
    /**
     * Create and start new game client. This is a blocking call.
     */
    GameClient(std::string host, int port);

  private:
    eRPC::Client client;
    int playerId;
    bool running = true;

    void renderLoop();
    void inputLoop();

    int addPlayer();
    void removePlayer();
  };
}

#endif // GAME_CLIENT_HPP