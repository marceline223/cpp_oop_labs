#include "phonebook.hpp"

#include <iostream>
#include <string>

size_t Phonebook::getSize() const
{
  return contacts_.size();
}

bool Phonebook::isEmpty() const
{
  return contacts_.empty();
}

void Phonebook::addContact(const Phonebook::contact_t contact)
{
  contacts_.push_back(contact);
}

void Phonebook::insertBefore(const contact_t &contact, ContactIterator itr)
{
  if (itr != contacts_.begin())
  {
    contacts_.insert(itr, contact);
  }
  else
  {
    contacts_.push_front(contact);
  }
}

void Phonebook::insertAfter(const contact_t &contact, ContactIterator itr)
{
  if (itr != contacts_.end())
  {
    contacts_.insert(std::next(itr), contact);
  }
  else
  {
    contacts_.push_back(contact);
  }
}

Phonebook::ContactIterator Phonebook::erase(ContactIterator itr)
{
  return contacts_.erase(itr);
}

Phonebook::ContactIterator Phonebook::begin()
{
  return contacts_.begin();
}

Phonebook::ContactIterator Phonebook::end()
{
  return contacts_.end();
}
