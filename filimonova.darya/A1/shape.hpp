#ifndef SHAPE_H
#define SHAPE_H

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

};

#endif
