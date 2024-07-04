#include "conio.hpp"

#include <termios.h>
#include <unistd.h>
#include <iostream>

/**
 * Get a character from the console without needing to press enter
 */
char conio::getch()
{
  char c;
  struct termios oldattr, newattr;

  // Get the terminal settings
  tcgetattr(STDIN_FILENO, &oldattr);
  newattr = oldattr;

  // Disable canonical mode and echo
  newattr.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newattr);

  // Get the character, will not wait for enter because of the new settings
  std::cin.get(c);

  // Reset the terminal settings back to normal behaviour
  tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);

  return c;
}