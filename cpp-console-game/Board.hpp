#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <string>

namespace ConsoleGame
{
  class Board
  {
  public:
    /**
     * Construct a new Board object
     * @param width The width of the board
     * @param height The height of the board
     * @param fill The string to fill the board with
     */
    Board(int width, int height, std::string fill = "#");
    void draw();
    void setCell(int x, int y, std::string value);
    std::string getCell(int x, int y);
    int getWidth();
    int getHeight();
    std::string getFill();

  private:
    std::vector<std::vector<std::string>> cells;
    std::string fill;
  };
}

#endif // BOARD_HPP