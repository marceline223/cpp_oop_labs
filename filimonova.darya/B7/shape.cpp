#include "shape.hpp"

#include <iostream>
#include <sstream>
#include <string>

Shape::Shape() :
  center_{0, 0}
{
}

Shape::Shape(const point_t& center):
  center_(center)
{
}

bool Shape::isMoreLeft(const std::shared_ptr<Shape> &shape) const
{
  return (center_.x < shape->center_.x);
}
bool Shape::isUpper(const std::shared_ptr<Shape> &shape) const
{
  return (center_.y > shape->center_.y);
}
