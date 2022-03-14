#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <initializer_list>
#include <iosfwd>
#include <memory>

#include "shape.hpp"
#include "base-types.hpp"

namespace filimonova
{

  class Polygon : public Shape
  {
  public:
    Polygon(const std::initializer_list<point_t> &list);

    Polygon(const Polygon &polygon);

    Polygon(Polygon &&polygon) noexcept;

    Polygon &operator=(const Polygon &polygon);

    Polygon &operator=(Polygon &&polygon) noexcept;

    point_t operator[](size_t i) const;

    size_t getSize() const;

    virtual point_t getPosition() const override;

    virtual double getArea() const override;

    virtual rectangle_t getFrameRect() const override;

    virtual void move(const point_t &point) override;

    virtual void move(double dX, double dY) override;

    virtual void scale(double coefficient) override;

    virtual void rotate(double angleDegree) override;

    virtual void print(std::ostream &out) const override;

  private:
    size_t size_;

    std::unique_ptr<point_t[]> points_;
  };

}

#endif
