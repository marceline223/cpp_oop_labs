#include "tasks.hpp"

#include <algorithm>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "figures.hpp"

void doTask2()
{
  std::vector<std::shared_ptr<Shape>> vector;
  std::string str;

  while (std::getline(std::cin, str))
  {
    if (std::cin.fail())
    {
      throw std::runtime_error("Invalid input\n");
    }

    std::stringstream stream(str);
    std::string shape;
    stream >> shape;

    if (shape.empty())
    {
      continue;
    }

    size_t openBracket = shape.find_first_of('(');

    size_t noPosition = std::string::npos;
    if (openBracket != noPosition)
    {
      std::getline(stream, str);
      str.insert(0, shape.substr(openBracket, shape.length()));
      shape.erase(openBracket, shape.length());
    }
    else
    {
      std::getline(stream, str);
    }

    if ((shape != "CIRCLE") && (shape != "TRIANGLE") && (shape != "SQUARE"))
    {
      throw std::invalid_argument("Invalid input of shape\n");
    }

    openBracket = str.find_first_of('(');
    size_t colon = str.find_first_of(';');
    size_t closeBracket = str.find_first_of(')');

    if ((openBracket == noPosition) || (colon == noPosition) || (closeBracket == noPosition))
    {
      throw std::invalid_argument("Invalid input of point\n");
    }

    int x = std::stoi(str.substr(openBracket + 1, colon - (openBracket + 1)));
    int y = std::stoi(str.substr(colon + 1, closeBracket - (colon + 1)));

    str.erase(0, closeBracket + 1);
    stream << str;

    if (!stream.eof())
    {
      throw std::invalid_argument("Invalid input\n");
    }

    if (shape == "CIRCLE")
    {
      vector.push_back(std::make_shared<Circle>(Circle({x, y})));
    }

    if (shape == "TRIANGLE")
    {
      vector.push_back(std::make_shared<Triangle>(Triangle({x, y})));
    }

    if (shape == "SQUARE")
    {
      vector.push_back(std::make_shared<Square>(Square({x, y})));
    }
  }

  auto print = [](const std::shared_ptr<Shape> &shape){shape->draw(std::cout);};

  std::cout << "Original:" << std::endl;
  std::for_each(vector.begin(), vector.end(), print);

  auto sortLeft = [](const std::shared_ptr<Shape> &shape1, const std::shared_ptr<Shape> &shape2){return shape1->isMoreLeft(shape2);};

  std::cout << "Left-Right:" << std::endl;
  std::sort(vector.begin(), vector.end(), sortLeft);
  std::for_each(vector.begin(), vector.end(), print);

  std::cout << "Right-Left:" << std::endl;
  std::for_each(vector.rbegin(), vector.rend(), print);

  auto sortUp = [](const std::shared_ptr<Shape> &shape1, const std::shared_ptr<Shape> &shape2){return shape1->isUpper(shape2);};

  std::cout << "Top-Bottom:" << std::endl;
  std::sort(vector.begin(), vector.end(), sortUp);
  std::for_each(vector.begin(), vector.end(), print);

  std::cout << "Bottom-Top:" << std::endl;
  std::for_each(vector.rbegin(), vector.rend(), print);
}
