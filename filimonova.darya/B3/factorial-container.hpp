#ifndef FACTORIAL_CONTAINER
#define FACTORIAL_CONTAINER

#include <iterator>

class FactorialContainer
{
public:

  class FactorialIterator : public std::iterator<std::bidirectional_iterator_tag, size_t>
  {
  public:

    FactorialIterator(unsigned int index);

    unsigned int &operator*();

    FactorialIterator &operator++();

    FactorialIterator operator++(int);

    FactorialIterator &operator--();

    FactorialIterator operator--(int);

    bool operator==(const FactorialContainer::FactorialIterator &itr) const;

    bool operator!=(const FactorialContainer::FactorialIterator &itr) const;

  private:

    unsigned int index_;

    unsigned int factorial_;

    FactorialIterator(unsigned int index, unsigned int factorial);

    friend class FactorialContainer;
  };

  FactorialContainer() = default;

  FactorialIterator begin() const;

  FactorialIterator end() const;

  typedef std::reverse_iterator<FactorialIterator> reverse_iterator;

  reverse_iterator rbegin() const;

  reverse_iterator rend() const;
};

#endif
