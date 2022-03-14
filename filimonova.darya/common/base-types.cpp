#include "base-types.hpp"

#include <cmath>

bool filimonova::areIntersecting(const rectangle_t &rect1, const rectangle_t &rect2)
{
  return (std::abs(rect1.pos.x - rect2.pos.x) < ((rect1.width + rect2.width) / 2.0))
      && (std::abs(rect1.pos.y - rect2.pos.y) < ((rect1.height + rect2.height) / 2.0));
}
