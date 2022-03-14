#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <iosfwd>

#include "shape.hpp"
#include "base-types.hpp"

namespace filimonova
{

  class Rectangle : public Shape
  {
  public:
    Rectangle(double width, double height, const point_t &pos, double angle = 0.0);

    double getWidth() const;

    double getHeight() const;

    virtual point_t getPosition() const override;

    virtual double getArea() const override;

    virtual rectangle_t getFrameRect() const override;

    virtual void move(const point_t &point) override;

    virtual void move(double dX, double dY) override;

    virtual void scale(double coefficient) override;

    virtual void rotate(double angleDegree) override;

    virtual void print(std::ostream &out) const override;

  private:
    point_t points_[4];
  };

}

#endif
