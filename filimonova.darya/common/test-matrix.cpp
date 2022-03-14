#include <boost/test/unit_test.hpp>

#include <stdexcept>

#include "matrix.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include "base-types.hpp"

BOOST_AUTO_TEST_SUITE(matrix_validConstructorWithoutParameters)

  BOOST_AUTO_TEST_CASE(matrix_validConstructorWithoutParameters_noThrow)
  {
    BOOST_CHECK_NO_THROW(filimonova::Matrix matrix);
  }

  BOOST_AUTO_TEST_CASE(matrix_validConstructorWithoutParameters_nullSize)
  {
    filimonova::Matrix matrix;
    BOOST_CHECK_EQUAL(matrix.getAmountOfLayers(), 0);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(matrix_addFigures)

  BOOST_AUTO_TEST_CASE(matrix_addFigures_addNullptr_throw)
  {
    filimonova::Matrix matrix;
    std::shared_ptr<filimonova::Rectangle> rect1 = nullptr;
    BOOST_CHECK_THROW(matrix.add(rect1), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(matrix_addFigures_correctDistributionToLayers_getAmountOfLayers_getSizeOfLayer)
  {
    filimonova::Matrix matrix;
    std::shared_ptr<filimonova::Rectangle> rect1 = std::make_shared<filimonova::Rectangle>(1,
        2, filimonova::point_t{-5.5, -3});
    std::shared_ptr<filimonova::Rectangle> rect2 = std::make_shared<filimonova::Rectangle>(2,
        1, filimonova::point_t{3, 8});
    std::shared_ptr<filimonova::Circle> circle = std::make_shared<filimonova::Circle>(filimonova::point_t{3, -3}, 100);

    matrix.add(rect1);
    matrix.add(rect2);
    matrix.add(circle);

    BOOST_CHECK_EQUAL(matrix.getAmountOfLayers(), 2);

    BOOST_CHECK_EQUAL(matrix.getSizeOfLayer(0), 2);
    BOOST_CHECK_EQUAL(matrix.getSizeOfLayer(1), 1);

    BOOST_CHECK(matrix[0][0] == rect1);
    BOOST_CHECK(matrix[0][1] == rect2);
    BOOST_CHECK(matrix[1][0] == circle);
  }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(matrix_indexOperator)

  BOOST_AUTO_TEST_CASE(matrix_indexOperator_correctIndex_correctShapes)
  {
    filimonova::Matrix matrix;
    std::shared_ptr<filimonova::Rectangle> rect1 = std::make_shared<filimonova::Rectangle>(1,
        2, filimonova::point_t{-5.5, -3});
    std::shared_ptr<filimonova::Rectangle> rect2 = std::make_shared<filimonova::Rectangle>(2,
        1, filimonova::point_t{3, 8});
    std::shared_ptr<filimonova::Circle> circle = std::make_shared<filimonova::Circle>(filimonova::point_t{3, -3}, 100);

    matrix.add(rect1);
    matrix.add(rect2);
    matrix.add(circle);

    BOOST_CHECK_THROW(matrix[5], std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(matrix_indexOperator_inCorrectIndex_throw)
  {
    filimonova::Matrix matrix;
    std::shared_ptr<filimonova::Rectangle> rect1 = std::make_shared<filimonova::Rectangle>(1,
        2, filimonova::point_t{-5.5, -3});
    std::shared_ptr<filimonova::Rectangle> rect2 = std::make_shared<filimonova::Rectangle>(2,
        1, filimonova::point_t{3, 8});
    std::shared_ptr<filimonova::Circle> circle = std::make_shared<filimonova::Circle>(filimonova::point_t{3, -3}, 100);

    matrix.add(rect1);
    matrix.add(rect2);
    matrix.add(circle);

    BOOST_CHECK_THROW(matrix[5][0], std::out_of_range);
    BOOST_CHECK_THROW(matrix[0][2], std::out_of_range);
  }

BOOST_AUTO_TEST_SUITE_END()
