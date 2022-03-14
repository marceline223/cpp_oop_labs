#include "details.hpp"

#include <cstring>
#include <stdexcept>

Direction makeDirection(const char *direction)
{
  if (direction == nullptr)
  {
    throw std::invalid_argument("Invalid direction of sorting.\n");
  }

  Direction dir = Direction::DESCENDING;
  if (strcmp(direction, "ascending") == 0)
  {
    dir = Direction::ASCENDING;
  }
  else if (strcmp(direction, "descending") != 0)
  {
    throw std::invalid_argument("Invalid direction of sorting.\n");
  }

  return dir;
}
