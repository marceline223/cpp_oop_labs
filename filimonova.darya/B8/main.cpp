#include <iostream>
#include <cstring>
#include <stdexcept>

#include "text-handler.hpp"

const int MIN_WIDTH = 25;

int main(int argc, char** argv)
{
  try
  {
    if ((argc > 3) || (argc == 2))
    {
      throw std::invalid_argument("Invalid arguments amount\n");
    }

    size_t width = 40;

    if (argc == 3)
    {
      if (std::string(argv[1]) != "--line-width")
      {
        throw std::invalid_argument("Invalid arguments\n");
      }

      width = std::stoul(argv[2]);
      if (width < MIN_WIDTH)
      {
        throw std::invalid_argument("Invalid width. It can't be less than 25\n");
      }
    }

    TextHandler text(width);
    text.read();
    text.print();
  }
  catch (const std::exception& exc)
  {
    std::cerr << exc.what() << '\n';
    return 1;
  }

  return 0;
}
