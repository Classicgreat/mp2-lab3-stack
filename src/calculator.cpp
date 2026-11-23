#include "../include/calculator.h"

void Calculator::infix_to_cont() {
  infix_cont.clear();
  int i = 0;
  bool expectOperand = true;

  while (i < infix.size()) {
    Token t;
    char c = infix[i];

    if (c == ' ') {
      ++i;
    } else if (c == '(') {
      t.type = TokenType::OPEN_BRACKET;
      t.data = "(";
      infix_cont.append(t);
      expectOperand = true;
      ++i;
    } else if (c == ')') {
      t.type = TokenType::CLOSE_BRACKET;
      t.data = ")";
      infix_cont.append(t);
      expectOperand = false;
      ++i;
    } else if ((c >= '0' && c <= '9') || c == '.') {
      const char *start = infix.c_str() + i;
      char *p = nullptr;
      t.val = strtod(start, &p);
      if (p == start) {
        throw "bad number";
      }
      t.type = TokenType::NUMBER;
      t.data = infix.substr(i, p - start);
      infix_cont.append(t);
      expectOperand = false;
      i += (p - start);
    } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
      if (expectOperand && c == '+') {
        ++i;
        continue;
      }
      if (expectOperand && c == '-') {
        t.type = TokenType::OPERATION;
        t.data = "u-";
        infix_cont.append(t);
        ++i;
        continue;
      }

      t.type = TokenType::OPERATION;
      t.data = std::string(1, c);
      infix_cont.append(t);
      ++i;
    } else {
      throw "bad character";
    }
  }
}

void Calculator::SetInfix(std::string expr) {
  infix = "(" + expr + ")";
  infix_to_cont();
  ToPostfix();
}

void Calculator::ToPostfix() {
  oper.clear();
  postfix_cont.clear();
  for (int i = 0; i < infix_cont.GetSize(); ++i) {
    if (infix_cont[i].type == TokenType::OPEN_BRACKET) {
      oper.push(infix_cont[i]);
    } else if (infix_cont[i].type == TokenType::NUMBER) {
      postfix_cont.append(infix_cont[i]);
    } else if (infix_cont[i].type == TokenType::CLOSE_BRACKET) {
      while (!oper.IsEmpty() && oper.top().type != TokenType::OPEN_BRACKET) {
        postfix_cont.append(oper.pop());
      }
      if (oper.IsEmpty()) {
        throw "unmatched )";
      }
      oper.pop();
    } else if (infix_cont[i].type == TokenType::OPERATION) {
      while (!oper.IsEmpty() && oper.top().type != TokenType::OPEN_BRACKET &&
             oper.top().Prior() >= infix_cont[i].Prior()) {
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
      const std::string &op = postfix_cont[i].data;

      if (op == "u-") {
        if (nums.IsEmpty())
          throw "not enough operands";

        double a = nums.pop();
        nums.push(-a);
        continue;
      }

      if (nums.IsEmpty())
        throw "not enough operands";
      double a = nums.pop();

      if (nums.IsEmpty())
        throw "not enough operands";
      double b = nums.pop();

      double res = 0;

      if (op == "+") {
        res = b + a;
      } else if (op == "-") {
        res = b - a;
      } else if (op == "*") {
        res = b * a;
      } else if (op == "/") {
        if (a == 0.0)
          throw "division by zero";
        res = b / a;
      } else if (op == "^") {
        res = pow(b, a);
      } else {
        throw "unknown operation";
      }

      nums.push(res);
    }
  }

  if (nums.IsEmpty()) {
    throw "Wrong postfix form (too much opers)";
  }
  double res = nums.pop();
  if (!nums.IsEmpty()) {
    throw "Wrong postfix form (too much nums)";
  }
  return res;
}
