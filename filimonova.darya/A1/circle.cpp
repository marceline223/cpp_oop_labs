#include "circle.hpp"
#include <cmath>
#include <stdexcept>
#include <string>
#include "base-types.hpp"

Circle::Circle(const point_t &center, double radius) :
  center_(center),
  radius_(radius)
{
  if (radius <= 0)
  {
    throw std::invalid_argument(std::string("Invalid parameters of circle: " + std::to_string(radius)
        + ". Radius can't be 0 or less."));
  }
}

point_t Circle::getPosition() const
{
  return center_;
}

double Circle::getRadius() const
{
  return radius_;
}

double Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

rectangle_t Circle::getFrameRect() const
{
  return {radius_ * 2, radius_ * 2, center_};
}

void Circle::move(const point_t &point)
{
  center_ = point;
}

void Circle::move(double dX, double dY)
{
  center_.x += dX;
  center_.y += dY;
}
