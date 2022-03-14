#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.hpp"
#include "base-types.hpp"

class Rectangle : public Shape
{
public:
  Rectangle(double width, double height, const point_t &pos);

  double getWidth() const;

  double getHeight() const;

  point_t getPosition() const override;

  double getArea() const override;

  rectangle_t getFrameRect() const override;

  void move(const point_t &point) override;

  void move(double dX, double dY) override;

private:
  rectangle_t rect_;
};

#endif
