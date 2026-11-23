#include "../include/calculator.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
  cout << "Enter math str: ";
  string expr;
  getline(cin, expr);

  Calculator calc;
  calc.SetInfix(expr);

  cout << "Result: " << calc.CalcPostfix() << "\n";
  return 0;
}
