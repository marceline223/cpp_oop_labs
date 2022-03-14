#include "factorial-container.hpp"

#include <stdexcept>

namespace detail
{
  constexpr unsigned int calculateFactorial(unsigned int index)
  {
    unsigned int result = 1;
    for (unsigned int i = 2; i <= index; i++)
    {
      result *= i;
    }
    return result;
  }

  static const unsigned int INDEX_MIN = 1;

  static const unsigned int INDEX_MAX = 11;

  static const unsigned int FACTORIAL_MIN = 1;

  constexpr unsigned int FACTORIAL_MAX = calculateFactorial(INDEX_MAX);
}

FactorialContainer::FactorialIterator::FactorialIterator(unsigned int index) : 
    index_(index),
    factorial_(detail::calculateFactorial(index))
{
  if ((index < detail::INDEX_MIN) || (index > detail::INDEX_MAX))
  {
    throw std::out_of_range("Invalid index. It can't be more than 10 or less than 1.\n");
  }
}

FactorialContainer::FactorialIterator::FactorialIterator(unsigned int index, unsigned int factorial) :
    index_(index),
    factorial_(factorial)
{
  if ((index < detail::INDEX_MIN) || (index > detail::INDEX_MAX))
  {
    throw std::out_of_range("Invalid index. It can't be more than 10 or less than 1.\n");
  }
}

FactorialContainer::FactorialIterator FactorialContainer::begin() const
{
  return {detail::INDEX_MIN, detail::FACTORIAL_MIN};
}

FactorialContainer::FactorialIterator FactorialContainer::end() const
{
  return {detail::INDEX_MAX, detail::FACTORIAL_MAX};
}

FactorialContainer::reverse_iterator FactorialContainer::rbegin() const
{
  return std::make_reverse_iterator(end());
}

FactorialContainer::reverse_iterator FactorialContainer::rend() const
{
  return std::make_reverse_iterator(begin());
}

unsigned int &FactorialContainer::FactorialIterator::operator*()
{
  return factorial_;
}

FactorialContainer::FactorialIterator &FactorialContainer::FactorialIterator::operator++()
{
  index_++;
  if (index_ > detail::INDEX_MAX)
  {
    throw std::out_of_range("Invalid index. It can't be more than 11.\n");
  }
  factorial_ *= index_;
  return *this;
}

FactorialContainer::FactorialIterator FactorialContainer::FactorialIterator::operator++(int)
{
  FactorialIterator temp = *this;

  this->operator++();

  return temp;
}

FactorialContainer::FactorialIterator &FactorialContainer::FactorialIterator::operator--()
{
  if (index_ <= detail::INDEX_MIN)
  {
    throw std::out_of_range("Invalid index. It can't be less than 1.\n");
  }
  factorial_ /= index_;
  index_--;
  return *this;
}

FactorialContainer::FactorialIterator FactorialContainer::FactorialIterator::operator--(int)
{
  FactorialIterator temp = *this;

  this->operator--();

  return temp;
}

bool FactorialContainer::FactorialIterator::operator==(const FactorialContainer::FactorialIterator &itr) const
{
  return index_ == itr.index_;
}

bool FactorialContainer::FactorialIterator::operator!=(const FactorialContainer::FactorialIterator &itr) const
{
  return index_ != itr.index_;
}
