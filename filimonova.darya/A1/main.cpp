#include <iostream>
#include "shape.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
#include "base-types.hpp"

int main(int, char **)
{
  Rectangle* rect = nullptr;
  try
  {
    rect = new Rectangle(10.5, 1.3, {1, 2});
  }
  catch (const std::invalid_argument& error)
  {
    std::cerr << error.what();
    return 1;
  }
  point_t position = rect->getPosition();
  rectangle_t frameRect = rect->getFrameRect();
  std::cout << "Rectangle: width " << rect->getWidth() << ", height " << rect->getHeight() << ", position ("
      << position.x << ", " << position.y << "). \nArea of rectangle: " << rect->getArea()
      << ".\nFrame rectangle: width "
      << frameRect.width << ", height " << frameRect.height << ", position (" << frameRect.pos.x << ", "
      << frameRect.pos.y << ").\n";
  Shape *shape = rect;
  shape->move({5, 0});
  position = rect->getPosition();
  std::cout << "Moved rectangle to point (5, 0): position (" << position.x << ", " << position.y << ").\n";
  shape->move(-3, 6.6);
  position = rect->getPosition();
  std::cout << "Moved rectangle by (-3, 6.6): position (" << position.x << ", " << position.y << ").\n\n";

  Circle* circle = nullptr;
  try
  {
    circle = new Circle({0, 0}, 12.2);
  }
  catch (const std::invalid_argument& error)
  {
    std::cerr << error.what();
    return 1;
  }
  position = circle->getPosition();
  frameRect = circle->getFrameRect();
  std::cout << "Circle: center (" << position.x << ", " << position.y << "), radius " << circle->getRadius()
      << ".\nArea of circle: " << circle->getArea() << ".\nFrame rectangle: width " << frameRect.width
      << ", height " << frameRect.height << ", position (" << frameRect.pos.x << ", " << frameRect.pos.y << ").\n";
  shape = circle;
  shape->move({-3, -7});
  position = circle->getPosition();
  std::cout << "Moved circle to point (-3, 7): center (" << position.x << ", " << position.y << ").\n";
  shape->move(5.6, 3.4);
  position = circle->getPosition();
  std::cout << "Moved circle by (5.6, 3.4): center (" << position.x << ", " << position.y << ").\n";

  delete rect;
  delete circle;
  return 0;
}
