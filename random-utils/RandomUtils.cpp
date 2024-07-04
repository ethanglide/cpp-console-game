#include "RandomUtils.hpp"

#include <time.h>

namespace RandomUtils
{
  bool seeded = false;

  void seed()
  {
    if (seeded)
    {
      return;
    }

    srand(time(NULL));
    seeded = true;
  }

  int rand(int min, int max)
  {
    seed();

    return min + std::rand() % (max - min + 1);
  }
}