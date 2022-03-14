#include "multiplyfunctor.hpp"

MultiplyFunctor::MultiplyFunctor(double coef) :
  coef_(coef)
{
}

void MultiplyFunctor::operator() (double& n)
{
  n*=coef_;
}
