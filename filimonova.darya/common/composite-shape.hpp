#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include <memory>
#include <iosfwd>

#include "base-types.hpp"
#include "shape.hpp"

namespace filimonova
{
  class CompositeShape : public Shape
  {
  public:

    CompositeShape();

    CompositeShape(const CompositeShape &compositeShape);

    CompositeShape(CompositeShape &&compositeShape) noexcept;

    ~CompositeShape() = default;

    CompositeShape &operator=(const CompositeShape &compositeShape);

    CompositeShape &operator=(CompositeShape &&compositeShape);

    std::shared_ptr<Shape> operator[](size_t i);

    std::shared_ptr<const Shape> operator[](size_t i) const;

    virtual point_t getPosition() const override;

    virtual double getArea() const override;

    virtual rectangle_t getFrameRect() const override;

    size_t getSize() const;

    void add(const std::shared_ptr<Shape> &shape);

    void remove(size_t i);

    virtual void move(const point_t &point) override;

    virtual void move(double dX, double dY) override;

    virtual void scale(double coefficient) override;

    virtual void rotate(double angleDegree) override;

    virtual void print(std::ostream &out) const override;

  private:

    std::unique_ptr<std::shared_ptr<Shape>[]> array_;

    size_t size_;

  };
}

#endif
