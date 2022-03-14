#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <memory>
#include <iosfwd>

#include "shape.hpp"

namespace filimonova
{
  class Matrix
  {
  public:

    class Layer
    {
    public:

      std::shared_ptr<filimonova::Shape> operator[](size_t i);

      std::shared_ptr<const filimonova::Shape> operator[](size_t i) const;

    private:
      size_t size_;
      std::shared_ptr<Shape>* layer_;

      Layer(std::shared_ptr<Shape>* shape, size_t size);

      friend class Matrix;
    };

    Matrix();

    Matrix(const Matrix &matrix);

    Matrix(Matrix &&matrix) noexcept;

    ~Matrix() = default;

    Matrix &operator=(const Matrix &matrix);

    Matrix &operator=(Matrix &&matrix) noexcept;

    Layer operator[](size_t i);

    const Layer operator[](size_t i) const;

    size_t getAmountOfLayers() const;

    size_t getSizeOfLayer(size_t i) const;

    void add(const std::shared_ptr<Shape> &shape);

    void print(std::ostream &out);

  private:
    size_t columns_;
    size_t rows_;

    std::unique_ptr<size_t[]> sizesOfLayers_;
    std::unique_ptr<std::shared_ptr<Shape>[]> matrix_;

    size_t getLayerForAdding(const std::shared_ptr<Shape> &shape) const;
    void expandMatrixForAdding(size_t currentLayer);
  };
}

#endif
