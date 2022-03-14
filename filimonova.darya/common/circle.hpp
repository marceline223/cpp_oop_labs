#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include <iosfwd>

#include "shape.hpp"
#include "base-types.hpp"

namespace filimonova
{

  class Circle : public Shape
  {

  public:

    Circle(const point_t &center, double radius);

    virtual point_t getPosition() const override;

    double getRadius() const;

    virtual double getArea() const override;

    virtual rectangle_t getFrameRect() const override;

    virtual void move(const point_t &point) override;

    virtual void move(double dX, double dY) override;

    virtual void scale(double coefficient) override;

    virtual void rotate(double angle) override;

    virtual void print(std::ostream &out) const override;

  private:

    point_t center_;

    double radius_;

  };

}

#endif
