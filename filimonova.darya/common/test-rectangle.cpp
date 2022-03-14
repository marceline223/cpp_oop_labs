#include <boost/test/unit_test.hpp>

#include <stdexcept>

#include "rectangle.hpp"
#include "base-types.hpp"

const double EPSILON = 0.0001, X = 8.12, Y = -34.6, WIDTH = 35.1, HEIGHT = 6.66;

BOOST_AUTO_TEST_SUITE(rectangle_validConstructor)

  BOOST_AUTO_TEST_CASE(rectangle_validConstructor_noThrow)
  {
    BOOST_CHECK_NO_THROW(filimonova::Rectangle rectangle(WIDTH, HEIGHT, {X, Y}));
  }

  BOOST_AUTO_TEST_CASE(rectangle_validConstructor_getterOfWidth)
  {
    filimonova::Rectangle rectangle(WIDTH, HEIGHT, {X, Y});

    BOOST_CHECK_CLOSE(rectangle.getWidth(), WIDTH, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(rectangle_validConstructor_getterOfHeight)
  {
    filimonova::Rectangle rectangle(WIDTH, HEIGHT, {X, Y});

    BOOST_CHECK_CLOSE(rectangle.getHeight(), HEIGHT, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(rectangle_validConstructor_getterOfPosition)
  {
    filimonova::Rectangle rectangle(WIDTH, HEIGHT, {X, Y});

    BOOST_CHECK_CLOSE(rectangle.getPosition().x, X, EPSILON);
    BOOST_CHECK_CLOSE(rectangle.getPosition().y, Y, EPSILON);
  }

BOOST_AUTO_TEST_SUITE_END();


BOOST_AUTO_TEST_SUITE(rectangle_invalidConstructor)

  BOOST_AUTO_TEST_CASE(rectangle_invalidConstructor_negativeNumberAsWidth_throw)
  {
    BOOST_CHECK_THROW(filimonova::Rectangle rectangle(-9.34, HEIGHT, {X, Y}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(rectangle_invalidConstructor_negativeNumberAsHeight_throw)
  {
    BOOST_CHECK_THROW(filimonova::Rectangle rectangle(WIDTH, -3.56, {X, Y}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(rectangle_invalidConstructor_nullAsWidth_throw)
  {
    BOOST_CHECK_THROW(filimonova::Rectangle rectangle(0, HEIGHT, {X, Y}), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(rectangle_invalidConstructor_nullAsHeight_throw)
  {
    BOOST_CHECK_THROW(filimonova::Rectangle rectangle(WIDTH, 0, {X, Y}), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END();


BOOST_AUTO_TEST_SUITE(rectangle_area)

  BOOST_AUTO_TEST_CASE(rectangle_area_close)
  {
    filimonova::Rectangle rectangle(WIDTH, HEIGHT, {X, Y});

    BOOST_CHECK_CLOSE(rectangle.getArea(), WIDTH * HEIGHT, EPSILON);
  }

BOOST_AUTO_TEST_SUITE_END();


BOOST_AUTO_TEST_SUITE(rectangle_frameRect)

  BOOST_AUTO_TEST_CASE(rectangle_frameRect_width_close)
  {
    filimonova::Rectangle rectangle(WIDTH, HEIGHT, {X, Y});
    filimonova::rectangle_t frameRect = rectangle.getFrameRect();

    BOOST_CHECK_CLOSE(rectangle.getWidth(), frameRect.width, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(rectangle_frameRect_height_close)
  {
    filimonova::Rectangle rectangle(WIDTH, HEIGHT, {X, Y});
    filimonova::rectangle_t frameRect = rectangle.getFrameRect();

    BOOST_CHECK_CLOSE(rectangle.getHeight(), frameRect.height, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(rectangle_frameRect_position_close)
  {
    filimonova::Rectangle rectangle(WIDTH, HEIGHT, {X, Y});
    filimonova::rectangle_t frameRect = rectangle.getFrameRect();

    BOOST_CHECK_CLOSE(rectangle.getPosition().x, frameRect.pos.x, EPSILON);
    BOOST_CHECK_CLOSE(rectangle.getPosition().y, frameRect.pos.y, EPSILON);
  }

BOOST_AUTO_TEST_SUITE_END();


BOOST_AUTO_TEST_SUITE(rectangle_moveToPoint)

  BOOST_AUTO_TEST_CASE(rectangle_moveToPoint_notChangeArea)
  {
    filimonova::Rectangle rectangle(WIDTH, HEIGHT, {X, Y});
    const filimonova::point_t newPos{13.5, -3};

    const double areaBeforeMoving = rectangle.getArea();

    rectangle.move(newPos);

    BOOST_CHECK_CLOSE(rectangle.getArea(), areaBeforeMoving, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(rectangle_moveToPoint_changePosition)
  {
    filimonova::Rectangle rectangle(WIDTH, HEIGHT, {X, Y});
    const filimonova::point_t newPos{13.5, -3};

    rectangle.move(newPos);

    BOOST_CHECK_CLOSE(rectangle.getPosition().x, newPos.x, EPSILON);
    BOOST_CHECK_CLOSE(rectangle.getPosition().y, newPos.y, EPSILON);
  }

BOOST_AUTO_TEST_SUITE_END();


BOOST_AUTO_TEST_SUITE(rectangle_moveByXY)

  BOOST_AUTO_TEST_CASE(rectangle_moveByXY_notChangeArea)
  {
    filimonova::Rectangle rectangle(WIDTH, HEIGHT, {X, Y});

    const double areaBeforeMoving = rectangle.getArea();

    const double dX = 0.53, dY = -5.0;
    rectangle.move(dX, dY);

    BOOST_CHECK_CLOSE(rectangle.getArea(), areaBeforeMoving, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(rectangle_moveByXY_changePosition)
  {
    filimonova::Rectangle rectangle(WIDTH, HEIGHT, {X, Y});

    const filimonova::point_t posBeforeMoving = rectangle.getPosition();

    const double dX = 0.53, dY = -5.0;
    rectangle.move(dX, dY);

    BOOST_CHECK_CLOSE(rectangle.getPosition().x, posBeforeMoving.x + dX, EPSILON);
    BOOST_CHECK_CLOSE(rectangle.getPosition().y, posBeforeMoving.y + dY, EPSILON);
  }

BOOST_AUTO_TEST_SUITE_END();


BOOST_AUTO_TEST_SUITE(rectangle_scale_correctCoefficient)

  BOOST_AUTO_TEST_CASE(rectangle_scale_correctCoefficient_noThrow)
  {
    filimonova::Rectangle rectangle(WIDTH, HEIGHT, {X, Y});

    const double coefficient = 5.7;

    BOOST_CHECK_NO_THROW(rectangle.scale(coefficient));
  }

  BOOST_AUTO_TEST_CASE(rectangle_scale_correctCoefficient_notChangePosition)
  {
    filimonova::Rectangle rectangle(WIDTH, HEIGHT, {X, Y});
    filimonova::point_t positionBeforeScaling = rectangle.getPosition();

    const double coefficient = 5.7;

    rectangle.scale(coefficient);

    BOOST_CHECK_CLOSE(rectangle.getPosition().x, positionBeforeScaling.x, EPSILON);
    BOOST_CHECK_CLOSE(rectangle.getPosition().y, positionBeforeScaling.y, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(rectangle_scale_correctCoefficient_notChangePositionOfFrameRect)
  {
    filimonova::Rectangle rectangle(WIDTH, HEIGHT, {X, Y});
    const filimonova::rectangle_t frameRectBeforeScaling = rectangle.getFrameRect();

    const double coefficient = 5.7;

    rectangle.scale(coefficient);

    BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, frameRectBeforeScaling.pos.x, EPSILON);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, frameRectBeforeScaling.pos.y, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(rectangle_scale_correctCoefficient_changeWidth)
  {
    filimonova::Rectangle rectangle(WIDTH, HEIGHT, {X, Y});

    const double coefficient = 5.7;

    rectangle.scale(coefficient);

    BOOST_CHECK_CLOSE(rectangle.getWidth(), WIDTH * coefficient, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(rectangle_scale_correctCoefficient_changeHeight)
  {
    filimonova::Rectangle rectangle(WIDTH, HEIGHT, {X, Y});

    const double coefficient = 5.7;

    rectangle.scale(coefficient);

    BOOST_CHECK_CLOSE(rectangle.getHeight(), HEIGHT * coefficient, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(rectangle_scale_correctCoefficient_changeArea)
  {
    filimonova::Rectangle rectangle(WIDTH, HEIGHT, {X, Y});
    const double areaBeforeScaling = rectangle.getArea();

    const double coefficient = 5.7;

    rectangle.scale(coefficient);

    BOOST_CHECK_CLOSE(rectangle.getArea(), areaBeforeScaling * coefficient * coefficient, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(rectangle_scale_correctCoefficient_changeFrameRectWidth)
  {
    filimonova::Rectangle rectangle(WIDTH, HEIGHT, {X, Y});
    const filimonova::rectangle_t frameRectBeforeScaling = rectangle.getFrameRect();

    const double coefficient = 5.7;

    rectangle.scale(coefficient);

    BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, frameRectBeforeScaling.width * coefficient, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(rectangle_scale_correctCoefficient_changeFrameRectHeight)
  {
    filimonova::Rectangle rectangle(WIDTH, HEIGHT, {X, Y});
    const filimonova::rectangle_t frameRectBeforeScaling = rectangle.getFrameRect();

    const double coefficient = 5.7;

    rectangle.scale(coefficient);

    BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, frameRectBeforeScaling.height * coefficient, EPSILON);
  }

BOOST_AUTO_TEST_SUITE_END();


BOOST_AUTO_TEST_SUITE(rectangle_scale_incorrectCoefficient)

  BOOST_AUTO_TEST_CASE(rectangle_scale_incorrectCoefficient_negativeNumberAsCoefficient_throw)
  {
    filimonova::Rectangle rectangle(WIDTH, HEIGHT, {X, Y});

    BOOST_CHECK_THROW(rectangle.scale(-5), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(rectangle_scale_incorrectCoefficient_nullAsCoefficient_throw)
  {
    filimonova::Rectangle rectangle(WIDTH, HEIGHT, {X, Y});

    BOOST_CHECK_THROW(rectangle.scale(0), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(rectangle_rotate)

  BOOST_AUTO_TEST_CASE(rectangle_rotate_notChangePosition_notChangeArea)
  {
    filimonova::Rectangle rectangle(WIDTH, HEIGHT, {X, Y});

    filimonova::point_t positionBeforeRotating = rectangle.getPosition();
    double areaBeforeRotating = rectangle.getArea();
    rectangle.rotate(60);

    BOOST_CHECK_CLOSE(positionBeforeRotating.x, rectangle.getPosition().x, EPSILON);
    BOOST_CHECK_CLOSE(positionBeforeRotating.y, rectangle.getPosition().y, EPSILON);

    BOOST_CHECK_CLOSE(areaBeforeRotating, rectangle.getArea(), EPSILON);
  }

BOOST_AUTO_TEST_SUITE_END();
