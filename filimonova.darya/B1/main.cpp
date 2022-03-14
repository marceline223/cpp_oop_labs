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
      std::cerr << "Invalid number of the task. Number can be 1, 2, 3 or 4.\n";
      return 1;
    }
  }
  catch (const std::invalid_argument &exc)
  {
    std::cerr << "Invalid number of the task. Number can be 1, 2, 3 or 4.\n";
    return 1;
  }
  catch (const std::out_of_range &exc)
  {
    std::cerr << "Invalid number of the task. Number can be 1, 2, 3 or 4.\n";
    return 1;
  }

  switch (number)
  {
  case 1:
    if (argc != 3)
    {
      std::cerr << "Invalid input: task 1 requires 1 additional argument - ascending or descending.\n";
      return 1;
    }
    if (argv[2] == nullptr)
    {
      std::cerr << "Empty input in the task 1.\n";
      return 1;
    }

    try
    {
      doTask1(argv[2]);
    }
    catch (const std::invalid_argument &exc)
    {
      std::cerr << exc.what() << '\n';
      return 1;
    }
    catch (const std::runtime_error &exc)
    {
      std::cerr << exc.what() << '\n';
      return 1;
    }
    break;

  case 2:
    if (argc != 3)
    {
      std::cerr << "Invalid input: task 2 requires 1 additional argument - name of input file.\n";
      return 1;
    }
    if (argv[2] == nullptr)
    {
      std::cerr << "Empty input in the task 2.\n";
      return 1;
    }

    try
    {
      doTask2(argv[2]);
    }
    catch (const std::invalid_argument &exc)
    {
      std::cerr << exc.what() << '\n';
      return 1;
    }
    catch (const std::runtime_error &exc)
    {
      std::cerr << exc.what() << '\n';
      return 1;
    }
    break;

  case 3:
    if (argc != 2)
    {
      std::cerr << "Invalid input: task 3 doesn't require any additional arguments.\n";
      return 1;
    }

    try
    {
      doTask3();
    }
    catch (const std::runtime_error &exc)
    {
      std::cerr << exc.what() << '\n';
      return 1;
    }
    break;

  case 4:
  {
    if (argc != 4)
    {
      std::cerr << "Invalid input: task 4 requires 2 additional arguments - ascending or descending and size of vector.\n";
      return 1;
    }

    if ((argv[2] == nullptr) || (argv[3] == nullptr))
    {
      std::cerr << "Empty input in the task 4.\n";
      return 1;
    }

    int size = 0;

    try
    {
      std::size_t pos = 0;
      size = std::stoi(argv[3], &pos);

      if (pos != std::strlen(argv[3]))
      {
        std::cerr << "Invalid size of vector in the task 4, it must be integer.\n";
        return 1;
      }
    }
    catch (const std::invalid_argument &exc)
    {
      std::cerr << "Invalid size of vector in the task 4.\n";
      return 1;
    }
    catch (const std::out_of_range &exc)
    {
      std::cerr << "Invalid size of vector in the task 4: size is out of range.\n";
      return 1;
    }

    try
    {
      doTask4(argv[2], size);
    }
    catch (const std::invalid_argument &exc)
    {
      std::cerr << exc.what() << '\n';
      return 1;
    }
    break;
  }

  default:
    std::cerr << "Invalid number of the task. Number can be 1, 2, 3 or 4.\n";
    return 1;
  }

  return 0;
}
