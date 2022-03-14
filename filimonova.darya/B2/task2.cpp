#include "tasks.hpp"

#include <iostream>
#include <list>

static void printList(const std::list<int> &list);

void doTask2()
{
  std::list<int> list;

  int element = 0;
  while (std::cin >> element)
  {
    if (list.size() == 20)
    {
      throw std::runtime_error("Invalid input in the task 2: it can't be more than 20 elements.\n");
    }
    if ((element >= 1) && (element <= 20))
    {
      list.push_back(element);
    }
    else
    {
      throw std::invalid_argument("Invalid input in the task 2: element mast be in [1, 20].\n");
    }
  }
  if (!std::cin.eof())
  {
    throw std::runtime_error("Invalid input in the task 2.\n");
  }

  printList(list);
}

static void printList(const std::list<int> &list)
{
  if (list.empty())
  {
    return;
  }
  std::list<int>::const_iterator left = list.cbegin();
  std::list<int>::const_iterator right = list.cend();

  while (left != right)
  {
    std::cout << *left << ' ';
    right--;
    if (left != right)
    {
      std::cout << *right << ' ';
      left++;
    }
  }
  std::cout << '\n';
}
