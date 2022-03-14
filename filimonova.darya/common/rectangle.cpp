#include "rectangle.hpp"

#include <stdexcept>
#include <string>
#include <iostream>
#include <cmath>
#include <algorithm>

#include "base-types.hpp"

filimonova::Rectangle::Rectangle(double width, double height, const point_t &pos, double angle)
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

  points_[0] = point_t{pos.x - width / 2, pos.y - height / 2};
  points_[1] = point_t{pos.x - width / 2, pos.y + height / 2};
  points_[2] = point_t{pos.x + width / 2, pos.y + height / 2};
  points_[3] = point_t{pos.x + width / 2, pos.y - height / 2};

  if (angle != 0.0)
  {
    rotate(angle);
  }
}

double filimonova::Rectangle::getWidth() const
{
  double x1 = points_[1].x;
  double x2 = points_[2].x;

  double y1 = points_[1].y;
  double y2 = points_[2].y;

  return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

double filimonova::Rectangle::getHeight() const
{
  double x0 = points_[0].x;
  double x1 = points_[1].x;

  double y0 = points_[0].y;
  double y1 = points_[1].y;

  return sqrt((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0));
}

filimonova::point_t filimonova::Rectangle::getPosition() const
{
  double minX = std::min({points_[0].x, points_[1].x, points_[2].x, points_[3].x});
  double minY = std::min({points_[0].y, points_[1].y, points_[2].y, points_[3].y});
  double maxX = std::max({points_[0].x, points_[1].x, points_[2].x, points_[3].x});
  double maxY = std::max({points_[0].y, points_[1].y, points_[2].y, points_[3].y});

  return {minX + (maxX - minX) / 2, minY + (maxY - minY) / 2};
}

double filimonova::Rectangle::getArea() const
{
  return getWidth() * getHeight();
}

filimonova::rectangle_t filimonova::Rectangle::getFrameRect() const
{
  double minX = std::min({points_[0].x, points_[1].x, points_[2].x, points_[3].x});
  double minY = std::min({points_[0].y, points_[1].y, points_[2].y, points_[3].y});
  double maxX = std::max({points_[0].x, points_[1].x, points_[2].x, points_[3].x});
  double maxY = std::max({points_[0].y, points_[1].y, points_[2].y, points_[3].y});

  return {maxX - minX, maxY - minY, getPosition()};
}

void filimonova::Rectangle::move(const point_t &point)
{
  point_t pos = getPosition();

  double dX = point.x - pos.x;
  double dY = point.y - pos.y;

  move(dX, dY);
}

void filimonova::Rectangle::move(double dX, double dY)
{
  for (size_t i = 0; i < 4; i++)
  {
    points_[i].x += dX;
    points_[i].y += dY;
  }
}

void filimonova::Rectangle::scale(double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument("Invalid coefficient of rectangle scale: " + std::to_string(coefficient)
        + ". Coefficient can't be 0 or less.");
  }

  double width = getWidth();
  double height = getHeight();
  point_t pos = getPosition();

  height *= coefficient;
  width *= coefficient;

  points_[0] = point_t{pos.x - width / 2, pos.y - height / 2};
  points_[1] = point_t{pos.x - width / 2, pos.y + height / 2};
  points_[2] = point_t{pos.x + width / 2, pos.y + height / 2};
  points_[3] = point_t{pos.x + width / 2, pos.y - height / 2};
}

void filimonova::Rectangle::rotate(double angleDegree)
{
  point_t pos = getPosition();

  double x0 = pos.x;
  double y0 = pos.y;

  double angleRad = angleDegree / 180 * M_PI;

  for (size_t i = 0; i < 4; i++)
  {
    double x = points_[i].x;
    double y = points_[i].y;

    points_[i].x = x0 + (x - x0) * cos(angleRad) - (y - y0) * sin(angleRad);
    points_[i].y = y0 + (y - y0) * cos(angleRad) + (x - x0) * sin(angleRad);
  }
}

void filimonova::Rectangle::print(std::ostream &out) const
{
  filimonova::point_t position = getPosition();
  filimonova::rectangle_t frameRect = getFrameRect();

  out << "\n\nRectangle: width " << getWidth() << ", height " << getHeight() << ", position ("
      << position.x << ", " << position.y << "). \nVertices: A (" << points_[0].x << ", " << points_[0].y << "), B ("
      << points_[1].x << ", " << points_[1].y << "), C (" << points_[2].x << ", " << points_[2].y << "), D ("
      << points_[3].x << ", " << points_[3].y << "). \nArea of rectangle: " << getArea()
      << ".\nFrame rectangle: width " << frameRect.width << ", height " << frameRect.height << ", position ("
      << frameRect.pos.x << ", " << frameRect.pos.y << ").\n";
}
