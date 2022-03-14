#include "text-handler.hpp"

#include <iostream>
#include <algorithm>

const int MAXWIDTH = 20;

TextHandler::TextHandler(size_t width) : 
  width_(width),
  text_()
{
}

void TextHandler::read()
{
  while (std::cin)
  {
    std::cin >> std::noskipws;
    char firstChar = std::cin.get();

    if (std::isalpha(firstChar))
    {
      std::string str;
      readWord(str += firstChar);
      token_t token = {TokenType::WORD, str};
      text_.push_back(token);
    }

    else if ((((firstChar == '+') || (firstChar == '-')) && (std::isdigit(std::cin.peek()))) || (std::isdigit(firstChar)))
    {
      std::string str;
      readNumber(str += firstChar);
      token_t token = {TokenType::NUMBER, str};
      text_.push_back(token);
    }

    else if (std::ispunct(firstChar))
    {
      if ((firstChar == '-') && (std::cin.peek() == '-'))
      {
        std::string str;
        readDash(str += firstChar);
        token_t token = {TokenType::DASH, str};
        text_.push_back(token);
      }
      else if (!std::ispunct(std::cin.peek()))
      {
        std::string str;
        str += firstChar;
        token_t token = {TokenType::PUNCT, str};
        text_.push_back(token);
      }
      else
      {
        throw std::invalid_argument("Invalid input\n");
      }
    }
  }
}

void TextHandler::print()
{
  if (text_.empty())
  {
    return;
  }

  if ((text_[0].type == TokenType::PUNCT) || (text_[0].type == TokenType::DASH))
  {
    throw std::invalid_argument("Invalid input: first element can't be punct\n");
  }

  for (size_t i = 0; i < text_.size() - 1; i++)
  {
    if ((text_[i].type == TokenType::PUNCT) && (text_[i + 1].type == TokenType::PUNCT))
    {
      throw std::invalid_argument("Invalid input: two punct are close\n");
    }
  }

  std::vector<std::string> lines;
  std::string line;

  size_t count = 0;
  size_t numberLines = 0;

  while (count < text_.size())
  {
    if (line.empty())
    {
      if ((text_[count].type == TokenType::PUNCT) || (text_[count].type == TokenType::DASH))
      {
        if ((text_[count].type == TokenType::PUNCT) && (lines[numberLines - 1].size() < width_))
        {
          lines[numberLines - 1] += text_[count].value;
          count++;
          continue;
        }
        if (text_[count - 1].type == TokenType::PUNCT)
        {
          line += text_[count - 2].value + text_[count - 1].value;;
        }
        else
        {
          line += text_[count - 1].value;
        }
        (text_[count].type == TokenType::DASH) ? line += " " + text_[count].value : line += text_[count].value;
        auto pos = lines[numberLines - 1].find_last_of(' ');
        lines[numberLines - 1].erase(pos);
        count++;
        continue;
      }
      line += text_[count].value;
      count++;
      continue;
    }

    if (line.size() + text_[count].value.size() + 1 <= width_)
    {
      if (text_[count].type == TokenType::PUNCT)
      {
        line += text_[count].value;
        count++;
        continue;
      }

      line += " " + text_[count].value;
      count++;
      continue;
    }
    lines.push_back(line);
    numberLines++;
    line.clear();
  }
  lines.push_back(line);

  for (size_t i = 0; i < lines.size(); i++)
  {
    std::cout << lines[i] << "\n";
  }
}

void TextHandler::readWord(std::string &string)
{
  while (std::cin)
  {
    if ((std::isalpha(std::cin.peek())) || (std::cin.peek() == '-'))
    {
      string += std::cin.get();
      if ((string.back() == '-') && (std::cin.peek() == '-'))
      {
        throw std::invalid_argument("Invalid input: too many dashes in word\n");
      }
    }
    else
    {
      break;
    }
  }

  if (string.size() > MAXWIDTH)
  {
    throw std::invalid_argument("Invalid input: width of word must be less than 20\n");
  }
}

void TextHandler::readDash(std::string &string)
{
  int numberDash = 1;
  while (std::cin)
  {
    if (std::cin.peek() == '-')
    {
      string += std::cin.get();
      numberDash++;
    }
    else
    {
      break;
    }
  }

  if (numberDash > 3)
  {
    throw std::invalid_argument("Invalid input: too many dashes for a hyphen\n");
  }
}

void TextHandler::readNumber(std::string &string)
{
  int dot = 0;
  while (std::cin)
  {
    if ((std::cin.peek() == '.') || (std::isdigit(std::cin.peek())))
    {
      string += std::cin.get();
      if (string.back() == '.')
      {
        dot++;
        if (dot > 1)
        {
          throw std::invalid_argument("Invalid input: it can't be more than 1 dot in number\n");
        }
      }
    }
    else
    {
      break;
    }
  }

  if (string.size() > MAXWIDTH)
  {
    throw std::invalid_argument("Invalid input: width of number must be less than 20\n");
  }
}
