#include <algorithm>
#include <iostream>
#include <iterator>
#include <stdexcept>

#include "functor.hpp"

int main()
{
  try
  {
    Functor functor = for_each(std::istream_iterator<int>(std::cin), std::istream_iterator<int>(), Functor());
    if (!std::cin.eof() && std::cin.fail())
    {
      throw std::runtime_error("Invalid input");
    }
    functor.printStatistic(std::cout);
  }
  catch (const std::runtime_error& exception)
  {
    std::cerr << exception.what();
    return 1;
  }
  return 0;
}
