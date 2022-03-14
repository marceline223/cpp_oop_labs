#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <iosfwd>
#include <memory>

struct point_t
{
  int x;
  int y;
};

class Shape
{
public:
  Shape();

  Shape(const point_t &center);

  virtual ~Shape() = default;

  bool isMoreLeft(const std::shared_ptr<Shape> &shape) const;

  bool isUpper(const std::shared_ptr<Shape> &shape) const;

  virtual void draw(std::ostream &out) const = 0;

protected:
  point_t center_;
};

#endif
