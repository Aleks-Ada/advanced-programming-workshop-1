#include "random.h"

#include <cstdlib>

int pick_random_number(const int low, const int high) {
  return low + (std::rand() % (high - low + 1));
}