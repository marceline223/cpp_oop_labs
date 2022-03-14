#include "tasks.hpp"

#include <vector>
#include <cstring>
#include <forward_list>
#include <iostream>

#include "details.hpp"

void doTask1(const char *direction)
{
  if (direction == nullptr)
  {
    throw std::invalid_argument("Invalid input in the task 1: invalid direction of sorting.\n");
  }

  std::vector<int> vector;
  int element = 0;

  while (std::cin.good() && (std::cin >> element))
  {
    vector.push_back(element);
  }  

  if (!std::cin.eof())
  {
    throw std::runtime_error("Invalid input in the task 1: invalid vector.\n");
  }

  std::vector<int> vectorCopy = vector;

  sort<IndexStrategy>(vectorCopy, makeDirection(direction));
  print(vectorCopy);

  std::forward_list<int> list(vector.begin(), vector.end());

  sort<AtStrategy>(vector, makeDirection(direction));
  print(vector);

  sort<IteratorStrategy>(list, makeDirection(direction));
  print(list);
}
