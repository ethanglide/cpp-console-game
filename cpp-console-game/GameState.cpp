#include "GameState.hpp"

#include <RandomUtils.hpp>

int idCounter = 0;

namespace ConsoleGame
{
  GameState::GameState(int width, int height, std::string fill)
      : board(width, height, fill),
        running(true),
        players() {}

  int GameState::addPlayer()
  {
    std::lock_guard<std::mutex> lock(mutex);

    // Check if the game is full
    if (players.size() >= board.getWidth() * board.getHeight())
    {
      return -1;
    }

    // Add a player to the game at a random position
    int x, y;
    do
    {
      x = RandomUtils::rand(0, board.getWidth() - 1);
      y = RandomUtils::rand(0, board.getHeight() - 1);
    } while (board.getCell(x, y) != board.getFill());

    // Increment the id counter and add the player to the map
    int id = idCounter++;
    players[id] = Player({x, y});
    board.setCell(x, y, players[id].getFill());

    return id;
  }

  void GameState::removePlayer(int id)
  {
    std::lock_guard<std::mutex> lock(mutex);

    // Replace the player's position with a regular board cell
    auto pos = players[id].getPosition();
    board.setCell(pos.first, pos.second, board.getFill());

    players.erase(id);
  }

  void GameState::movePlayer(int id, std::pair<int, int> newPos)
  {
    std::lock_guard<std::mutex> lock(mutex);

    // Check if the new position is out of bounds or occupied
    if (newPos.first < 0 ||
        newPos.first >= board.getWidth() ||
        newPos.second < 0 ||
        newPos.second >= board.getHeight() ||
        board.getCell(newPos.first, newPos.second) != board.getFill())
    {
      return;
    }

    // Replace the player's old position with a regular board cell
    auto oldPos = players[id].getPosition();
    board.setCell(oldPos.first, oldPos.second, board.getFill());

    // Update the player's position and set the new position on the board
    players[id].setPosition(newPos);
    board.setCell(newPos.first, newPos.second, players[id].getFill());
  }

  std::pair<int, int> GameState::getPlayerPosition(int id)
  {
    std::lock_guard<std::mutex> lock(mutex);

    return players[id].getPosition();
  }

  std::string GameState::draw()
  {
    std::lock_guard<std::mutex> lock(mutex);

    return board.draw();
  }

  bool GameState::isRunning()
  {
    std::lock_guard<std::mutex> lock(mutex);

    return running;
  }

  void GameState::stop()
  {
    std::lock_guard<std::mutex> lock(mutex);

    running = false;
  }
}
