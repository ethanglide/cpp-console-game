#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "Board.hpp"
#include "Player.hpp"

#include <unordered_map>
#include <string>
#include <mutex>

namespace ConsoleGame
{
  class GameState
  {
  public:
    GameState(int width, int height, std::string fill = "#");

    /**
     * Add a player to the game
     * @return New player id
     */
    int addPlayer();

    /**
     * Remove a player from the game
     * @param id Player id
     */
    void removePlayer(int id);

    /**
     * Move a player to a new position
     * @param id Player id
     * @param newPos New position of the player
     */
    void movePlayer(int id, std::pair<int, int> newPos);

    /**
     * Get the position of a player
     * @param id Player id
     * @return Player position
     */
    std::pair<int, int> getPlayerPosition(int id);

    /**
     * Draw the game board
     */
    std::string draw();

    /**
     * Check if the game is running
     * @return True if the game is running, false otherwise
     */
    bool isRunning();

    /**
     * Stop the game
     */
    void stop();

  private:
    Board board;
    std::unordered_map<int, Player> players;
    bool running = true;
    std::mutex mutex;
  };
}

#endif // GAME_STATE_HPP