#ifndef SHAPE_H
#define SHAPE_H

#include <iosfwd>

namespace filimonova
{
  struct point_t;
  struct rectangle_t;

  class Shape
  {
  public:

    virtual ~Shape() = default;

    virtual point_t getPosition() const = 0;

    virtual double getArea() const = 0;

    virtual rectangle_t getFrameRect() const = 0;

    virtual void move(const point_t &point) = 0;

    virtual void move(double dX, double dY) = 0;

    virtual void scale(double coefficient) = 0;

    virtual void rotate(double angleDegree) = 0;

    virtual void print(std::ostream &out) const = 0;

  };
}

#endif
