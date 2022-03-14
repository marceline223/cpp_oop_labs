#include "tasks.hpp"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

#include "shape.hpp"

void doTask2()
{
  std::vector<Shape> shapes{ std::istream_iterator<Shape>(std::cin), std::istream_iterator<Shape>() };
  if (!std::cin.eof())
  {
    throw std::invalid_argument("Invalid input!");
  }

  size_t amountOfTriangles = 0;
  size_t amountOfRectangles = 0;
  size_t amountOfSquares = 0;
  size_t amountOfVertices = 0;
  

  for (const Shape& shape : shapes)
  {
    amountOfVertices += shape.points.size();
    switch (shape.type) 
    {
      case ShapeType::TRIANGLE:
        ++amountOfTriangles;
        break;
      case ShapeType::SQUARE:
        ++amountOfSquares;
        ++amountOfRectangles;
        break;
      case ShapeType::RECTANGLE:
        ++amountOfRectangles;
        break;
      default:
        break;
    }
  }
  
  shapes.erase(std::remove_if(shapes.begin(), shapes.end(), [](const Shape& shape)
  {
    return shape.points.size() == 5;
  }), shapes.end());

  std::cout << "Vertices: " << amountOfVertices << '\n'
      << "Triangles: " << amountOfTriangles << '\n'
      << "Squares: " << amountOfSquares << '\n'
      << "Rectangles: " << amountOfRectangles << '\n';

  std::vector<Point> points{};
  for (Shape& shape : shapes)
  {
    points.push_back(shape.points[0]);
  }
 
  std::cout << "Points:";
  std::copy(points.begin(), points.end(), std::ostream_iterator<Point>(std::cout, " "));
  std::cout << "\n";

  std::sort(shapes.begin(), shapes.end());
  std::cout << "Shapes:\n";
  std::copy(shapes.begin(), shapes.end(), std::ostream_iterator<Shape>(std::cout, "\n"));
}
