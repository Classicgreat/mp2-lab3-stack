#include "Container.h"
#include <iostream>
#include <string>
#include <sys/select.h>

enum class TokenType { NUMBER, OPERATION, OPEN_BRACKET, CLOSE_BRACKET };

struct Token {
  TokenType type;
  std::string data;
  double val;
};

class Calculator {
  std::string infix, postfix;
  Container<Token> infix_cont, postfix_cont;

  void infix_to_cont() {
    infix_cont.clear();
    int i = 0;
    while (i < infix_cont.GetSize()) {
      Token t;
      if (infix[i] == '(') {
        t.type = TokenType::OPEN_BRACKET;
        t.data = '(';
        infix_cont.append(t);
      }
      if (infix[i] >= '0' && infix[i] <= '9' || infix[i] == '.') {
        char *p;
        t.val = strtod(&infix[i], &p);
        t.type = TokenType::NUMBER;
        t.data = ""; // Подстрока
        infix_cont.append(t);
        int delta = p - &infix[i];
        i += delta - 1;
      }
    }
  }

public:
  Calculator() : infix(""), postfix(""), infix_cont(), postfix_cont() {}

  void SetInfix() {}
  void Calc() {}
};
