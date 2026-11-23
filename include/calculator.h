#ifndef CALCULATOR
#define CALCULATOR

#include "Container.h"
#include "stack.h"
#include <cmath>
#include <iostream>
#include <string>

enum class TokenType { NUMBER, OPERATION, OPEN_BRACKET, CLOSE_BRACKET };

struct Token {
  TokenType type;
  std::string data;
  double val;
  int Prior() const {
    switch (type) {
    case TokenType::OPEN_BRACKET:
    case TokenType::CLOSE_BRACKET:
      return 0;
    case TokenType::OPERATION:
      if (data == "+" || data == "-") {
        return 1;
      } else if (data == "*" || data == "/") {
        return 2;
      }
      return 3;
    }
    return -1;
  }
};

class Calculator {
  std::string infix, postfix;
  Container<Token> infix_cont, postfix_cont;
  Stack<Token> oper;
  Stack<double> nums;

  void infix_to_cont();
  void ToPostfix();

public:
  Calculator() : infix(""), postfix(""), infix_cont(), postfix_cont() {}

  void SetInfix(std::string expr);
  double CalcPostfix();
};

#endif
