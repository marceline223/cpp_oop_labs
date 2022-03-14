#include "data-struct.hpp"

#include <iostream>
#include <string>

#include "guard.hpp"

static const int MIN_KEY = -5;
static const int MAX_KEY = 5;

bool DataStruct::operator<(const DataStruct &other) const
{
  if (key1 != other.key1)
  {
    return key1 < other.key1;
  }
  else if (key2 != other.key2)
  {
    return key2 < other.key2;
  }
  else
  {
    return str.size() < other.str.size();
  }
}

std::istream &ignoreBlanks(std::istream &in)
{
  while (std::isblank(in.peek()))
  {
    in.ignore();
  }
  return in;
}

std::istream &operator>>(std::istream &in, DataStruct &data)
{
  Guard guard(in);
  in >> std::noskipws;

  int key1 = 0;
  if (!(in >> ignoreBlanks >> key1) || (key1 > MAX_KEY) || (key1 < MIN_KEY))
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  char c = ' ';
  if (!(in >> ignoreBlanks >> c) || (c != ','))
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  int key2 = 0;
  if (!(in >> ignoreBlanks >> key2) || (key2 > MAX_KEY) || (key2 < MIN_KEY))
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  
  if (!(in >> ignoreBlanks >> c) || (c != ','))
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  std::string str;
  std::getline(in >> ignoreBlanks, str);
  if (!in.eof() && in.fail())
  {
    return in;
  }

  data.key1 = key1;
  data.key2 = key2;
  data.str = str;

  return in;
}

std::ostream &operator<<(std::ostream &out, const DataStruct &data)
{
  out << data.key1 << ',' << data.key2 << ',' << data.str;
  return out;
}
