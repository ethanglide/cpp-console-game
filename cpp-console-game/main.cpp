#include "GameState.hpp"

#include <unistd.h>
#include <thread>
#include <conio.hpp>

ConsoleGame::GameState gameState(20, 10);

void inputLoop(int playerId)
{
  while (gameState.isRunning())
  {
    char c = conio::getch();
    auto position = gameState.getPlayerPosition(playerId);

    switch (c)
    {
    case 'w':
      gameState.movePlayer(playerId, {position.first, position.second - 1});
      break;
    case 'a':
      gameState.movePlayer(playerId, {position.first - 1, position.second});
      break;
    case 's':
      gameState.movePlayer(playerId, {position.first, position.second + 1});
      break;
    case 'd':
      gameState.movePlayer(playerId, {position.first + 1, position.second});
      break;
    case 'q':
      gameState.stop();
      break;
    case 'p':
      gameState.addPlayer();
      break;
    }
  }
}

void renderLoop()
{
  while (gameState.isRunning())
  {
    gameState.draw();
    usleep(100000); // Sleep for 100ms
  }
}

int main()
{
  int playerId = gameState.addPlayer();

  std::thread inputThread(inputLoop, playerId);
  std::thread renderThread(renderLoop);

  inputThread.join();
  renderThread.join();

  return 0;
}