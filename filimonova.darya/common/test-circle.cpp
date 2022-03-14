#include <boost/test/unit_test.hpp>

#include <stdexcept>
#include <cmath>

#include "circle.hpp"
#include "base-types.hpp"

const double EPSILON = 0.0001, X = -15.6, Y = 3.33, RADIUS = 24.13;

BOOST_AUTO_TEST_SUITE(circle_validConstructor)

  BOOST_AUTO_TEST_CASE(circle_validConstructor_noThrow)
  {
    BOOST_CHECK_NO_THROW(filimonova::Circle circle({X, Y}, RADIUS));
  }

  BOOST_AUTO_TEST_CASE(circle_validConstructor_getterOfRadius)
  {
    filimonova::Circle circle({X, Y}, RADIUS);
    BOOST_CHECK_CLOSE(circle.getRadius(), RADIUS, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(circle_validConstructor_getterOfPosition)
  {
    filimonova::Circle circle({X, Y}, RADIUS);
    BOOST_CHECK_CLOSE(circle.getPosition().x, X, EPSILON);
    BOOST_CHECK_CLOSE(circle.getPosition().y, Y, EPSILON);
  }

BOOST_AUTO_TEST_SUITE_END();


BOOST_AUTO_TEST_SUITE(circle_invalidConstructor)

  BOOST_AUTO_TEST_CASE(circle_invalidConstructor_negativeNumberAsRadius_throw)
  {
    BOOST_CHECK_THROW(filimonova::Circle circle({5.6, 3.9}, -5), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(circle_invalidConstructor_nullAsRadius_throw)
  {
    BOOST_CHECK_THROW(filimonova::Circle circle({5.6, 3.9}, 0), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END();


BOOST_AUTO_TEST_SUITE(circle_area)

  BOOST_AUTO_TEST_CASE(circle_area_close)
  {
    filimonova::Circle circle({X, Y}, RADIUS);
    BOOST_CHECK_CLOSE(circle.getArea(), M_PI * RADIUS * RADIUS, EPSILON);
  }

BOOST_AUTO_TEST_SUITE_END();


BOOST_AUTO_TEST_SUITE(circle_frameRect)

  BOOST_AUTO_TEST_CASE(circle_frameRect_width_close)
  {
    filimonova::Circle circle({X, Y}, RADIUS);
    filimonova::rectangle_t frameRect = circle.getFrameRect();

    BOOST_CHECK_CLOSE(circle.getRadius() * 2, frameRect.width, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(circle_frameRect_height_close)
  {
    filimonova::Circle circle({X, Y}, RADIUS);
    filimonova::rectangle_t frameRect = circle.getFrameRect();

    BOOST_CHECK_CLOSE(circle.getRadius() * 2, frameRect.height, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(circle_frameRect_position_close)
  {
    filimonova::Circle circle({X, Y}, RADIUS);
    filimonova::rectangle_t frameRect = circle.getFrameRect();

    BOOST_CHECK_CLOSE(circle.getPosition().x, frameRect.pos.x, EPSILON);
    BOOST_CHECK_CLOSE(circle.getPosition().y, frameRect.pos.y, EPSILON);
  }

BOOST_AUTO_TEST_SUITE_END();


BOOST_AUTO_TEST_SUITE(circle_moveToPoint)

  BOOST_AUTO_TEST_CASE(cirlce_moveToPoint_notChangeArea)
  {
    filimonova::Circle circle({X, Y}, RADIUS);
    const filimonova::point_t newPos{13.5, -3};

    const double areaBeforeMoving = circle.getArea();

    circle.move(newPos);

    BOOST_CHECK_CLOSE(circle.getArea(), areaBeforeMoving, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(cirlce_moveToPoint_changePosition)
  {
    filimonova::Circle circle({X, Y}, RADIUS);
    const filimonova::point_t newPos{13.5, -3};

    circle.move(newPos);

    BOOST_CHECK_CLOSE(circle.getPosition().x, newPos.x, EPSILON);
    BOOST_CHECK_CLOSE(circle.getPosition().y, newPos.y, EPSILON);
  }

BOOST_AUTO_TEST_SUITE_END();


BOOST_AUTO_TEST_SUITE(circle_moveByXY)

  BOOST_AUTO_TEST_CASE(circle_moveByXY_notChangeArea)
  {
    filimonova::Circle circle({X, Y}, RADIUS);

    const double areaBeforeMoving = circle.getArea();

    const double dX = 0.53, dY = -5.0;
    circle.move(dX, dY);

    BOOST_CHECK_CLOSE(circle.getArea(), areaBeforeMoving, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(circle_moveByXY_changePosition)
  {
    filimonova::Circle circle({X, Y}, RADIUS);

    const filimonova::point_t posBeforeMoving = circle.getPosition();

    const double dX = 0.53, dY = -5.0;
    circle.move(dX, dY);

    BOOST_CHECK_CLOSE(circle.getPosition().x, posBeforeMoving.x + dX, EPSILON);
    BOOST_CHECK_CLOSE(circle.getPosition().y, posBeforeMoving.y + dY, EPSILON);
  }

BOOST_AUTO_TEST_SUITE_END();


BOOST_AUTO_TEST_SUITE(circle_scale_correctCoefficient)

  BOOST_AUTO_TEST_CASE(circle_scale_correctCoefficient_noThrow)
  {
    filimonova::Circle circle({X, Y}, RADIUS);

    const double coefficient = 5.7;

    BOOST_CHECK_NO_THROW(circle.scale(coefficient));
  }

  BOOST_AUTO_TEST_CASE(circle_scale_correctCoefficient_notChangePosition)
  {
    filimonova::Circle circle({X, Y}, RADIUS);
    filimonova::point_t positionBeforeScaling = circle.getPosition();

    const double coefficient = 5.7;

    circle.scale(coefficient);

    BOOST_CHECK_CLOSE(circle.getPosition().x, positionBeforeScaling.x, EPSILON);
    BOOST_CHECK_CLOSE(circle.getPosition().y, positionBeforeScaling.y, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(circle_scale_correctCoefficient_notChangePositionOfFrameRect)
  {
    filimonova::Circle circle({X, Y}, RADIUS);
    const filimonova::rectangle_t frameRectBeforeScaling = circle.getFrameRect();

    const double coefficient = 5.7;

    circle.scale(coefficient);

    BOOST_CHECK_CLOSE(circle.getFrameRect().pos.x, frameRectBeforeScaling.pos.x, EPSILON);
    BOOST_CHECK_CLOSE(circle.getFrameRect().pos.y, frameRectBeforeScaling.pos.y, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(circle_scale_correctCoefficient_changeRadius)
  {
    filimonova::Circle circle({X, Y}, RADIUS);

    const double coefficient = 5.7;

    circle.scale(coefficient);

    BOOST_CHECK_CLOSE(circle.getRadius(), RADIUS * coefficient, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(circle_scale_correctCoefficient_changeArea)
  {
    filimonova::Circle circle({X, Y}, RADIUS);
    const double areaBeforeScaling = circle.getArea();

    const double coefficient = 5.7;

    circle.scale(coefficient);

    BOOST_CHECK_CLOSE(circle.getArea(), areaBeforeScaling * coefficient * coefficient, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(circle_scale_correctCoefficient_changeFrameRectWidth)
  {
    filimonova::Circle circle({X, Y}, RADIUS);
    const filimonova::rectangle_t frameRectBeforeScaling = circle.getFrameRect();

    const double coefficient = 5.7;

    circle.scale(coefficient);

    BOOST_CHECK_CLOSE(circle.getFrameRect().width, frameRectBeforeScaling.width * coefficient, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(circle_scale_correctCoefficient_changeFrameRectHeight)
  {
    filimonova::Circle circle({X, Y}, RADIUS);
    const filimonova::rectangle_t frameRectBeforeScaling = circle.getFrameRect();

    const double coefficient = 5.7;

    circle.scale(coefficient);

    BOOST_CHECK_CLOSE(circle.getFrameRect().height, frameRectBeforeScaling.height * coefficient, EPSILON);
  }

BOOST_AUTO_TEST_SUITE_END();


BOOST_AUTO_TEST_SUITE(circle_scale_incorrectCoefficient)

  BOOST_AUTO_TEST_CASE(circle_scale_incorrectCoefficient_negativeNumberAsCoefficient_throw)
  {
    filimonova::Circle circle({X, Y}, RADIUS);

    BOOST_CHECK_THROW(circle.scale(-5), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(circle_scale_incorrectCoefficient_nullAsCoefficient_throw)
  {
    filimonova::Circle circle({X, Y}, RADIUS);

    BOOST_CHECK_THROW(circle.scale(0), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(circle_rotate)

  BOOST_AUTO_TEST_CASE(circle_rotate_notChenge)
  {
    filimonova::Circle circle({X, Y}, RADIUS);

    circle.rotate(15.5);

    BOOST_CHECK_CLOSE(circle.getRadius(), RADIUS, EPSILON);
    BOOST_CHECK_CLOSE(circle.getPosition().x, X, EPSILON);
    BOOST_CHECK_CLOSE(circle.getPosition().y, Y, EPSILON);
    BOOST_CHECK_CLOSE(circle.getFrameRect().width, RADIUS * 2, EPSILON);
    BOOST_CHECK_CLOSE(circle.getFrameRect().height, RADIUS * 2, EPSILON);
  }

BOOST_AUTO_TEST_SUITE_END();
