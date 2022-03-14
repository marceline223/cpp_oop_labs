#include "interface.hpp"

#include <iostream>
#include <stdexcept>
#include <string>

Interface::Interface() : 
    phonebook_(),   
    bookmarks_()                
{
  bookmarks_.insert({"current", phonebook_.end()});
}

void Interface::show(const std::string &markName) const
{
  BookmarkConstIterator bookmark = bookmarks_.find(markName);
  if (bookmark == bookmarks_.end())
  {
    throw std::invalid_argument("<INVALID BOOKMARK>");
  }

  if (phonebook_.isEmpty())
  {
    throw std::invalid_argument("<EMPTY>");
  }
  std::cout << bookmark->second->number << ' ' << bookmark->second->name << '\n';
}

void Interface::add(const std::string &number, const std::string &name)
{
  phonebook_.addContact({number, name});

  if (phonebook_.getSize() == 1)
  {
    bookmarks_.find("current")->second = phonebook_.begin();
  }
}

void Interface::store(const std::string &markName, const std::string &newMarkName)
{
  BookmarkIterator bookmark = bookmarks_.find(markName);
  if (bookmark == bookmarks_.end())
  {
    throw std::invalid_argument("<INVALID BOOKMARK>");
  }
  bookmarks_.insert({newMarkName, bookmark->second});
}

void Interface::insertBefore(const std::string &markName, const std::string &number, const std::string &name)
{
  BookmarkIterator bookmark = bookmarks_.find(markName);
  if (bookmark == bookmarks_.end())
  {
    throw std::invalid_argument("<INVALID BOOKMARK>");
  }

  phonebook_.insertBefore({number, name}, bookmark->second);

  if (phonebook_.getSize() == 1)
  {
    bookmarks_.find("current")->second = phonebook_.begin();
  }
}

void Interface::insertAfter(const std::string &markName, const std::string &number, const std::string &name)
{
  BookmarkIterator bookmark = bookmarks_.find(markName);
  if (bookmark == bookmarks_.end())
  {
    throw std::invalid_argument("<INVALID BOOKMARK>");
  }

  phonebook_.insertAfter({number, name}, bookmark->second);

  if (phonebook_.getSize() == 1)
  {
    bookmarks_.find("current")->second = phonebook_.begin();
  }
}

void Interface::deleteContact(const std::string &markName)
{
  if (phonebook_.isEmpty())
  {
    return;
  }

  BookmarkIterator bookmark = bookmarks_.find(markName);
  if (bookmark == bookmarks_.end())
  {
    throw std::invalid_argument("<INVALID BOOKMARK>");
  }
  Phonebook::ContactIterator itr = bookmark->second;
  bookmark->second = phonebook_.erase(bookmark->second);

  if (bookmark->second == phonebook_.end())
  {
    --bookmark->second;
  }
  for (BookmarkIterator i = bookmarks_.begin(); i != bookmarks_.end(); i++)
  {
    if (i->second == itr)
    {
      i->second = bookmark->second;
    }
  }
}

void Interface::move(const std::string &markName, int steps)
{
  BookmarkIterator bookmark = bookmarks_.find(markName);

  if (bookmark == bookmarks_.end())
  {
    throw std::invalid_argument("<INVALID BOOKMARK>");
  }

  Phonebook::ContactIterator& itr = bookmark->second;
  
  if (steps > 0)
  {
    for (int i = 0; i < steps; i++)
    {
      if (itr == std::prev(phonebook_.end()))
      {
        itr = phonebook_.begin();
      }
      else
      {
        itr++;
      }
    }
  }
  else
  {
    for (int i = 0; i > steps; i--)
    {
      if (itr == phonebook_.begin())
      {
        itr = std::prev(phonebook_.end());
      }
      else
      {
        itr--;
      }
      
    }
  }
}

void Interface::moveToFirst(const std::string &markName)
{
  BookmarkIterator bookmark = bookmarks_.find(markName);

  if (bookmark == bookmarks_.end())
  {
    throw std::invalid_argument("<INVALID BOOKMARK>");
  } 

  bookmark->second = phonebook_.begin();
}

void Interface::moveToLast(const std::string &markName)
{
  BookmarkIterator bookmark = bookmarks_.find(markName);

  if (bookmark == bookmarks_.end())
  {
    throw std::invalid_argument("<INVALID BOOKMARK>");
  }  

  bookmark->second = std::prev(phonebook_.end());
}
