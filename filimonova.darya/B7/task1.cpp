#include "tasks.hpp"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <list>

#include "multiplyfunctor.hpp"

void doTask1()
{
  std::list<double> numList{std::istream_iterator<double>(std::cin), std::istream_iterator<double>()};

  if (!std::cin.eof())
  {
    throw std::invalid_argument("Invalid input");
  }

  std::for_each(numList.begin(), numList.end(), MultiplyFunctor(M_PI));
  std::copy(numList.begin(), numList.end(), std::ostream_iterator<double>(std::cout, " "));
}
