#ifndef FIGURES_HPP
#define FIGURES_HPP

#include <iosfwd>
#include "shape.hpp"

class Circle : public Shape
{
public:

  Circle();

  Circle(const point_t& center);

  void draw(std::ostream &out) const override;
};

class Triangle : public Shape
{
public:

  Triangle();

  Triangle(const point_t& center);

  void draw(std::ostream &out) const override;
};

class Square : public Shape
{
public:

  Square();

  Square(const point_t& center);

  void draw(std::ostream &out) const override;
};

#endif
