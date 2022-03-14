#include "shape.hpp"

#include <cmath>
#include <iterator>
#include <sstream>

#include "guard.hpp"

double getDistance(const Point &point1, const Point &point2)
{
  return sqrt(pow(point2.x - point1.x, 2) + pow(point2.y - point1.y, 2));
}

std::ostream &operator<<(std::ostream &out, const Point &point)
{
  out << '(' << point.x << ';' << point.y << ')';

  return out;
}

std::ostream &operator<<(std::ostream &out, const Shape &shape)
{
  out << shape.points.size() << ' ';

  for (unsigned int i = 0; i < shape.points.size(); i++)
  {
    out << shape.points[i] << ' ';
  }

  return out;
}

std::istream &operator>>(std::istream &in, Point &point)
{
  Guard guard(in);
  in >> std::noskipws;

  char ch = 0;
  if (!(in >> ignoreBlanks >> ch) || (ch != '('))
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  int x = 0;
  if (!(in >> ignoreBlanks >> x))
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  if (!(in >> ignoreBlanks >> ch) || (ch != ';'))
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  int y = 0;
  if (!(in >> ignoreBlanks >> y))
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  if (!(in >> ignoreBlanks >> ch) || (ch != ')'))
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  point = {x, y};
  return in;
}

std::istream &operator>>(std::istream &in, Shape &shape)
{
  size_t vertices = 0;
  in >> vertices;

  std::string str = "";
  std::getline(in, str);

  std::istringstream iss(str);

  Shape tempShape = {{std::istream_iterator<Point>(iss), std::istream_iterator<Point>()}, ShapeType::ANOTHER};

  if ((tempShape.points.size() < 3) || (tempShape.points.size() != vertices))
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  std::swap(shape, tempShape);
  setTypeOfShape(shape);
  
  return in;
}

bool isTriangle(const Shape &shape)
{
  return (shape.points.size() == 3);
}

bool isRectangle(const Shape &shape)
{
  if (shape.points.size() == 4)
  {
    return (getDistance(shape.points[0], shape.points[1]) == getDistance(shape.points[2], shape.points[3])) && 
    (getDistance(shape.points[0], shape.points[3]) == getDistance(shape.points[1], shape.points[2]));
  }
  return false;
}

bool isSquare(const Shape &shape)
{
  if (!isRectangle(shape))
  {
    return false;
  }
  return (getDistance(shape.points[0], shape.points[1]) == getDistance(shape.points[1], shape.points[2]));
}

ShapeType getTypeOfShape(const Shape& shape)
{
  if (isTriangle(shape))
  {
    return ShapeType::TRIANGLE;
  }

  if (isRectangle(shape))
  {
    if (isSquare(shape))
    {
      return ShapeType::SQUARE;
    }
    return ShapeType::RECTANGLE;
  }

  return ShapeType::ANOTHER;
}

void setTypeOfShape(Shape& shape)
{
  shape.type = getTypeOfShape(shape);
}

bool operator<(const Shape& first, const Shape& second)
{
  return first.type < second.type;
}

