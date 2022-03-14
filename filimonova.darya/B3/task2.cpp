#include "tasks.hpp"

#include <algorithm>
#include <iostream>

#include "factorial-container.hpp"

void doTask2()
{
  FactorialContainer container;

  std::copy(container.begin(), container.end(), std::ostream_iterator<size_t>(std::cout, " "));
  std::cout << '\n';

  std::reverse_copy(container.begin(), container.end(), std::ostream_iterator<size_t>(std::cout, " "));
  std::cout << '\n';
}
