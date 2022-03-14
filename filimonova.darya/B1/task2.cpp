#include "tasks.hpp"

#include <algorithm>
#include <fstream>
#include <memory>
#include <vector>

#include "details.hpp"

void doTask2(const char *nameOfFile)
{
  if (nameOfFile == nullptr)
  {
    throw std::invalid_argument("Invalid input in the task 2: invalid name of file.\n");
  }

  std::ifstream fileIn(nameOfFile);

  if (!fileIn)
  {
    throw std::invalid_argument("Invalid input in the task 2: invalid name of file.\n");
  }
  size_t currentSize = 5;

  std::unique_ptr<char[]> array = std::make_unique<char[]>(currentSize);

  size_t realSize = 0;

  const size_t sizeCoef = 2;
  while (fileIn)
  {
    fileIn.read(array.get() + realSize, currentSize - realSize);
    realSize += fileIn.gcount();

    if (realSize == currentSize)
    {
      currentSize *= sizeCoef;
      std::unique_ptr<char[]> newArray = std::make_unique<char[]>(currentSize);
      std::copy(array.get(), array.get() + realSize, newArray.get());
      array.swap(newArray);
    }
  }

  if (!fileIn.eof())
  {
    throw std::runtime_error("Invalid input in the task 2: invalid vector.\n");
  }

  std::vector<char> outputVector(array.get(), array.get() + realSize);

  print(outputVector, false);
}
