#include <iostream>
#include <stdexcept>
#include <memory>
#include <initializer_list>

#include "../common/shape.hpp"
#include "../common/circle.hpp"
#include "../common/rectangle.hpp"
#include "../common/base-types.hpp"
#include "../common/composite-shape.hpp"
#include "../common/matrix.hpp"
#include "../common/polygon.hpp"

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

  std::cout << "Rotate rectangle with angle 90 degrees:";
  rect->rotate(90);
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

  std::cout << "Rotate circle with angle 14.156 degrees:";
  rect->rotate(14.156);
  rect->print(std::cout);


  std::shared_ptr<filimonova::Polygon> polygon = nullptr;
  try
  {
    polygon = std::make_shared<filimonova::Polygon>(
        std::initializer_list<filimonova::point_t>{{-5, 1}, {-1, 2}, {2, -1}, {-4, 4}, {3, 0}});
  }
  catch (const std::invalid_argument &error)
  {
    std::cerr << error.what();
    return 1;
  }

  polygon->print(std::cout);

  polygon->move({-11, 8});
  std::cout << "\nMoved polygon to point (-11, 8):";
  polygon->print(std::cout);

  shape->move(5.6, 3.4);
  std::cout << "\nMoved polygon by (5.6, 3.4):";
  polygon->print(std::cout);

  try
  {
    polygon->scale(2);
  }
  catch (const std::invalid_argument &error)
  {
    std::cerr << error.what();
    return 1;
  }

  std::cout << "\nScaled polygon with coefficient 2:";
  polygon->print(std::cout);

  std::cout << "\nRotate polygon with angle 30 degrees:";
  polygon->rotate(30);
  polygon->print(std::cout);


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

  std::cout << "\nRotated composite shape with angle 90 degrees:";
  compositeShape.rotate(90);
  compositeShape.print(std::cout);

  std::cout << "\nCreating matrix with previously submitted figures:\n";
  filimonova::Matrix matrix;

  try
  {
    matrix.add(circle1);
    matrix.add(circle2);
    matrix.add(rect);
    matrix.add(polygon);
  }
  catch (const std::invalid_argument &error)
  {
    std::cerr << error.what();
    return 1;
  }
  matrix.print(std::cout);

  return 0;
}

