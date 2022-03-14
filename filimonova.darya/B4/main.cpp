#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

#include "data-struct.hpp"

int main()
{
  std::vector<DataStruct> vector{std::istream_iterator<DataStruct>(std::cin), std::istream_iterator<DataStruct>()};

  if (std::cin.fail() && !std::cin.eof())
  {
    std::cerr << "Invalid input.\n";
    return 1;
  }

  std::sort(vector.begin(), vector.end());
  std::copy(vector.begin(), vector.end(), std::ostream_iterator<DataStruct>(std::cout, "\n"));

  return 0;
}
