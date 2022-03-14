#include <cstring>
#include <iostream>
#include <stdexcept>

#include "tasks.hpp"

int main(int argc, char **argv)
{
  if (argc == 1)
  {
    std::cerr << "Invalid input: there is no arguments.\n";
    return 1;
  }

  if (argv[1] == nullptr)
  {
    std::cerr << "Invalid input of the task number.\n";
    return 1;
  }

  int number = 0;
  try
  {
    std::size_t pos = 0;
    number = std::stoi(argv[1], &pos);

    if (pos != std::strlen(argv[1]))
    {
      std::cerr << "Invalid number of the task. Number can be 1 or 2.\n";
      return 1;
    }
  }
  catch (const std::invalid_argument &exc)
  {
    std::cerr << "Invalid number of the task. Number can be 1 or 2.\n";
    return 1;
  }
  catch (const std::out_of_range &exc)
  {
    std::cerr << "Invalid number of the task. Number can be 1 or 2.\n";
    return 1;
  }

  switch (number)
  {
  case 1:

    if (argc != 2)
    {
      std::cerr << "Invalid input: task 1 doesn't require any additional arguments.\n";
      return 1;
    }

    try
    {
      doTask1();
    }
    catch (const std::invalid_argument &exc)
    {
      std::cerr << exc.what() << '\n';
      return 1;
    }

    break;

  case 2:

    if (argc != 2)
    {
      std::cerr << "Invalid input: task 2 doesn't require any additional arguments.\n";
      return 1;
    }

    try
    {
      doTask2();
    }
    catch (const std::invalid_argument &exc)
    {
      std::cerr << exc.what() << '\n';
      return 1;
    }

    break;

  default:
    std::cerr << "Invalid number of the task. Number can be 1 or 2.\n";
    return 1;
  }

  return 0;
}

