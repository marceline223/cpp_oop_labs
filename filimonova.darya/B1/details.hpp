#ifndef DETAILS_HPP
#define DETAILS_HPP

#include <cstring>
#include <functional>
#include <iostream>

enum struct Direction
{
  ASCENDING,
  DESCENDING
};

Direction makeDirection(const char *direction);

template <typename C>
struct IndexStrategy
{
  typedef typename C::size_type index_type;
  static index_type getBegin(const C &)
  {
    return 0;
  }

  static index_type getEnd(const C &collection)
  {
    return collection.size();
  }

  static typename C::reference getElement(C &collection, index_type i)
  {
    return collection[i];
  }
};

template <typename C>
struct AtStrategy
{
  typedef typename C::size_type index_type;
  static index_type getBegin(const C &)
  {
    return 0;
  }

  static index_type getEnd(const C &collection)
  {
    return collection.size();
  }

  static typename C::reference getElement(C &collection, index_type i)
  {
    return collection.at(i);
  }
};

template <typename C>
struct IteratorStrategy
{
  typedef typename C::iterator index_type;

  static index_type getBegin(C &collection)
  {
    return collection.begin();
  }

  static index_type getEnd(C &collection)
  {
    return collection.end();
  }

  static typename C::reference getElement(C &, index_type i)
  {
    return *i;
  }
};

template <template <typename C> typename Strategy, typename C>
void sort(C &collection, Direction dir)
{
  typedef typename C::value_type value_type;

  std::function<bool(value_type, value_type)> cmp;
  if (dir == Direction::ASCENDING)
  {
    cmp = std::greater<value_type>();
  }
  else
  {
    cmp = std::less<value_type>();
  }

  for (typename Strategy<C>::index_type i = Strategy<C>::getBegin(collection); i != Strategy<C>::getEnd(collection); i++)
  {
    typename C::reference element1 = Strategy<C>::getElement(collection, i);
    
    for (typename Strategy<C>::index_type j = i; j != Strategy<C>::getEnd(collection); j++)
    {
      typename C::reference element2 = Strategy<C>::getElement(collection, j);

      if (cmp(element1, element2))
      {
        std::swap(element1, element2);
      }
    }
  }
}

template <typename C>
void print(const C &collection, bool needSpaces = true)
{
  for (typename C::const_iterator currentElement = collection.begin(); currentElement != collection.end(); currentElement++)
  {
    std::cout << *currentElement;
    if (needSpaces)
    {
      std::cout << ' ';
    }
  }

  if (needSpaces)
  {
    std::cout << '\n';
  }
}

#endif
