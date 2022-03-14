#include "figures.hpp"

#include <iostream>

Circle::Circle() :
  Shape()
{ }

Circle::Circle(const point_t& center) :
  Shape(center)
{ }

void Circle::draw(std::ostream &out) const
{
  out << "CIRCLE (" << center_.x << ";" << center_.y << ")" << '\n';
}

Triangle::Triangle() :
  Shape()
{ }

Triangle::Triangle(const point_t& center) :
  Shape(center)
{ }

void Triangle::draw(std::ostream &out) const
{
  out << "TRIANGLE (" << center_.x << ";" << center_.y << ")" << '\n';
}

Square::Square() :
  Shape()
{ }

Square::Square(const point_t& center) :
  Shape(center)
{ }

void Square::draw(std::ostream &out) const
{
  out << "SQUARE (" << center_.x << ";" << center_.y << ")" << '\n';
}
