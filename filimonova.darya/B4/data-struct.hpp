#ifndef DATA_STRUCT
#define DATA_STRUCT

#include <iostream>
#include <string>

struct DataStruct
{
  int key1;
  int key2;
  std::string str;

  bool operator<(const DataStruct &other) const;
};

std::istream &operator>>(std::istream &in, DataStruct &data);
std::ostream &operator<<(std::ostream &out, const DataStruct &data);

#endif
