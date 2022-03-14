#ifndef PHONEBOOK
#define PHONEBOOK

#include <iosfwd>
#include <list>
#include <string>

class Phonebook
{
public:

  struct contact_t
  {
    std::string number;
    
    std::string name;
  };

  typedef std::list<contact_t>::iterator ContactIterator;

  size_t getSize() const;

  bool isEmpty() const;

  void getContact(const ContactIterator itr) const;

  void addContact(const Phonebook::contact_t contact);
  
  void insertBefore(const contact_t& contact, ContactIterator itr);

  void insertAfter(const contact_t& contact, ContactIterator itr);

  ContactIterator erase(ContactIterator itr);

  ContactIterator begin();

  ContactIterator end();

private:

  std::list<contact_t> contacts_;
};

#endif
