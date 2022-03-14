#include <boost/test/unit_test.hpp>

#include <stdexcept>
#include <algorithm>

#include "composite-shape.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include "base-types.hpp"

const double EPSILON = 0.0001, WIDTH_1 = 12.0, WIDTH_2 = 2.54, HEIGHT_1 = 3.4, HEIGHT_2 = 7.0, RADIUS = 13.33;

const filimonova::point_t CIRCLE_POSITION{0.6, -1.2}, RECTANGLE_1_POSITION{17.5, -3.33},
    RECTANGLE_2_POSITION{1.53, -9.2};

BOOST_AUTO_TEST_SUITE(compositeShape_validConstructor)

  BOOST_AUTO_TEST_CASE(compositeShape_validConstructorWithoutParameters_noThrow)
  {
    BOOST_CHECK_NO_THROW(filimonova::CompositeShape compositeShape);
  }

  BOOST_AUTO_TEST_CASE(compositeShape_validConstructorWithoutParameters_correctSize)
  {
    filimonova::CompositeShape compositeShape;

    BOOST_CHECK_EQUAL(compositeShape.getSize(), 0);
  }

  BOOST_AUTO_TEST_CASE(compositeShape_validConstructorWithParameters_noThrow)
  {
    filimonova::CompositeShape compositeShape1;

    compositeShape1.add(std::make_shared<filimonova::Rectangle>(WIDTH_1, HEIGHT_1, RECTANGLE_1_POSITION));
    compositeShape1.add(std::make_shared<filimonova::Rectangle>(WIDTH_2, HEIGHT_2, RECTANGLE_2_POSITION));
    compositeShape1.add(std::make_shared<filimonova::Circle>(CIRCLE_POSITION, RADIUS));

    BOOST_CHECK_NO_THROW(filimonova::CompositeShape compositeShape2(compositeShape1));
  }

  BOOST_AUTO_TEST_CASE(compositeShape_validConstructorWithParameters_correctSizeAndShapes)
  {
    filimonova::CompositeShape compositeShape1;

    compositeShape1.add(std::make_shared<filimonova::Rectangle>(WIDTH_1, HEIGHT_1, RECTANGLE_1_POSITION));
    compositeShape1.add(std::make_shared<filimonova::Rectangle>(WIDTH_2, HEIGHT_2, RECTANGLE_2_POSITION));
    compositeShape1.add(std::make_shared<filimonova::Circle>(CIRCLE_POSITION, RADIUS));

    filimonova::CompositeShape compositeShape2(compositeShape1);

    BOOST_CHECK_EQUAL(compositeShape1[0], compositeShape2[0]);
    BOOST_CHECK_EQUAL(compositeShape1[1], compositeShape2[1]);
    BOOST_CHECK_EQUAL(compositeShape1[2], compositeShape2[2]);
    BOOST_CHECK_EQUAL(compositeShape2.getSize(), 3);
  }

BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(compositeShape_assignmentOperator)

  BOOST_AUTO_TEST_CASE(compositeShape_assignmentOperator_correctSizeAndShapes)
  {
    filimonova::CompositeShape compositeShape1;

    compositeShape1.add(std::make_shared<filimonova::Rectangle>(WIDTH_1, HEIGHT_1, RECTANGLE_1_POSITION));
    compositeShape1.add(std::make_shared<filimonova::Rectangle>(WIDTH_2, HEIGHT_2, RECTANGLE_2_POSITION));
    compositeShape1.add(std::make_shared<filimonova::Circle>(CIRCLE_POSITION, RADIUS));

    filimonova::CompositeShape compositeShape2 = compositeShape1;

    BOOST_CHECK_EQUAL(compositeShape1[0], compositeShape2[0]);
    BOOST_CHECK_EQUAL(compositeShape1[1], compositeShape2[1]);
    BOOST_CHECK_EQUAL(compositeShape1[2], compositeShape2[2]);

    BOOST_CHECK_EQUAL(compositeShape1.getSize(), compositeShape2.getSize());
  }

BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(compositeShape_indexOperator_correctIndex)

  BOOST_AUTO_TEST_CASE(compositeShape_indexOperator_correctIndex_noThrow)
  {
    filimonova::CompositeShape compositeShape;

    std::shared_ptr<filimonova::Rectangle> rect = std::make_shared<filimonova::Rectangle>(WIDTH_1,
        HEIGHT_1, RECTANGLE_1_POSITION);
    std::shared_ptr<filimonova::Circle> circle = std::make_shared<filimonova::Circle>(CIRCLE_POSITION, RADIUS);

    compositeShape.add(rect);
    compositeShape.add(circle);

    BOOST_CHECK_NO_THROW(compositeShape[0]);
    BOOST_CHECK_NO_THROW(compositeShape[1]);
  }

  BOOST_AUTO_TEST_CASE(compositeShape_indexOperator_correctIndex_correctShapes)
  {
    filimonova::CompositeShape compositeShape;

    std::shared_ptr<filimonova::Rectangle> rect = std::make_shared<filimonova::Rectangle>(WIDTH_1,
        HEIGHT_1, RECTANGLE_1_POSITION);
    std::shared_ptr<filimonova::Circle> circle = std::make_shared<filimonova::Circle>(CIRCLE_POSITION, RADIUS);

    compositeShape.add(rect);
    BOOST_CHECK_EQUAL(compositeShape[0], rect);

    compositeShape.add(circle);
    BOOST_CHECK_EQUAL(compositeShape[1], circle);
  }

BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(compositeShape_indexOperator_incorrectIndex)

  BOOST_AUTO_TEST_CASE(compositeShape_indexOperator_incorrectIndex_throw)
  {
    filimonova::CompositeShape compositeShape;

    std::shared_ptr<filimonova::Rectangle> rect = std::make_shared<filimonova::Rectangle>(WIDTH_1,
        HEIGHT_1, RECTANGLE_1_POSITION);
    std::shared_ptr<filimonova::Circle> circle = std::make_shared<filimonova::Circle>(CIRCLE_POSITION, RADIUS);

    compositeShape.add(rect);
    compositeShape.add(circle);

    BOOST_CHECK_THROW(compositeShape[2], std::out_of_range);
  }

BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(compositeShape_getFrameRect)

  BOOST_AUTO_TEST_CASE(compositeShape_getFrameRect_correctWidthHeightAndPosition)
  {
    filimonova::CompositeShape compositeShape;

    std::shared_ptr<filimonova::Rectangle> rect = std::make_shared<filimonova::Rectangle>(WIDTH_1,
        HEIGHT_1, RECTANGLE_1_POSITION);
    std::shared_ptr<filimonova::Circle> circle = std::make_shared<filimonova::Circle>(CIRCLE_POSITION, RADIUS);

    compositeShape.add(rect);
    compositeShape.add(circle);

    filimonova::rectangle_t frameRect = compositeShape.getFrameRect();

    const double minX = std::min(CIRCLE_POSITION.x - RADIUS, RECTANGLE_1_POSITION.x - WIDTH_1 / 2.0),
        minY = std::min(CIRCLE_POSITION.y - RADIUS, RECTANGLE_1_POSITION.y - HEIGHT_1 / 2.0),
        maxX = std::max(CIRCLE_POSITION.x + RADIUS, RECTANGLE_1_POSITION.x + WIDTH_1 / 2.0),
        maxY = std::max(CIRCLE_POSITION.y + RADIUS, RECTANGLE_1_POSITION.y + HEIGHT_1 / 2.0);

    BOOST_CHECK_CLOSE(frameRect.width, maxX - minX, EPSILON);
    BOOST_CHECK_CLOSE(frameRect.height, maxY - minY, EPSILON);
    BOOST_CHECK_CLOSE(frameRect.pos.x, minX + (maxX - minX) / 2.0, EPSILON);
    BOOST_CHECK_CLOSE(frameRect.pos.y, minY + (maxY - minY) / 2.0, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(compositeShape_getFrameRect_emptyShape_negativeWidthAndHeight)
  {
    filimonova::CompositeShape compositeShape;

    BOOST_CHECK_CLOSE(compositeShape.getFrameRect().width, -1, EPSILON);
    BOOST_CHECK_CLOSE(compositeShape.getFrameRect().height, -1, EPSILON);
  }

BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(compositeShape_getPosition)

  BOOST_AUTO_TEST_CASE(compositeShape_getPosition_correctPosition)
  {
    filimonova::CompositeShape compositeShape;

    std::shared_ptr<filimonova::Rectangle> rect = std::make_shared<filimonova::Rectangle>(WIDTH_1,
        HEIGHT_1, RECTANGLE_1_POSITION);
    std::shared_ptr<filimonova::Circle> circle = std::make_shared<filimonova::Circle>(CIRCLE_POSITION, RADIUS);

    compositeShape.add(rect);
    compositeShape.add(circle);

    const filimonova::point_t position = compositeShape.getPosition();

    BOOST_CHECK_CLOSE(position.x, compositeShape.getFrameRect().pos.x, EPSILON);
    BOOST_CHECK_CLOSE(position.y, compositeShape.getFrameRect().pos.y, EPSILON);
  }

BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(compositeShape_getArea)

  BOOST_AUTO_TEST_CASE(compositeShape_getArea_areaClose)
  {
    filimonova::CompositeShape compositeShape;

    std::shared_ptr<filimonova::Rectangle> rect = std::make_shared<filimonova::Rectangle>(WIDTH_1,
        HEIGHT_1, RECTANGLE_1_POSITION);
    std::shared_ptr<filimonova::Circle> circle = std::make_shared<filimonova::Circle>(CIRCLE_POSITION, RADIUS);

    compositeShape.add(rect);
    compositeShape.add(circle);

    const double areaOfCompositeShape = compositeShape.getArea();

    BOOST_CHECK_CLOSE(areaOfCompositeShape, rect->getArea() + circle->getArea(), EPSILON);
  }

BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(compositeShape_addCorrectShape)

  BOOST_AUTO_TEST_CASE(compositeShape_addCorrectShape_noThrow)
  {
    filimonova::CompositeShape compositeShape;

    std::shared_ptr<filimonova::Rectangle> rect = std::make_shared<filimonova::Rectangle>(WIDTH_1,
        HEIGHT_1, RECTANGLE_1_POSITION);
    std::shared_ptr<filimonova::Circle> circle = std::make_shared<filimonova::Circle>(CIRCLE_POSITION, RADIUS);

    BOOST_CHECK_NO_THROW(compositeShape.add(rect));
    BOOST_CHECK_NO_THROW(compositeShape.add(circle));
  }

  BOOST_AUTO_TEST_CASE(compositeShape_addCorrectShape_changeSize)
  {
    filimonova::CompositeShape compositeShape;

    std::shared_ptr<filimonova::Rectangle> rect = std::make_shared<filimonova::Rectangle>(WIDTH_1,
        HEIGHT_1, RECTANGLE_1_POSITION);
    std::shared_ptr<filimonova::Circle> circle = std::make_shared<filimonova::Circle>(CIRCLE_POSITION, RADIUS);

    compositeShape.add(rect);
    compositeShape.add(circle);

    BOOST_CHECK_EQUAL(compositeShape.getSize(), 2);
  }

BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(compositeShape_addIncorrectShape)

  BOOST_AUTO_TEST_CASE(compositeShape_addIncorrectShape_throw)
  {
    filimonova::CompositeShape compositeShape;

    BOOST_CHECK_THROW(compositeShape.add(nullptr), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(compositeShape_remove_correctIndex)

  BOOST_AUTO_TEST_CASE(compositeShape_remove_correctIndex_noThrow)
  {
    filimonova::CompositeShape compositeShape;

    compositeShape.add(std::make_shared<filimonova::Rectangle>(WIDTH_1, HEIGHT_1, RECTANGLE_1_POSITION));
    compositeShape.add(std::make_shared<filimonova::Rectangle>(WIDTH_2, HEIGHT_2, RECTANGLE_2_POSITION));
    compositeShape.add(std::make_shared<filimonova::Circle>(CIRCLE_POSITION, RADIUS));

    BOOST_CHECK_NO_THROW(compositeShape.remove(1));
  }

  BOOST_AUTO_TEST_CASE(compositeShape_remove_correctIndex_changeSize)
  {
    filimonova::CompositeShape compositeShape;

    compositeShape.add(std::make_shared<filimonova::Rectangle>(WIDTH_1, HEIGHT_1, RECTANGLE_1_POSITION));
    compositeShape.add(std::make_shared<filimonova::Rectangle>(WIDTH_2, HEIGHT_2, RECTANGLE_2_POSITION));
    compositeShape.add(std::make_shared<filimonova::Circle>(CIRCLE_POSITION, RADIUS));

    compositeShape.remove(1);

    BOOST_CHECK_EQUAL(compositeShape.getSize(), 2);
  }

BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(compositeShape_remove_incorrectIndex)

  BOOST_AUTO_TEST_CASE(compositeShape_remove_incorrectIndex_throw)
  {
    filimonova::CompositeShape compositeShape;

    compositeShape.add(std::make_shared<filimonova::Rectangle>(WIDTH_1, HEIGHT_1, RECTANGLE_1_POSITION));
    compositeShape.add(std::make_shared<filimonova::Rectangle>(WIDTH_2, HEIGHT_2, RECTANGLE_2_POSITION));
    compositeShape.add(std::make_shared<filimonova::Circle>(CIRCLE_POSITION, RADIUS));

    BOOST_CHECK_THROW(compositeShape.remove(5), std::out_of_range);
  }

BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(compositeShape_moveToPoint)

  BOOST_AUTO_TEST_CASE(compositeShape_moveToPoint_notChangeArea)
  {
    filimonova::CompositeShape compositeShape;

    std::shared_ptr<filimonova::Rectangle> rect = std::make_shared<filimonova::Rectangle>(WIDTH_1,
        HEIGHT_1, RECTANGLE_1_POSITION);
    std::shared_ptr<filimonova::Circle> circle = std::make_shared<filimonova::Circle>(CIRCLE_POSITION, RADIUS);

    compositeShape.add(rect);
    compositeShape.add(circle);

    const double areaBeforeMoving = compositeShape.getArea();

    compositeShape.move({-5.6, 2.4});

    BOOST_CHECK_CLOSE(areaBeforeMoving, compositeShape.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(compositeShape_moveToPoint_changePosition)
  {
    filimonova::CompositeShape compositeShape;

    std::shared_ptr<filimonova::Rectangle> rect = std::make_shared<filimonova::Rectangle>(WIDTH_1,
        HEIGHT_1, RECTANGLE_1_POSITION);
    std::shared_ptr<filimonova::Circle> circle = std::make_shared<filimonova::Circle>(CIRCLE_POSITION, RADIUS);

    compositeShape.add(rect);
    compositeShape.add(circle);

    const filimonova::point_t newPosition{-5.6, 2.4};

    compositeShape.move(newPosition);

    BOOST_CHECK_CLOSE(compositeShape.getPosition().x, newPosition.x, EPSILON);
    BOOST_CHECK_CLOSE(compositeShape.getPosition().y, newPosition.y, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(compositeShape_moveToPoint_moveEmptyShape_throw)
  {
    filimonova::CompositeShape compositeShape;

    const filimonova::point_t newPosition{-5.6, 2.4};

    BOOST_CHECK_THROW(compositeShape.move(newPosition), std::domain_error);
  }

BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(compositeShape_moveByXY)

  BOOST_AUTO_TEST_CASE(compositeShape_moveByXY_notChangeArea)
  {
    filimonova::CompositeShape compositeShape;

    std::shared_ptr<filimonova::Rectangle> rect = std::make_shared<filimonova::Rectangle>(WIDTH_1,
        HEIGHT_1, RECTANGLE_1_POSITION);
    std::shared_ptr<filimonova::Circle> circle = std::make_shared<filimonova::Circle>(CIRCLE_POSITION, RADIUS);

    compositeShape.add(rect);
    compositeShape.add(circle);

    const double areaBeforeMoving = compositeShape.getArea();

    compositeShape.move(-4.11, 3.14);

    BOOST_CHECK_CLOSE(areaBeforeMoving, compositeShape.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(compositeShape_moveByXY_changePosition)
  {
    filimonova::CompositeShape compositeShape;

    std::shared_ptr<filimonova::Rectangle> rect = std::make_shared<filimonova::Rectangle>(WIDTH_1,
        HEIGHT_1, RECTANGLE_1_POSITION);
    std::shared_ptr<filimonova::Circle> circle = std::make_shared<filimonova::Circle>(CIRCLE_POSITION, RADIUS);

    compositeShape.add(rect);
    compositeShape.add(circle);

    const filimonova::point_t positionBeforeMoving = compositeShape.getPosition();
    const double dX = -4.11, dY = 3.14;

    compositeShape.move(dX, dY);

    BOOST_CHECK_CLOSE(compositeShape.getPosition().x, positionBeforeMoving.x + dX, EPSILON);
    BOOST_CHECK_CLOSE(compositeShape.getPosition().y, positionBeforeMoving.y + dY, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(compositeShape_moveByXY_moveEmptyShape_throw)
  {
    filimonova::CompositeShape compositeShape;

    const double dX = -4.11, dY = 3.14;

    BOOST_CHECK_THROW(compositeShape.move(dX, dY), std::domain_error);
  }

BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(compositeShape_scale_correctCoefficient)

  BOOST_AUTO_TEST_CASE(compositeShape_scale_correctCoefficient_noThrow)
  {
    filimonova::CompositeShape compositeShape;

    std::shared_ptr<filimonova::Rectangle> rect = std::make_shared<filimonova::Rectangle>(WIDTH_1,
        HEIGHT_1, RECTANGLE_1_POSITION);
    std::shared_ptr<filimonova::Circle> circle = std::make_shared<filimonova::Circle>(CIRCLE_POSITION, RADIUS);

    compositeShape.add(rect);
    compositeShape.add(circle);

    BOOST_CHECK_NO_THROW(compositeShape.scale(1.5));
  }

  BOOST_AUTO_TEST_CASE(compositeShape_scale_correctCoefficient_notChangePosition)
  {
    filimonova::CompositeShape compositeShape;

    std::shared_ptr<filimonova::Rectangle> rect = std::make_shared<filimonova::Rectangle>(WIDTH_1,
        HEIGHT_1, RECTANGLE_1_POSITION);
    std::shared_ptr<filimonova::Circle> circle = std::make_shared<filimonova::Circle>(CIRCLE_POSITION, RADIUS);

    compositeShape.add(rect);
    compositeShape.add(circle);

    filimonova::point_t positionBeforeScaling = compositeShape.getPosition();

    compositeShape.scale(1.5);

    BOOST_CHECK_CLOSE(compositeShape.getPosition().x, positionBeforeScaling.x, EPSILON);
    BOOST_CHECK_CLOSE(compositeShape.getPosition().y, positionBeforeScaling.y, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(compositeShape_scale_correctCoefficient_changeFrameRect)
  {
    filimonova::CompositeShape compositeShape;

    std::shared_ptr<filimonova::Rectangle> rect = std::make_shared<filimonova::Rectangle>(WIDTH_1,
        HEIGHT_1, RECTANGLE_1_POSITION);
    std::shared_ptr<filimonova::Circle> circle = std::make_shared<filimonova::Circle>(CIRCLE_POSITION, RADIUS);

    compositeShape.add(rect);
    compositeShape.add(circle);

    filimonova::rectangle_t frameRectBeforeScaling = compositeShape.getFrameRect();

    const double coefficient = 1.5;
    compositeShape.scale(coefficient);

    BOOST_CHECK_CLOSE(compositeShape.getFrameRect().width, frameRectBeforeScaling.width * coefficient, EPSILON);
    BOOST_CHECK_CLOSE(compositeShape.getFrameRect().height, frameRectBeforeScaling.height * coefficient, EPSILON);

    BOOST_CHECK_CLOSE(compositeShape.getFrameRect().pos.x, frameRectBeforeScaling.pos.x, EPSILON);
    BOOST_CHECK_CLOSE(compositeShape.getFrameRect().pos.y, frameRectBeforeScaling.pos.y, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(compositeShape_scale_correctCoefficient_changeArea)
  {
    filimonova::CompositeShape compositeShape;

    std::shared_ptr<filimonova::Rectangle> rect = std::make_shared<filimonova::Rectangle>(WIDTH_1,
        HEIGHT_1, RECTANGLE_1_POSITION);
    std::shared_ptr<filimonova::Circle> circle = std::make_shared<filimonova::Circle>(CIRCLE_POSITION, RADIUS);

    compositeShape.add(rect);
    compositeShape.add(circle);

    const double areaBeforeScaling = compositeShape.getArea(), coefficient = 1.5;

    compositeShape.scale(coefficient);

    BOOST_CHECK_CLOSE(compositeShape.getArea(), areaBeforeScaling * coefficient * coefficient, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(compositeShape_scale_coefficientAs1_noChange)
  {
    filimonova::CompositeShape compositeShape;

    std::shared_ptr<filimonova::Rectangle> rect = std::make_shared<filimonova::Rectangle>(WIDTH_1,
        HEIGHT_1, RECTANGLE_1_POSITION);
    std::shared_ptr<filimonova::Circle> circle = std::make_shared<filimonova::Circle>(CIRCLE_POSITION, RADIUS);

    compositeShape.add(rect);
    compositeShape.add(circle);

    const double areaBeforeScaling = compositeShape.getArea(), coefficient = 1.0;
    filimonova::rectangle_t frameRectBeforeScaling = compositeShape.getFrameRect();
    filimonova::point_t positionBeforeScaling = compositeShape.getPosition();

    compositeShape.scale(coefficient);

    BOOST_CHECK_CLOSE(compositeShape.getArea(), areaBeforeScaling, EPSILON);

    BOOST_CHECK_CLOSE(compositeShape.getFrameRect().width, frameRectBeforeScaling.width, EPSILON);
    BOOST_CHECK_CLOSE(compositeShape.getFrameRect().height, frameRectBeforeScaling.height, EPSILON);

    BOOST_CHECK_CLOSE(compositeShape.getPosition().x, positionBeforeScaling.x, EPSILON);
    BOOST_CHECK_CLOSE(compositeShape.getPosition().y, positionBeforeScaling.y, EPSILON);
  }

BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(compositeShape_scale_inCorrectCoefficient)

  BOOST_AUTO_TEST_CASE(compositeShape_scale_inCorrectCoefficient_negativeNumberAsCoefficient_throw)
  {
    filimonova::CompositeShape compositeShape;

    std::shared_ptr<filimonova::Rectangle> rect = std::make_shared<filimonova::Rectangle>(WIDTH_1,
        HEIGHT_1, RECTANGLE_1_POSITION);
    std::shared_ptr<filimonova::Circle> circle = std::make_shared<filimonova::Circle>(CIRCLE_POSITION, RADIUS);

    compositeShape.add(rect);
    compositeShape.add(circle);

    BOOST_CHECK_THROW(compositeShape.scale(-5.7), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(compositeShape_scale_inCorrectCoefficient_nullAsCoefficient_throw)
  {
    filimonova::CompositeShape compositeShape;

    std::shared_ptr<filimonova::Rectangle> rect = std::make_shared<filimonova::Rectangle>(WIDTH_1,
        HEIGHT_1, RECTANGLE_1_POSITION);
    std::shared_ptr<filimonova::Circle> circle = std::make_shared<filimonova::Circle>(CIRCLE_POSITION, RADIUS);

    compositeShape.add(rect);
    compositeShape.add(circle);

    BOOST_CHECK_THROW(compositeShape.scale(0), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(compositeShape_rotate)

  BOOST_AUTO_TEST_CASE(compositeShape_rotate_notChangeArea)
  {
    filimonova::CompositeShape compositeShape;

    std::shared_ptr<filimonova::Rectangle> rect = std::make_shared<filimonova::Rectangle>(WIDTH_1,
        HEIGHT_1, RECTANGLE_1_POSITION);
    std::shared_ptr<filimonova::Circle> circle = std::make_shared<filimonova::Circle>(CIRCLE_POSITION, RADIUS);

    compositeShape.add(rect);
    compositeShape.add(circle);

    double areaBeforeRotating = compositeShape.getArea();

    compositeShape.rotate(30);

    BOOST_CHECK_CLOSE(areaBeforeRotating, compositeShape.getArea(), EPSILON);
  }

BOOST_AUTO_TEST_SUITE_END();
