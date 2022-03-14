#include "tasks.hpp"

#include <cstring>
#include <iostream>
#include <map>
#include <string>
#include <stdexcept>
#include <sstream>

#include "interface.hpp"

static void add(Interface &phonebook, std::istringstream &iss);

static void store(Interface &phonebook, std::istringstream &iss);

static void insert(Interface &phonebook, std::istringstream &iss);

static void deleteContact(Interface &phonebook, std::istringstream &iss);

static void show(Interface &phonebook, std::istringstream &iss);

static void move(Interface &phonebook, std::istringstream &iss);

namespace
{
  struct number_t
  {
    std::string str;
  };

  struct name_t
  {
    std::string str;
  };

  struct mark_name_t
  {
    std::string str;
  };

  const std::map<std::string, void (*)(Interface &, std::istringstream &)> commands
  {
    {"add", add},
    {"store", store},
    {"insert", insert},
    {"delete", deleteContact},
    {"show", show},
    {"move", move}
  };
}

static std::istringstream &operator>>(std::istringstream &in, name_t &name);

static std::istringstream &operator>>(std::istringstream &in, number_t &number);

static std::istringstream &operator>>(std::istringstream &in, mark_name_t &markName);

static bool areStepsValid(const std::string &steps);

void doTask1()
{
  std::string inputCommand;
  Interface phonebook;
  std::istringstream iss;

  while (std::getline(std::cin, inputCommand))
  {
    try
    {  
      iss.clear();      
      iss.str(inputCommand);

      std::string command;
      iss >> command >> std::ws;

      std::map<std::string, void (*)(Interface &, std::istringstream &)>::const_iterator itr = commands.find(command);

      if (itr == commands.end())
      {
        throw std::invalid_argument("<INVALID COMMAND>");
      }

      itr->second(phonebook, iss);
    }
    catch (const std::invalid_argument &exc)
    {
      std::cout << exc.what() << '\n';
    }
  }
}

static void add(Interface &phonebook, std::istringstream &iss)
{
  number_t argNumber;
  name_t argName;
  if (!(iss >> argNumber >> argName))
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }

  phonebook.add(argNumber.str, argName.str);
}

static void store(Interface &phonebook, std::istringstream &iss)
{
  mark_name_t argName;
  mark_name_t argNewName;

  if (!(iss >> argName >> argNewName))
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }

  phonebook.store(argName.str, argNewName.str);
}

static void insert(Interface &phonebook, std::istringstream &iss)
{
  std::string argPosition;
  mark_name_t argMarkName;
  number_t argNumber;
  name_t argName;

  iss >> argPosition >> std::ws;

  if (!(iss >> argMarkName >> argNumber >> argName))
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }

  if (argPosition == "before")
  {
    phonebook.insertBefore(argMarkName.str, argNumber.str, argName.str);
  }
  else if (argPosition == "after")
  {
    phonebook.insertAfter(argMarkName.str, argNumber.str, argName.str);
  }
  else
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
}

static void deleteContact(Interface &phonebook, std::istringstream &iss)
{
  mark_name_t argMarkName;

  if (!(iss >> argMarkName))
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }

  phonebook.deleteContact(argMarkName.str);
}

static void show(Interface &phonebook, std::istringstream &iss)
{
  mark_name_t argMarkName;

  if (!(iss >> argMarkName))
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }

  phonebook.show(argMarkName.str);
}

static void move(Interface &phonebook, std::istringstream &iss)
{
  mark_name_t argMarkName;

  if (!(iss >> argMarkName))
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }

  std::string argSteps;
  iss >> std::ws >> argSteps;

  if (!areStepsValid(argSteps))
  {
    throw std::invalid_argument("<INVALID STEP>");
  }

  if (argSteps == "first")
  {
    phonebook.moveToFirst(argMarkName.str);
  }
  else if (argSteps == "last")
  {
    phonebook.moveToLast(argMarkName.str);
  }
  else
  {
    int steps = std::stoi(argSteps);

    phonebook.move(argMarkName.str, steps);
  }
}

static bool areStepsValid(const std::string &steps)
{
  if (steps.empty())
  {
    return false;
  }
  if ((steps == "first") || (steps == "last"))
  {
    return true;
  }
  if (((steps[0] != '+') && (steps[0] != '-') && (!std::isdigit(steps[0]))))
  {
    return false;
  }
  for (size_t i = 0; i < steps.length(); i++)
  {
    if (!std::isdigit(steps[i]) && (i != 0))
    {
      return false;
    }
  }
  return true;
}

static std::istringstream &operator>>(std::istringstream &in, name_t &name)
{
  std::ios_base::fmtflags flags = in.flags();
  in >> std::ws;

  char c = ' ';
  if (!(in >> c) || (c != '"'))
  {
    in.setf(flags);
    in.setstate(std::ios_base::failbit);
    return in;
  }

  in >> std::noskipws;
  in >> c;

  while (in.good())
  {
    name.str.push_back(c);

    in >> c;

    if ((c == '\"') && (name.str.back() != '\\'))
    {
      break;
    }

    if (((c == '"') || (c == '\\')) && (name.str.back() == '\\'))
    {
      name.str.pop_back();
    }
  }

  in.setf(flags);
  return in;
}

static std::istringstream &operator>>(std::istringstream &in, number_t &number)
{
  std::ios_base::fmtflags flags = in.flags();
  char c = ' ';
  in >> std::ws >> std::noskipws;

  while ((in >> c) && (c != ' '))
  {
    if (!isdigit(c))
    {
      in.setf(flags);
      in.setstate(std::ios_base::failbit);
      return in;
    }

    number.str.push_back(c);
  }

  in.setf(flags);
  return in;
}

static std::istringstream &operator>>(std::istringstream &in, mark_name_t &markName)
{
  std::ios_base::fmtflags flags = in.flags();
  in >> std::ws >> std::noskipws;
  in >> markName.str;

  if (markName.str.empty())
  {
    in.setf(flags);
    in.setstate(std::ios_base::failbit);
    return in;
  }

  for (size_t i = 0; i < markName.str.length(); i++)
  {
    if ((!std::isalnum(markName.str[i])) && (markName.str[i] != '-'))
    {
      in.setf(flags);
      in.setstate(std::ios_base::failbit);
      return in;
    }
  }

  in.setf(flags);
  return in;
}
