#include "matrix.hpp"

#include <iostream>
#include <stdexcept>
#include <cmath>

#include "shape.hpp"
#include "base-types.hpp"

filimonova::Matrix::Layer::Layer(std::shared_ptr<Shape> *shape, size_t size) :
    size_(size),
    layer_(shape)
{
}

std::shared_ptr<filimonova::Shape> filimonova::Matrix::Layer::operator[](size_t i)
{
  if (!layer_)
  {
    throw std::out_of_range("This layer is nullptr.");
  }

  if (i >= size_)
  {
    throw std::out_of_range("Index " + std::to_string(i) + "is out of layer range.");
  }
  return layer_[i];
}

std::shared_ptr<const filimonova::Shape> filimonova::Matrix::Layer::operator[](size_t i) const
{
  if (i >= size_)
  {
    throw std::out_of_range("Index " + std::to_string(i) + "is out of layer range.");
  }
  return layer_[i];
}

filimonova::Matrix::Matrix() :
    columns_(0),
    rows_(0),
    sizesOfLayers_(nullptr),
    matrix_(nullptr)
{
}

filimonova::Matrix::Matrix(const Matrix &matrix) :
    columns_(matrix.columns_),
    rows_(matrix.rows_),
    sizesOfLayers_(std::make_unique<size_t[]>(rows_)),
    matrix_(std::make_unique<std::shared_ptr<Shape>[]>(columns_))
{
  for (size_t i = 0; i < rows_; i++)
  {
    sizesOfLayers_[i] = matrix.sizesOfLayers_[i];
    for (size_t j = 0; j < sizesOfLayers_[i]; j++)
    {
      matrix_[i * columns_ + j] = matrix.matrix_[i * columns_ + j];
    }
  }
}

filimonova::Matrix::Matrix(Matrix &&matrix) noexcept:
    columns_(matrix.columns_),
    rows_(matrix.rows_),
    sizesOfLayers_(std::move(matrix.sizesOfLayers_)),
    matrix_(std::move(matrix.matrix_))
{
  matrix.columns_ = 0;
  matrix.rows_ = 0;
}

filimonova::Matrix &filimonova::Matrix::operator=(const Matrix &matrix)
{
  if (this == &matrix)
  {
    return *this;
  }

  matrix_.reset();
  sizesOfLayers_.reset();
  rows_ = matrix.rows_;
  columns_ = matrix.columns_;

  sizesOfLayers_ = std::make_unique<size_t[]>(rows_);
  matrix_ = std::make_unique<std::shared_ptr<Shape>[]>(rows_ * columns_);

  for (size_t i = 0; i < rows_; i++)
  {
    sizesOfLayers_[i] = matrix.sizesOfLayers_[i];
    for (size_t j = 0; j < sizesOfLayers_[i]; j++)
    {
      matrix_[i * columns_ + j] = matrix.matrix_[i * columns_ + j];
    }
  }

  return *this;
}

filimonova::Matrix &filimonova::Matrix::operator=(Matrix &&matrix) noexcept
{
  if (this == &matrix)
  {
    return *this;
  }

  rows_ = matrix.rows_;
  columns_ = matrix.columns_;

  matrix_.reset();
  sizesOfLayers_.reset();

  sizesOfLayers_ = std::move(matrix.sizesOfLayers_);
  matrix_ = std::move(matrix.matrix_);

  matrix.columns_ = 0;
  matrix.rows_ = 0;

  return *this;
}

filimonova::Matrix::Layer filimonova::Matrix::operator[](size_t layer)
{
  if (columns_ == 0)
  {
    throw std::domain_error("This matrix is empty.");
  }

  if (layer >= rows_)
  {
    throw std::out_of_range("Index " + std::to_string(layer) + "is out of matrix range.");
  }

  return Layer(&matrix_[columns_ * layer], sizesOfLayers_[layer]);
}

const filimonova::Matrix::Layer filimonova::Matrix::operator[](size_t layer) const
{
  if (columns_ == 0)
  {
    throw std::domain_error("This matrix is empty.");
  }

  if (layer >= rows_)
  {
    throw std::out_of_range("Index " + std::to_string(layer) + " is out of matrix range.");
  }

  return Layer(&matrix_[columns_ * layer], sizesOfLayers_[layer]);
}

size_t filimonova::Matrix::getAmountOfLayers() const
{
  return rows_;
}

size_t filimonova::Matrix::getSizeOfLayer(size_t i) const
{
  if (i >= rows_)
  {
    throw std::out_of_range("Index " + std::to_string(i) + "is out of matrix range.");
  }
  return sizesOfLayers_[i];
}

void filimonova::Matrix::add(const std::shared_ptr<Shape> &shape)
{
  if (!shape)
  {
    throw std::invalid_argument("Invalid shape: null pointer can't be added to matrix.");
  }

  size_t currentLayer = getLayerForAdding(shape);
  expandMatrixForAdding(currentLayer);

  matrix_[currentLayer * columns_ + sizesOfLayers_[currentLayer]] = shape;
  sizesOfLayers_[currentLayer]++;
}

void filimonova::Matrix::print(std::ostream &out)
{
  out << "\nMatrix:\n";

  for (size_t i = 0; i < rows_; i++)
  {
    out << '\n' << i + 1 << " layer:";
    for (size_t j = 0; j < sizesOfLayers_[i]; j++)
    {
      matrix_[i * columns_ + j]->print(out);
    }
  }
}

size_t filimonova::Matrix::getLayerForAdding(const std::shared_ptr<Shape> &shape) const
{
  size_t currentLayer = 0;

  for (size_t i = 0; i < rows_; i++)
  {
    for (size_t j = 0; j < sizesOfLayers_[i]; j++)
    {
      if (shape == matrix_[i * columns_ + j])
      {
        throw std::invalid_argument("This shape is already in the matrix.");
      }
      else if (areIntersecting(matrix_[i * columns_ + j]->getFrameRect(), shape->getFrameRect()))
      {
        currentLayer = i + 1;
      }
    }
  }
  return currentLayer;
}

void filimonova::Matrix::expandMatrixForAdding(size_t currentLayer)
{
  if (currentLayer == rows_)
  {
    std::unique_ptr<size_t[]> sizesCopy = std::make_unique<size_t[]>(rows_ + 1);
    sizesCopy.swap(sizesOfLayers_);

    std::unique_ptr<std::shared_ptr<Shape>[]> matrixCopy = std::make_unique<std::shared_ptr<Shape>[]>(
        (rows_ + 1) * columns_);
    matrixCopy.swap(matrix_);
    for (size_t i = 0; i < rows_; i++)
    {
      sizesOfLayers_[i] = sizesCopy[i];
      for (size_t j = 0; j < sizesOfLayers_[i]; j++)
      {
        matrix_[i * columns_ + j] = matrixCopy[i * columns_ + j];
      }
    }
    sizesOfLayers_[rows_++] = 0;
  }

  if ((sizesOfLayers_[currentLayer] + 1) > columns_)
  {
    columns_ = sizesOfLayers_[currentLayer] + 1;

    std::unique_ptr<std::shared_ptr<Shape>[]> matrixCopy = std::make_unique<std::shared_ptr<Shape>[]>(rows_ * columns_);
    matrixCopy.swap(matrix_);

    for (size_t i = 0; i < rows_; i++)
    {
      for (size_t j = 0; j < sizesOfLayers_[i]; j++)
      {
        matrix_[i * columns_ + j] = matrixCopy[i * (columns_ - 1) + j];
      }
    }
  }
}
