#include "tasks.hpp"

#include <cstring>
#include <random>
#include <vector>

#include "details.hpp"

static void fillRandom(double *array, int size)
{
  static std::random_device rd;
  std::default_random_engine gen(rd());
  std::uniform_real_distribution<double> dist(-1.0, 1.0);

  for (int i = 0; i < size; i++)
  {
    array[i] = dist(gen);
  }
}

void doTask4(const char *direction, int size)
{
  Direction dir = makeDirection(direction);

  if (size < 1)
  {
    throw std::invalid_argument("Invalid input in the task 4: size can't be 0 or less.\n");
  }

  std::vector<double> vector(size);
  
  fillRandom(&vector[0], size);
  print(vector);

  sort<IndexStrategy>(vector, dir);
  print(vector);
}
