#ifndef BASE_TYPES_H
#define BASE_TYPES_H

namespace filimonova
{
  struct point_t
  {
    double x;
    double y;
  };

  struct rectangle_t
  {
    double width;
    double height;
    point_t pos;
  };

  bool areIntersecting(const rectangle_t& rect1, const rectangle_t& rect2);
}

#endif
