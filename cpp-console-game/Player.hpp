#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>

namespace ConsoleGame
{
  class Player
  {
  public:
    Player(); // TODO - Get rid of this constructor while keeping the compiler happy
    Player(std::pair<int, int> pos);

    std::pair<int, int> getPosition();
    std::string getFill();

    void setPosition(std::pair<int, int> newPos);

  private:
    std::pair<int, int> pos;
    std::string fill;
  };
}

#endif // PLAYER_HPP