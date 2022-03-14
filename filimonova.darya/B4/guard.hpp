#ifndef GUARD
#define GUARD

#include <istream>

class Guard
{
public:

  Guard(std::istream &in);

  ~Guard();

private:

  std::istream &in_;

  std::ios_base::fmtflags flags_;
};

#endif
