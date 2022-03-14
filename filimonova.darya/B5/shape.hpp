#ifndef SHAPE
#define SHAPE

#include <iostream>
#include <vector>

struct Point
{
  int x, y;
};

double getDistance(const Point& point1, const Point& point2);

enum struct ShapeType
{
  TRIANGLE,
  SQUARE,
  RECTANGLE,
  ANOTHER
};

struct Shape
{
  std::vector<Point> points;
  ShapeType type;
};

std::istream &operator>>(std::istream &in, Point &point);
std::istream &operator>>(std::istream &in, Shape &shape);
std::ostream &operator<<(std::ostream &out, const Point &point);
std::ostream &operator<<(std::ostream &out, const Shape &shape);
bool operator<(const Shape& first, const Shape& second);

bool isTriangle(const Shape& shape);
bool isRectangle(const Shape& shape);
bool isSquare(const Shape& shape);

ShapeType getTypeOfShape(const Shape& shape);
void setTypeOfShape(Shape& shape);

#endif
