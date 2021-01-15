#include "random.h"

#include <random>

std::mt19937 random_number_generator((std::random_device())());

int pick_random_number(const int low, const int high) {
  std::uniform_int_distribution<int> dist(low, high);
  return dist(random_number_generator);
}