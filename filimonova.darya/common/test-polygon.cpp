#include <boost/test/unit_test.hpp>

#include <stdexcept>
#include <initializer_list>

#include "polygon.hpp"
#include "base-types.hpp"

const double EPSILON = 0.0001;

const filimonova::point_t POINT1{5, 3};

const filimonova::point_t POINT2{1, 6};

const filimonova::point_t POINT3{-2, 2};

BOOST_AUTO_TEST_SUITE(polygon_validConstructor)

  BOOST_AUTO_TEST_CASE(polygon_validConstructor_noThrow)
  {
    BOOST_CHECK_NO_THROW(
        filimonova::Polygon polygon(std::initializer_list<filimonova::point_t>{POINT1, POINT2, POINT3}));
  }

  BOOST_AUTO_TEST_CASE(polygon_validConstructor_getterOfSize)
  {
    filimonova::Polygon polygon(std::initializer_list<filimonova::point_t>{POINT1, POINT2, POINT3});

    BOOST_CHECK_EQUAL(polygon.getSize(), 3);
  }

BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(polygon_invalidConstructor)

  BOOST_AUTO_TEST_CASE(polygon_invalidConstructor_twoPoints_throw)
  {
    BOOST_CHECK_THROW(filimonova::Polygon polygon(std::initializer_list<filimonova::point_t>{POINT1, POINT2}),
        std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(polygon_invalidConstructor_pointsOnTheSameLine)
  {
    filimonova::point_t point1{0, 0};
    filimonova::point_t point2{1, 1};
    filimonova::point_t point3{2, 2};
    BOOST_CHECK_THROW(filimonova::Polygon polygon(std::initializer_list<filimonova::point_t>{point1, point2, point3}),
        std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(polygon_getArea)

  BOOST_AUTO_TEST_CASE(polygon_getArea_close)
  {
    filimonova::Polygon polygon(std::initializer_list<filimonova::point_t>{POINT1, POINT2, POINT3});

    double area = std::abs((
        POINT1.x * POINT2.y + POINT2.x * POINT3.y + POINT3.x * POINT1.y - POINT1.y * POINT2.x - POINT2.y * POINT3.x -
            POINT3.y * POINT1.x)) / 2;

    BOOST_CHECK_CLOSE(area, polygon.getArea(), EPSILON);
  }

BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(polygon_frameRect)

  BOOST_AUTO_TEST_CASE(polygon_frameRect_parametersClose)
  {
    filimonova::Polygon polygon(std::initializer_list<filimonova::point_t>{POINT1, POINT2, POINT3});

    filimonova::rectangle_t frameRect = polygon.getFrameRect();

    double minX = std::min(POINT1.x, std::min(POINT2.x, POINT3.x));
    double minY = std::min(POINT1.y, std::min(POINT2.y, POINT3.y));
    double maxX = std::max(POINT1.x, std::max(POINT2.x, POINT3.x));
    double maxY = std::max(POINT1.y, std::max(POINT2.y, POINT3.y));

    BOOST_CHECK_CLOSE(frameRect.pos.x, (maxX + minX) / 2, EPSILON);
    BOOST_CHECK_CLOSE(frameRect.pos.y, (maxY + minY) / 2, EPSILON);
    BOOST_CHECK_CLOSE(frameRect.width, maxX - minX, EPSILON);
    BOOST_CHECK_CLOSE(frameRect.height, maxY - minY, EPSILON);
  }

BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(polygon_getPosition)

  BOOST_AUTO_TEST_CASE(polygon_getPosition_close)
  {
    filimonova::Polygon polygon(std::initializer_list<filimonova::point_t>{POINT1, POINT2, POINT3});

    filimonova::point_t position = {(POINT1.x + POINT2.x + POINT3.x) / 3, (POINT1.y + POINT2.y + POINT3.y) / 3};

    BOOST_CHECK_CLOSE(polygon.getPosition().x, position.x, EPSILON);
    BOOST_CHECK_CLOSE(polygon.getPosition().y, position.y, EPSILON);
  }

BOOST_AUTO_TEST_SUITE_END();


BOOST_AUTO_TEST_SUITE(polygon_indexOperator_correctIndex)

  BOOST_AUTO_TEST_CASE(polygon_indexOperator_correctIndex_noThrow)
  {
    filimonova::Polygon polygon(std::initializer_list<filimonova::point_t>{POINT1, POINT2, POINT3});

    BOOST_CHECK_NO_THROW(polygon[0]);
  }

  BOOST_AUTO_TEST_CASE(polygon_indexOperator_correctIndex_correctPoint)
  {
    filimonova::Polygon polygon(std::initializer_list<filimonova::point_t>{POINT1, POINT2, POINT3});

    BOOST_CHECK_CLOSE(polygon[0].x, POINT1.x, EPSILON);
    BOOST_CHECK_CLOSE(polygon[0].y, POINT1.y, EPSILON);
    BOOST_CHECK_CLOSE(polygon[1].x, POINT2.x, EPSILON);
    BOOST_CHECK_CLOSE(polygon[1].y, POINT2.y, EPSILON);
    BOOST_CHECK_CLOSE(polygon[2].x, POINT3.x, EPSILON);
    BOOST_CHECK_CLOSE(polygon[2].y, POINT3.y, EPSILON);
  }

BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(polygon_indexOperator_incorrectIndex)

  BOOST_AUTO_TEST_CASE(polygon_indexOperator_incorrectIndex_throw)
  {
    filimonova::Polygon polygon(std::initializer_list<filimonova::point_t>{POINT1, POINT2, POINT3});

    BOOST_CHECK_THROW(polygon[5], std::out_of_range);
  }

BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(polygon_moveToPoint)

  BOOST_AUTO_TEST_CASE(polygon_moveToPoint_notChangeArea)
  {
    filimonova::Polygon polygon(std::initializer_list<filimonova::point_t>{POINT1, POINT2, POINT3});

    double areaBeforeMoving = polygon.getArea();

    polygon.move({1.5, 5.1});
    BOOST_CHECK_CLOSE(areaBeforeMoving, polygon.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(polygon_moveToPoint_changePosition)
  {
    filimonova::Polygon polygon(std::initializer_list<filimonova::point_t>{POINT1, POINT2, POINT3});

    filimonova::point_t positionBeforeMoving = polygon.getPosition();
    filimonova::point_t newPoint{1.5, 5.1};
    double dX = newPoint.x - positionBeforeMoving.x;
    double dY = newPoint.y - positionBeforeMoving.y;

    polygon.move(newPoint);
    BOOST_CHECK_CLOSE(positionBeforeMoving.x + dX, polygon.getPosition().x, EPSILON);
    BOOST_CHECK_CLOSE(positionBeforeMoving.y + dY, polygon.getPosition().y, EPSILON);
  }

BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(polygon_moveByXY)

  BOOST_AUTO_TEST_CASE(polygon_moveByXY_notChangeArea)
  {
    filimonova::Polygon polygon(std::initializer_list<filimonova::point_t>{POINT1, POINT2, POINT3});

    double areaBeforeMoving = polygon.getArea();
    double dX = -6;
    double dY = 3.5;

    polygon.move(dX, dY);
    BOOST_CHECK_CLOSE(areaBeforeMoving, polygon.getArea(), EPSILON);
  }

  BOOST_AUTO_TEST_CASE(polygon_moveByXY_changePosition)
  {
    filimonova::Polygon polygon(std::initializer_list<filimonova::point_t>{POINT1, POINT2, POINT3});

    filimonova::point_t positionBeforeMoving = polygon.getPosition();
    double dX = -6;
    double dY = 3.5;

    polygon.move(dX, dY);
    BOOST_CHECK_CLOSE(positionBeforeMoving.x + dX, polygon.getPosition().x, EPSILON);
    BOOST_CHECK_CLOSE(positionBeforeMoving.y + dY, polygon.getPosition().y, EPSILON);
  }

BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(polygon_scale_correctCoefficient)

  BOOST_AUTO_TEST_CASE(polygon_scale_correctCoefficient_noThrow)
  {
    filimonova::Polygon polygon(std::initializer_list<filimonova::point_t>{POINT1, POINT2, POINT3});

    BOOST_CHECK_NO_THROW(polygon.scale(2));
  }

  BOOST_AUTO_TEST_CASE(polygon_scale_correctCoefficient_notChangePosition)
  {
    filimonova::Polygon polygon(std::initializer_list<filimonova::point_t>{POINT1, POINT2, POINT3});

    filimonova::point_t positionBeforeScaling = polygon.getPosition();

    polygon.scale(2);

    BOOST_CHECK_CLOSE(positionBeforeScaling.x, polygon.getPosition().x, EPSILON);
    BOOST_CHECK_CLOSE(positionBeforeScaling.y, polygon.getPosition().y, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(polygon_scale_correctCoefficient_changeFrameRect)
  {
    filimonova::Polygon polygon(std::initializer_list<filimonova::point_t>{POINT1, POINT2, POINT3});

    filimonova::rectangle_t frameRectBeforeScaling = polygon.getFrameRect();
    polygon.scale(2);

    BOOST_CHECK_CLOSE(frameRectBeforeScaling.width * 2, polygon.getFrameRect().width, EPSILON);
    BOOST_CHECK_CLOSE(frameRectBeforeScaling.height * 2, polygon.getFrameRect().height, EPSILON);
  }

BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(polygon_scale_incorrectCoefficient)

  BOOST_AUTO_TEST_CASE(polygon_scale_incorrectCoefficient_throw)
  {
    filimonova::Polygon polygon(std::initializer_list<filimonova::point_t>{POINT1, POINT2, POINT3});

    BOOST_CHECK_THROW(polygon.scale(-2), std::invalid_argument);
    BOOST_CHECK_THROW(polygon.scale(0), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(polygon_rotate)

  BOOST_AUTO_TEST_CASE(polygon_rotate_notChangePosition)
  {
    filimonova::Polygon polygon(std::initializer_list<filimonova::point_t>{POINT1, POINT2, POINT3});

    filimonova::point_t positionBeforeRotating = polygon.getPosition();
    polygon.rotate(30);

    BOOST_CHECK_CLOSE(positionBeforeRotating.x, polygon.getPosition().x, EPSILON);
    BOOST_CHECK_CLOSE(positionBeforeRotating.y, polygon.getPosition().y, EPSILON);
  }

  BOOST_AUTO_TEST_CASE(polygon_rotate_notChangeArea)
  {
    filimonova::Polygon polygon(std::initializer_list<filimonova::point_t>{POINT1, POINT2, POINT3});

    double areaBeforeRotating = polygon.getArea();
    polygon.rotate(90);

    BOOST_CHECK_CLOSE(areaBeforeRotating, polygon.getArea(), EPSILON);
  }

BOOST_AUTO_TEST_SUITE_END();
