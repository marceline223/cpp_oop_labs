#include "circle.hpp"

#include <cmath>
#include <stdexcept>
#include <string>
#include <iostream>

#include "base-types.hpp"

filimonova::Circle::Circle(const point_t &center, double radius) :
    center_(center),
    radius_(radius)
{
  if (radius <= 0)
  {
    throw std::invalid_argument("Invalid parameters of circle: " + std::to_string(radius)
        + ". Radius can't be 0 or less.");
  }
}

filimonova::point_t filimonova::Circle::getPosition() const
{
  return center_;
}

double filimonova::Circle::getRadius() const
{
  return radius_;
}

double filimonova::Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

filimonova::rectangle_t filimonova::Circle::getFrameRect() const
{
  return {radius_ * 2, radius_ * 2, center_};
}

void filimonova::Circle::move(const point_t &point)
{
  center_ = point;
}

void filimonova::Circle::move(double dX, double dY)
{
  center_.x += dX;
  center_.y += dY;
}

void filimonova::Circle::scale(double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument("Invalid coefficient of circle scale: " + std::to_string(coefficient)
        + ". Coefficient can't be 0 or less.");
  }
  radius_ *= coefficient;
}

void filimonova::Circle::rotate(double)
{
}

void filimonova::Circle::print(std::ostream &out) const
{
  filimonova::point_t position = getPosition();
  filimonova::rectangle_t frameRect = getFrameRect();

  out << "\n\nCircle: position (" << position.x << ", " << position.y << "), radius " << getRadius()
      << ".\nArea of circle: " << getArea() << ".\nFrame rectangle: width " << frameRect.width
      << ", height " << frameRect.height << ", position (" << frameRect.pos.x << ", " << frameRect.pos.y << ").\n";
}
