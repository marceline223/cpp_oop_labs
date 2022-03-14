#ifndef TEXT_HANDLER_HPP
#define TEXT_HANDLER_HPP

#include <string>
#include <vector>

enum TokenType
{
  WORD,
  PUNCT,
  DASH,
  NUMBER
};

struct token_t
{
  TokenType type;
  
  std::string value;
};

class TextHandler
{
public:
  TextHandler(size_t width);

  void read();

  void print();

  void readWord(std::string &string);

  void readDash(std::string &string);
  
  void readNumber(std::string &string);

private:
  size_t width_;

  std::vector<token_t> text_;
};

#endif
