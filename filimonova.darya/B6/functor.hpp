#ifndef FUNCTOR_HPP
#define FUNCTOR_HPP

#include <iosfwd>

class Functor
{
public:
  Functor();

  void operator()(int n);

  void printStatistic(std::ostream& out) const;

private:
  int amountOfElements_;

  int maxElement_;

  int minElement_;

  int firstElement_;

  int lastElement_;

  double average_;

  int amountOfPositiveElements_;

  int amountOfNegativeElements_;

  long long int sumOfOddElements_;

  long long int sumOfEvenElements_;

  bool isEmpty_;
};

#endif
