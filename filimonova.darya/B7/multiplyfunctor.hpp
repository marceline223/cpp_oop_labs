#ifndef MULTIPLY_FUNCTOR_HPP
#define MULTIPLY_FUNCTOR_HPP

class MultiplyFunctor
{
public:

  MultiplyFunctor(double coef);

  void operator()(double &n);

private:

  double coef_;
};

#endif
