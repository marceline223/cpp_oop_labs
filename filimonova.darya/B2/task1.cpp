#include "tasks.hpp"

#include <iostream>
#include <string>
#include <sstream>

#include "queue.hpp"

enum struct Command
{
  ADD,
  GET,
  ACCELERATE,
  INVALID_COMMAND
};

Command handleCommand(std::istringstream &iss);

static void add(QueueWithPriority<std::string> &queue, std::istringstream &iss);

static void get(QueueWithPriority<std::string> &queue);

static void accelerate(QueueWithPriority<std::string> &queue);

void doTask1()
{
  std::string command;
  QueueWithPriority<std::string> queue;

  std::istringstream iss;
  while (std::getline(std::cin, command))
  {
    iss.clear();
    iss.str(command);
    switch (handleCommand(iss))
    {
    case Command::ADD:
      add(queue, iss);
      break;
    case Command::GET:
      get(queue);
      break;
    case Command::ACCELERATE:
      accelerate(queue);
      break;
    case Command::INVALID_COMMAND:
      std::cout << "<INVALID COMMAND>\n";
    default:
      break;
    }
  }

  if (!std::cin.eof())
  {
    throw std::runtime_error("Invalid input in the task 1.\n");
  }
}

Command handleCommand(std::istringstream &iss)
{
  std::string command;
  iss >> command >> std::ws;

  if ((command == "get") && iss.eof())
  {
    return Command::GET;
  }
  else if ((command == "accelerate") && iss.eof())
  {
    return Command::ACCELERATE;
  }
  else if ((command == "add") && !iss.eof())
  {
    return Command::ADD;
  }
  else
  {
    return Command::INVALID_COMMAND;
  }
}

static void add(QueueWithPriority<std::string> &queue, std::istringstream &iss)
{
  std::string argPriority;
  if (!(iss >> argPriority))
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }

  QueueWithPriority<std::string>::Priority priority;
  if (argPriority == "low")
  {
    priority = QueueWithPriority<std::string>::Priority::LOW;
  }
  else if (argPriority == "normal")
  {
    priority = QueueWithPriority<std::string>::Priority::NORMAL;
  }
  else if (argPriority == "high")
  {
    priority = QueueWithPriority<std::string>::Priority::HIGH;
  }
  else
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }

  std::string argElement;
  iss >> std::ws;
  if (!std::getline(iss, argElement))
  {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }

  queue.add(argElement, priority);
}

static void get(QueueWithPriority<std::string> &queue)
{
  if (queue.isEmpty())
  {
    std::cout << "<EMPTY>\n";
    return;
  }
  queue.popElement([](std::string& element) {
    std::cout << element << '\n';  
    return true;
  });
}

static void accelerate(QueueWithPriority<std::string> &queue)
{
  queue.accelerate();
}
