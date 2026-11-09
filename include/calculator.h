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

  void SetInfix();
  double CalcPostfix();
};

void Calculator::infix_to_cont() {
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

void Calculator::SetInfix() {}

void Calculator::ToPostfix() {
  oper.clear();
  for (int i = 0; i < infix_cont.GetSize(); ++i) {
    if (infix_cont[i].type == TokenType::OPEN_BRACKET) {
      oper.push(infix_cont[i]);
    } else if (infix_cont[i].type == TokenType::NUMBER) {
      postfix_cont.append(infix_cont[i]);
    } else if (infix_cont[i].type == TokenType::CLOSE_BRACKET) {
      while (oper.top().type != TokenType::OPEN_BRACKET) {
        postfix_cont.append(oper.pop());
      }
      oper.pop();
    } else if (infix_cont[i].type == TokenType::OPERATION) {
      while (oper.top().Prior() >= infix_cont[i].Prior()) {
        postfix_cont.append(oper.pop());
      }
      oper.push(infix_cont[i]);
    }
  }
  if (!oper.IsEmpty()) {
    throw "too much brackets";
  }
}

double Calculator::CalcPostfix() {
  nums.clear();
  for (int i = 0; i < postfix_cont.GetSize(); ++i) {
    if (postfix_cont[i].type == TokenType::NUMBER) {
      nums.push(postfix_cont[i].val);
    } else if (postfix_cont[i].type == TokenType::OPERATION) {
      double a = nums.pop();
      double b = nums.pop();
      double res;
      if (postfix_cont[i].data == "+") {
        res = b + a;
      } else if (postfix_cont[i].data == "-") {
        res = b - a;
      } else if (postfix_cont[i].data == "*") {
        res = b * a;
      } else if (postfix_cont[i].data == "/") {
        res = b / a;
      } else if (postfix_cont[i].data == "^") {
        res = pow(b, a);
      }
      nums.push(res);
    }
  }

  double res;
  if (nums.IsEmpty()) {
    throw "Wrong postfix form (too mush opers)";
  }
  res = nums.pop();
  if (!nums.IsEmpty()) {
    throw "Wrong postfix form (too much nums)";
  }
  return res;
};
