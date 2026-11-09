#pragma once
#include "Container.h"
#include <iostream>

template <typename T> class Stack {
  Container<T> cont;
  int top_id;

public:
  Stack<T>(int size = 10) : top_id(-1), cont(size) {
    if (size <= 0) {
      throw "Neg Size";
    }
  }
  Stack<T>(const Stack<T> &st) : cont(st.cont), top_id(st.top_id) {}
  Stack<T>(Stack<T> &&st) : cont(st.cont), top_id(st.top_id) {}

  ~Stack<T>() {}

  Stack<T> &operator=(const Stack<T> &st) {
    if (this != &st) {
      cont = st.cont;
      top_id = st.top_id;
    }

    return (*this);
  }
  Stack<T> &operator=(Stack<T> &&st) {
    if (this != &st) {
      cont = st.cont;
      top_id = st.top_id;
      st.cont = nullptr;
      st.top_id = -1;
    }
    return (*this);
  }

  bool operator==(const Stack<T> &st) const noexcept {
    if (cont.GetSize() != st.cont.GetSize() || top_id != st.top_id ||
        cont != st.cont) {
      return false;
    }
    return true;
  }
  bool operator!=(const Stack<T> &st) const noexcept { return !(this == st); }

  bool IsFull() const noexcept { return cont.GetSize() - 1 == top_id; }
  bool IsEmpty() const noexcept { return -1 == top_id; }

  void push(T el) {
    if (IsFull()) {
      throw "Stack is full for push";
    }
    cont[++top_id] = el;
  }

  T pop() {
    if (IsEmpty()) {
      throw "Stack is empty for pop";
    }
    return cont[top_id--];
  }
  void clear() noexcept { top_id = -1; }
};
