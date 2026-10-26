#include "../include/stack.h"
#include <iostream>
#include <string>

int main() {
  Stack<char> st(20);
  std::string math_str;
  std::cout << "Enter math string: ";
  std::cin >> math_str;

  try {
    for (int i = 0; i < math_str.length(); ++i) {
      if (math_str[i] == '(') {
        st.push('(');
      } else if (math_str[i] == ')') {
        st.pop();
      }
    }
  } catch (const char *err) {
    // std::cout << err << "\n";
    std::cout << "Math string is WRONG\n";
    return 0;
  }

  if (st.IsEmpty()) {
    std::cout << "Math string is OK\n";
  } else {
    std::cout << "Math string is WRONG\n";
  }
  return 0;
}
