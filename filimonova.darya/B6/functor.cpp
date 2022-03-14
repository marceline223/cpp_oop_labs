#include "functor.hpp"

#include <algorithm>
#include <iomanip>
#include <iostream>

Functor::Functor() : 
  amountOfElements_(0),
  maxElement_(0),
  minElement_(0),
  firstElement_(0),
  lastElement_(0),
  average_(0.0),
  amountOfPositiveElements_(0),
  amountOfNegativeElements_(0),
  sumOfOddElements_(0),
  sumOfEvenElements_(0),
  isEmpty_(true)
{
}

void Functor::operator()(int n)
{
  if (isEmpty_)
  {
    maxElement_ = n;
    minElement_ = n;
    firstElement_ = n;
    isEmpty_ = false;
  }
  maxElement_ = std::max(maxElement_, n);
  minElement_ = std::min(minElement_, n);
  amountOfElements_++;
  lastElement_ = n;

  if (n > 0)
  {
    amountOfPositiveElements_++;
  }
  else if (n < 0)
  {
    amountOfNegativeElements_++;
  }
  if (n % 2 == 0)
  {
    sumOfEvenElements_ += n;
  }
  else
  {
    sumOfOddElements_ += n;
  }
  average_ = static_cast<double>(sumOfEvenElements_ + sumOfOddElements_) / amountOfElements_;
}

void Functor::printStatistic(std::ostream &out) const
{
  if (isEmpty_)
  {
    out << "No Data\n";
    return;
  }

  out << "Max: " << maxElement_ << '\n';
  out << "Min: " << minElement_ << '\n';
  out << "Mean: " << std::setprecision(1) << std::fixed << average_ << '\n';
  out << "Positive: " << amountOfPositiveElements_ << '\n';
  out << "Negative: " << amountOfNegativeElements_ << '\n';
  out << "Odd Sum: " << sumOfOddElements_ << '\n';
  out << "Even Sum: " << sumOfEvenElements_ << '\n';
  out << "First/Last Equal: " << ((firstElement_ == lastElement_) ? "yes" : "no") << '\n';

  return;
}
