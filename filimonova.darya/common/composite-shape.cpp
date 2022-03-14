#include "composite-shape.hpp"

#include <memory>
#include <stdexcept>
#include <algorithm>
#include <cmath>
#include <iostream>

#include "base-types.hpp"
#include "shape.hpp"

filimonova::CompositeShape::CompositeShape() :
    array_(nullptr),
    size_(0)
{
}

filimonova::CompositeShape::CompositeShape(const filimonova::CompositeShape &compositeShape) :
    array_(std::make_unique<std::shared_ptr<Shape>[]>(compositeShape.size_)),
    size_(compositeShape.size_)
{
  if (!compositeShape.getSize())
  {
    throw std::invalid_argument("Invalid shape: composite shape can't be initialized with null composite shape.");
  }

  for (size_t i = 0; i < size_; i++)
  {
    array_[i] = compositeShape.array_[i];
  }
}

filimonova::CompositeShape::CompositeShape(CompositeShape &&compositeShape) noexcept:
    array_(std::move(compositeShape.array_)),
    size_(compositeShape.size_)
{
  compositeShape.size_ = 0;
}

filimonova::CompositeShape &filimonova::CompositeShape::operator=(const CompositeShape &compositeShape)
{
  if (this == &compositeShape)
  {
    return *this;
  }

  array_.reset();
  size_ = compositeShape.size_;
  array_ = std::make_unique<std::shared_ptr<Shape>[]>(size_);

  for (size_t i = 0; i < size_; i++)
  {
    array_[i] = compositeShape.array_[i];
  }

  return *this;
}

filimonova::CompositeShape &filimonova::CompositeShape::operator=(CompositeShape &&compositeShape)
{
  size_ = compositeShape.size_;

  array_.reset();
  array_ = std::move(compositeShape.array_);

  compositeShape.size_ = 0;

  return *this;
}

std::shared_ptr<filimonova::Shape> filimonova::CompositeShape::operator[](size_t i)
{
  if (i >= size_)
  {
    throw std::out_of_range("Index " + std::to_string(i) + " is out of composite shape range.");
  }
  return array_[i];
}

std::shared_ptr<const filimonova::Shape> filimonova::CompositeShape::operator[](size_t i) const
{
  if (i >= size_)
  {
    throw std::out_of_range("Index " + std::to_string(i) + " is out of composite shape range.");
  }
  return array_[i];
}

filimonova::point_t filimonova::CompositeShape::getPosition() const
{
  return getFrameRect().pos;
}

double filimonova::CompositeShape::getArea() const
{
  double area = 0;

  for (size_t i = 0; i < size_; i++)
  {
    area += array_[i]->getArea();
  }

  return area;
}

filimonova::rectangle_t filimonova::CompositeShape::getFrameRect() const
{
  double minX = 0;
  double maxX = 0;
  double minY = 0;
  double maxY = 0;

  size_t i = 0;

  for (i = 0; i < size_; i++)
  {
    filimonova::rectangle_t frameRect = array_[i]->getFrameRect();

    if ((frameRect.width >= 0) && (frameRect.height >= 0))
    {
      minX = frameRect.pos.x - frameRect.width / 2.0;
      minY = frameRect.pos.y - frameRect.height / 2.0;
      maxX = frameRect.pos.x + frameRect.width / 2.0;
      maxY = frameRect.pos.y + frameRect.height / 2.0;

      break;
    }
  }

  if (i == size_)
  {
    return filimonova::rectangle_t{-1, -1, {0.0, 0.0}};
  }

  for (size_t j = i + 1; j < size_; j++)
  {
    filimonova::rectangle_t frameRect = array_[j]->getFrameRect();

    if ((frameRect.width >= 0) && (frameRect.height >= 0))
    {
      minX = std::min(frameRect.pos.x - frameRect.width / 2.0, minX);
      minY = std::min(frameRect.pos.y - frameRect.height / 2.0, minY);
      maxX = std::max(frameRect.pos.x + frameRect.width / 2.0, maxX);
      maxY = std::max(frameRect.pos.y + frameRect.height / 2.0, maxY);
    }
  }

  return {maxX - minX, maxY - minY, {(minX + maxX) / 2.0, (minY + maxY) / 2.0}};
}

size_t filimonova::CompositeShape::getSize() const
{
  return size_;
}

void filimonova::CompositeShape::add(const std::shared_ptr<Shape> &shape)
{
  if (!shape)
  {
    throw std::invalid_argument("Invalid shape: null pointer can't be added to composite shape.");
  }

  if (this == shape.get())
  {
    throw std::invalid_argument("Invalid shape: the shape can't be added to itself.");
  }

  std::unique_ptr<std::shared_ptr<Shape>[]> arrayCopy = std::make_unique<std::shared_ptr<Shape>[]>(++size_);
  arrayCopy.swap(array_);

  for (size_t i = 0; i < size_ - 1; i++)
  {
    array_[i] = arrayCopy[i];
  }

  array_[size_ - 1] = shape;
}

void filimonova::CompositeShape::remove(size_t i)
{
  if (i >= size_)
  {
    throw std::out_of_range("Index " + std::to_string(i) + " is out of composite shape range.");
  }

  std::unique_ptr<std::shared_ptr<Shape>[]> arrayCopy = std::make_unique<std::shared_ptr<Shape>[]>(--size_);
  arrayCopy.swap(array_);

  for (size_t j = 0; j <= size_; j++)
  {
    if (j < i)
    {
      array_[j] = arrayCopy[j];
    }
    else if (j > i)
    {
      array_[j - 1] = arrayCopy[j];
    }
  }
}

void filimonova::CompositeShape::move(const point_t &point)
{
  filimonova::point_t position = getPosition();

  move(point.x - position.x, point.y - position.y);
}

void filimonova::CompositeShape::move(double dX, double dY)
{
  if (!size_)
  {
    throw std::domain_error("Composite shape is empty and can't be moved.");
  }

  for (size_t i = 0; i < size_; i++)
  {
    array_[i]->move(dX, dY);
  }
}

void filimonova::CompositeShape::scale(double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument("Invalid coefficient of composite shape scale: " + std::to_string(coefficient)
        + ". Coefficient can't be 0 or less.");
  }

  point_t positionOfCompositeShape = getPosition();

  for (size_t i = 0; i < size_; i++)
  {
    point_t positionOfFigure = array_[i]->getPosition();

    array_[i]->move({(positionOfFigure.x - positionOfCompositeShape.x) * coefficient + positionOfCompositeShape.x,
        (positionOfFigure.y - positionOfCompositeShape.y) * coefficient + positionOfCompositeShape.y});

    array_[i]->scale(coefficient);
  }
}

void filimonova::CompositeShape::rotate(double angleDegree)
{
  double x0 = getPosition().x;
  double y0 = getPosition().y;

  double angleRad = angleDegree / 180 * M_PI;

  for (size_t i=0; i<getSize(); i++)
  {
    double x = array_[i]->getPosition().x;
    double y = array_[i]->getPosition().y;

    double newX = x0 + (x - x0) * cos(angleRad) - (y - y0) * sin(angleRad);
    double newY = y0 + (y - y0) * cos(angleRad) + (x - x0) * sin(angleRad);

    array_[i]->move({newX,newY});
    array_[i]->rotate(angleDegree);
  }
}

void filimonova::CompositeShape::print(std::ostream &out) const
{
  out << "\n\nComposite shape: \n";

  filimonova::point_t position = getPosition();

  out << "\nPosition: (" << position.x << ", " << position.y << ").\nArea: " << getArea() << "\n";

  for (size_t i = 0; i < size_; i++)
  {
    out << "\nFigure " << i + 1 << ":";
    array_[i]->print(out);
  }
}
