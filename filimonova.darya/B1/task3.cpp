#include "tasks.hpp"

#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include "details.hpp"

void doTask3()
{ 
  std::vector<int> vector;
  int element = 0;

  while (std::cin.good() && (std::cin >> element) && (element != 0))
  {
    vector.push_back(element);
  }
  
  if ((std::cin.fail() && !std::cin.eof()) || (std::cin.eof() && (element != 0)))
  {
    throw std::runtime_error("Invalid input in the task 3.\n");
  }

  if (vector.empty())
  {
    return;
  }

  if (vector.back() == 1)
  {
    std::vector<int>::iterator it = vector.begin();
    while (it != vector.end())
    {
      if (*it % 2 == 0)
      {
        it = vector.erase(it);
      }
      else
      {
        it++;
      }
    }
  }
  else if (vector.back() == 2)
  {
    std::vector<int>::iterator it = vector.begin();
    while (it != vector.end())
    {
      if (*it % 3 == 0)
      {
        it = vector.insert(++it, 3, 1);
        it += 3;
      }
      else
      {
        it++;
      }
    }
  }

  print(vector);
}
