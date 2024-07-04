#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <cstdlib>

namespace RandomUtils
{
  /**
   * Generates a random number between min and max (inclusive).
   */
  int rand(int min = 0, int max = RAND_MAX);
}

#endif // RANDOM_HPP