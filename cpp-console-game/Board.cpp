#include "Board.hpp"

#include <iostream>

namespace ConsoleGame
{
  Board::Board(int width, int height, std::string fill) : fill(fill)
  {
    cells.resize(height);
    for (int i = 0; i < height; i++)
    {
      cells[i].resize(width, fill);
    }
  }

  void Board::draw()
  {
    std::cout << "\033[H";  // Move cursor to the top left corner

    for (auto row : cells)
    {
      for (auto cell : row)
      {
        std::cout << cell;
      }
      std::cout << std::endl;
    }
  }

  void Board::setCell(int x, int y, std::string value)
  {
    cells[y][x] = value;
  }

  std::string Board::getCell(int x, int y)
  {
    return cells[y][x];
  }

  int Board::getWidth()
  {
    return cells[0].size();
  }

  int Board::getHeight()
  {
    return cells.size();
  }

  std::string Board::getFill()
  {
    return fill;
  }
}