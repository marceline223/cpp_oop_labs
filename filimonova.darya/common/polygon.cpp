#include "polygon.hpp"

#include <cmath>
#include <iostream>

#include "base-types.hpp"

filimonova::Polygon::Polygon(const std::initializer_list<point_t> &list) :
    size_(list.size())
{
  if (size_ < 3)
  {
    throw std::invalid_argument("Polygon can't be initialized by 2 or less points.");
  }
  points_ = std::make_unique<point_t[]>(size_);
  size_t i = 0;
  for (const point_t *point = list.begin(); point != list.end(); point++)
  {
    points_[i] = *point;
    i++;
  }
  if (getArea() == 0)
  {
    throw std::invalid_argument("Points are on the same line.");
  }
}

filimonova::Polygon::Polygon(const filimonova::Polygon &polygon) :
    size_(polygon.size_),
    points_(std::make_unique<point_t[]>(size_))
{
  for (size_t i = 0; i < size_; i++)
  {
    points_[i] = polygon.points_[i];
  }
}

filimonova::Polygon::Polygon(filimonova::Polygon &&polygon) noexcept:
    size_(polygon.size_),
    points_(std::move(polygon.points_))
{
  polygon.size_ = 0;
}

filimonova::Polygon &filimonova::Polygon::operator=(const filimonova::Polygon &polygon)
{
  if (this == &polygon)
  {
    return *this;
  }

  points_.reset();
  size_ = polygon.size_;
  points_ = std::make_unique<point_t[]>(size_);

  for (size_t i = 0; i < size_; i++)
  {
    points_[i] = polygon.points_[i];
  }

  return *this;
}

filimonova::Polygon &filimonova::Polygon::operator=(filimonova::Polygon &&polygon) noexcept
{
  size_ = polygon.size_;

  points_.reset();
  points_ = std::move(polygon.points_);

  polygon.size_ = 0;

  return *this;
}

filimonova::point_t filimonova::Polygon::operator[](size_t i) const
{
  if (i >= size_)
  {
    throw std::out_of_range("Index " + std::to_string(i) + " is out of polygon range.");
  }
  return points_[i];
}

size_t filimonova::Polygon::getSize() const
{
  return size_;
}

filimonova::point_t filimonova::Polygon::getPosition() const
{
  double sumX = 0;
  double sumY = 0;

  for (size_t i = 0; i < size_; i++)
  {
    sumX += points_[i].x;
    sumY += points_[i].y;
  }

  return {sumX / size_, sumY / size_};
}

double filimonova::Polygon::getArea() const
{
  double area = 0;
  for (size_t i = 0; i < size_; i++)
  {
    area += points_[i].x * points_[(i + 1) % size_].y - points_[i].y * points_[(i + 1) % size_].x;
  }
  return std::abs(area / 2);
}

filimonova::rectangle_t filimonova::Polygon::getFrameRect() const
{
  double maxX = points_[0].x;
  double maxY = points_[0].y;
  double minX = points_[0].x;
  double minY = points_[0].y;

  for (size_t i = 1; i < size_; i++)
  {
    minX = std::min(minX, points_[i].x);
    minY = std::min(minY, points_[i].y);

    maxX = std::max(maxX, points_[i].x);
    maxY = std::max(maxY, points_[i].y);
  }

  return {maxX - minX, maxY - minY, {(maxX + minX) / 2, (maxY + minY) / 2}};
}

void filimonova::Polygon::move(const filimonova::point_t &point)
{
  point_t pos = getPosition();

  double dX = point.x - pos.x;
  double dY = point.y - pos.y;

  move(dX, dY);
}

void filimonova::Polygon::move(double dX, double dY)
{
  for (size_t i = 0; i < size_; i++)
  {
    points_[i].x += dX;
    points_[i].y += dY;
  }
}

void filimonova::Polygon::scale(double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument("Invalid coefficient of polygon scale: " + std::to_string(coefficient)
        + ". Coefficient can't be 0 or less.");
  }

  point_t pos = getPosition();

  for (size_t i = 0; i < size_; i++)
  {
    points_[i].x = pos.x + (points_[i].x - pos.x) * coefficient;
    points_[i].y = pos.y + (points_[i].y - pos.y) * coefficient;
  }
}

void filimonova::Polygon::rotate(double angleDegree)
{
  point_t pos = getPosition();

  double x0 = pos.x;
  double y0 = pos.y;

  double angleRad = angleDegree / 180 * M_PI;

  for (size_t i = 0; i < size_; i++)
  {
    double x = points_[i].x;
    double y = points_[i].y;

    points_[i].x = x0 + (x - x0) * cos(angleRad) - (y - y0) * sin(angleRad);
    points_[i].y = y0 + (y - y0) * cos(angleRad) + (x - x0) * sin(angleRad);
  }
}

void filimonova::Polygon::print(std::ostream &out) const
{
  out << "\nPolygon: points";
  for (size_t i = 0; i < size_; i++)
  {
    out << "\nPoint " << i + 1 << " (" << points_[i].x << ", " << points_[i].y << ").";
  }
  double area = getArea();
  out << "\nArea of polygon: " << area;
  rectangle_t frameRect = getFrameRect();
  out << "\nFrame rectangle: width " << frameRect.width << ", height " << frameRect.height << ", position ("
      << frameRect.pos.x << ", " << frameRect.pos.y << ").\n";
}
