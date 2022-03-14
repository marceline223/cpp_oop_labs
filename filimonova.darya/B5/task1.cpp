#include "tasks.hpp"

#include <iterator>
#include <iostream>
#include <string>
#include <stdexcept>
#include <set>

void doTask1()
{
  std::set<std::string> words{std::istream_iterator<std::string>(std::cin), std::istream_iterator<std::string>()};

  if ((!std::cin.eof()) && (std::cin.fail()))
  {
    throw std::runtime_error("Invalid input.\n");
  }
  
  std::copy(words.begin(), words.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
}
