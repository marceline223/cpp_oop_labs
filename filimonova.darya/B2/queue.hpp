#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <list>
#include <stdexcept>
#include <string>

template <typename T>
class QueueWithPriority
{
public:

  enum struct Priority
  {
    LOW,
    NORMAL,
    HIGH
  };

  QueueWithPriority();

  void add(const T &element, Priority priority);

  template <typename F>
  void popElement(F callBack);

  void accelerate();

  bool isEmpty() const;

private:
  std::list<T> queueLow_;
 
  std::list<T> queueNormal_;

  std::list<T> queueHigh_;
};

template <typename T>
QueueWithPriority<T>::QueueWithPriority() : 
  queueLow_(),
  queueNormal_(),
  queueHigh_()
{}

template <typename T>
void QueueWithPriority<T>::add(const T &element, Priority priority)
{
  switch (priority)
  {
  case Priority::LOW:
    queueLow_.push_back(element);
    break;

  case Priority::NORMAL:
    queueNormal_.push_back(element);
    break;

  case Priority::HIGH:
    queueHigh_.push_back(element);
    break;

  default:
    throw std::invalid_argument("Invalid priority of element.\n");
  }
}

template <typename T> 
template <typename F>
void QueueWithPriority<T>::popElement(F callBack)
{
  if (!queueHigh_.empty() && callBack(queueHigh_.front()))
  {
    queueHigh_.pop_front();
  }
  else if (!queueNormal_.empty() && callBack(queueNormal_.front()))
  {
    queueNormal_.pop_front();
  }
  else if (!queueLow_.empty() && callBack(queueLow_.front()))
  {
    queueLow_.pop_front();
  }
  else
  {
    throw std::runtime_error("Queue is empty.\n");
  }
}

template <typename T>
void QueueWithPriority<T>::accelerate()
{
  queueHigh_.splice(queueHigh_.end(), queueLow_);
}

template <typename T>
bool QueueWithPriority<T>::isEmpty() const
{
  return queueHigh_.empty() && queueNormal_.empty() && queueLow_.empty();
}

#endif
