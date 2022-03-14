#include "guard.hpp"

#include <istream>

Guard::Guard(std::istream &in) :
  in_(in),
  flags_(in.flags())
{ }

Guard::~Guard()
{
  in_.setf(flags_);
}
