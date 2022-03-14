#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.hpp"
#include "base-types.hpp"

class Circle : public Shape
{
public:
  Circle(const point_t &center, double radius);

  point_t getPosition() const override;

  double getRadius() const;

  double getArea() const override;

  rectangle_t getFrameRect() const override;

  void move(const point_t &point) override;

  void move(double dX, double dY) override;

private:
  point_t center_;
  double radius_;
};

#endif
