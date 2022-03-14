#include <iostream>
#include <stdexcept>
#include "../common/shape.hpp"
#include "../common/circle.hpp"
#include "../common/rectangle.hpp"
#include "../common/base-types.hpp"

int main(int, char **)
{
  filimonova::Rectangle *rect = nullptr;

  try
  {
    rect = new filimonova::Rectangle(10.5, 1.3, {1, 2});
  }
  catch (const std::invalid_argument &error)
  {
    std::cerr << error.what();
    return 1;
  }

  filimonova::point_t position = rect->getPosition();
  filimonova::rectangle_t frameRect = rect->getFrameRect();

  std::cout << "Rectangle: width " << rect->getWidth() << ", height " << rect->getHeight() << ", position ("
      << position.x << ", " << position.y << "). \nArea of rectangle: " << rect->getArea()
      << ".\nFrame rectangle: width " << frameRect.width << ", height " << frameRect.height << ", position ("
      << frameRect.pos.x << ", " << frameRect.pos.y << ").\n";

  filimonova::Shape *shape = rect;

  shape->move({5, 0});
  position = rect->getPosition();
  std::cout << "Moved rectangle to point (5, 0): position (" << position.x << ", " << position.y << ").\n";

  shape->move(-3, 6.6);
  position = rect->getPosition();
  std::cout << "Moved rectangle by (-3, 6.6): position (" << position.x << ", " << position.y << ").\n\n";

  try
  {
    shape->scale(1.7);
  }
  catch (const std::invalid_argument &error)
  {
    std::cerr << error.what();
    delete rect;
    return 1;
  }

  frameRect = rect->getFrameRect();
  std::cout << "Scaled rectangle with coefficient 1.7:\nWidth " << rect->getWidth() << ", height " << rect->getHeight()
      << ", position (" << position.x << ", " << position.y << "). \nArea of rectangle: " << rect->getArea()
      << ".\nFrame rectangle: width " << frameRect.width << ", height " << frameRect.height << ", position ("
      << frameRect.pos.x << ", " << frameRect.pos.y << ").\n\n";

  delete rect;

  filimonova::Circle *circle = nullptr;
  try
  {
    circle = new filimonova::Circle({0, 0}, 12.2);
  }
  catch (const std::invalid_argument &error)
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
  std::cout << "Moved circle by (5.6, 3.4): center (" << position.x << ", " << position.y << ").\n\n";

  try
  {
    shape->scale(3.2);
  }
  catch (const std::invalid_argument &error)
  {
    std::cerr << error.what();
    delete circle;
    return 1;
  }

  frameRect = circle->getFrameRect();

  std::cout << "Scaled circle with coefficient 3.2:\nCenter (" << position.x << ", " << position.y << "), radius "
      << circle->getRadius() << ".\nArea of circle: " << circle->getArea() << ".\nFrame rectangle: width "
      << frameRect.width << ", height " << frameRect.height << ", position (" << frameRect.pos.x << ", "
      << frameRect.pos.y << ").\n";

  delete circle;

  return 0;
}
