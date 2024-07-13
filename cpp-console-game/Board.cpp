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

  std::string Board::draw()
  {
    std::string board;

    for (auto row : cells)
    {
      for (auto cell : row)
      {
        board += cell;
      }
      board += "|";
    }

    return board;
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