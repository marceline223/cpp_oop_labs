#ifndef INTERFACE
#define INTERFACE

#include <map>
#include <string>

#include "phonebook.hpp"

class Interface
{
public:

  Interface();

  void add(const std::string &number, const std::string &name);

  void store(const std::string &name, const std::string &newName);

  void insertBefore(const std::string &markName, const std::string &number, const std::string &name);

  void insertAfter(const std::string &markName, const std::string &number, const std::string &name);

  void deleteContact(const std::string &markName);

  void show(const std::string &markName) const;

  void move(const std::string &markName, int steps);

  void moveToFirst(const std::string &markName);

  void moveToLast(const std::string &markName);

private:

  Phonebook phonebook_;

  std::map<std::string, Phonebook::ContactIterator> bookmarks_;

  typedef std::map<std::string, Phonebook::ContactIterator>::iterator BookmarkIterator;

  typedef std::map<std::string, Phonebook::ContactIterator>::const_iterator BookmarkConstIterator;
};

#endif
