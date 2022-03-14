#include <iostream>
#include <stdexcept>
#include <memory>

#include "../common/shape.hpp"
#include "../common/circle.hpp"
#include "../common/rectangle.hpp"
#include "../common/base-types.hpp"
#include "../common/composite-shape.hpp"

int main(int, char **)
{
  std::shared_ptr<filimonova::Rectangle> rect = nullptr;

  try
  {
    rect = std::make_shared<filimonova::Rectangle>(10.5, 1.3, filimonova::point_t{1, 2});
  }
  catch (const std::invalid_argument &error)
  {
    std::cerr << error.what();
    return 1;
  }
  rect->print(std::cout);

  std::shared_ptr<filimonova::Shape> shape = rect;

  shape->move({5, 0});
  filimonova::point_t position = rect->getPosition();
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
    return 1;
  }

  std::cout << "Scaled rectangle with coefficient 1.7:";
  rect->print(std::cout);

  std::shared_ptr<filimonova::Circle> circle1 = nullptr;
  try
  {
    circle1 = std::make_shared<filimonova::Circle>(filimonova::point_t{0, 0}, 12.2);
  }
  catch (const std::invalid_argument &error)
  {
    std::cerr << error.what();
    return 1;
  }

  circle1->print(std::cout);

  shape = circle1;

  shape->move({-3, -7});
  position = circle1->getPosition();
  std::cout << "Moved circle to point (-3, 7): position (" << position.x << ", " << position.y << ").\n";

  shape->move(5.6, 3.4);
  position = circle1->getPosition();
  std::cout << "Moved circle by (5.6, 3.4): position (" << position.x << ", " << position.y << ").\n\n";

  try
  {
    shape->scale(3.2);
  }
  catch (const std::invalid_argument &error)
  {
    std::cerr << error.what();
    return 1;
  }

  std::cout << "Scaled circle with coefficient 3.2:";
  circle1->print(std::cout);

  filimonova::CompositeShape compositeShape;

  std::shared_ptr<filimonova::Circle> circle2 = nullptr;
  try
  {
    circle2 = std::make_shared<filimonova::Circle>(filimonova::point_t{-7.12, 11}, 2.1);
  }
  catch (const std::invalid_argument &error)
  {
    std::cerr << error.what();
    return 1;
  }

  try
  {
    compositeShape.add(rect);
    compositeShape.add(circle1);
    compositeShape.add(circle2);
  }
  catch (const std::invalid_argument &error)
  {
    std::cerr << error.what();
    return 1;
  }

  compositeShape.print(std::cout);

  compositeShape.move({-9.88, -4.0});
  position = compositeShape.getPosition();
  std::cout << "\nMoved composite shape to point (-9.88, -4.0): position (" << position.x << ", " << position.y
      << ").\n";

  compositeShape.move(7.0, 5.6);
  position = compositeShape.getPosition();
  std::cout << "\nMoved composite shape by (7.0, 5.6): position (" << position.x << ", " << position.y
      << ").\n";

  try
  {
    compositeShape.remove(2);
  }
  catch (std::invalid_argument &error)
  {
    std::cerr << error.what();
    return 1;
  }
  std::cout << "\nRemove figure 3 from composite shape:";

  compositeShape.print(std::cout);

  try
  {
    compositeShape.scale(2.4);
  }
  catch (const std::invalid_argument &error)
  {
    std::cerr << error.what();
    return 1;
  }

  std::cout << "\nScaled composite shape with coefficient 2.4:";
  compositeShape.print(std::cout);

  return 0;
}
