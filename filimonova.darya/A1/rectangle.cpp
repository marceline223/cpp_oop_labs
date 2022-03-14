#include "rectangle.hpp"
#include <stdexcept>
#include <string>
#include "base-types.hpp"

Rectangle::Rectangle(double width, double height, const point_t &pos) :
  rect_{width, height, pos}
{
  if (width <= 0)
  {
    throw std::invalid_argument("Invalid parameters of rectangle: " + std::to_string(width)
        + ". Width can't be 0 or less.");
  }
  if (height <= 0)
  {
    throw std::invalid_argument("Invalid parameters of rectangle: " + std::to_string(height)
        + ". Height can't be 0 or less.");
  }
}

double Rectangle::getWidth() const
{
  return rect_.width;
}

double Rectangle::getHeight() const
{
  return rect_.height;
}

point_t Rectangle::getPosition() const
{
  return rect_.pos;
}

double Rectangle::getArea() const
{
  return rect_.width * rect_.height;
}

rectangle_t Rectangle::getFrameRect() const
{
  return rect_;
}

void Rectangle::move(const point_t &point)
{
  rect_.pos = point;
}

void Rectangle::move(double dX, double dY)
{
  rect_.pos.x += dX;
  rect_.pos.y += dY;
}
