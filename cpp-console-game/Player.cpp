#include "Player.hpp"

#include <string>
#include <RandomUtils.hpp>

namespace ConsoleGame
{
  int colors[] = {
    31, // Red
    32, // Green
    33, // Yellow
    36, // Cyan
  };

  Player::Player() : pos({0, 0})
  {
    fill = "\033[32m@\033[0m";
  }

  Player::Player(std::pair<int, int> pos) : pos(pos)
  {
    // Set the fill color to a random color
    int color = colors[RandomUtils::rand(0, sizeof(colors) / sizeof(colors[0]) - 1)];
    fill = "\033[" + std::to_string(color) + "m@\033[0m";
  }

  std::pair<int, int> Player::getPosition()
  {
    return pos;
  }

  std::string Player::getFill()
  {
    return fill;
  }

  void Player::setPosition(std::pair<int, int> newPos)
  {
    pos = newPos;
  }
}