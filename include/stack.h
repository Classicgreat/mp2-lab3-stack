#pragma once
#include <iostream>

template <typename T> class Stack {
  T *pMem;
  int size;
  int top_id;

public:
  Stack<T>(int s = 10) : top_id(-1), size(s) {
    if (size <= 0) {
      throw "Neg Size";
    }
    pMem = new T[size];
  }
  Stack<T>(const Stack<T> &st) : size(st.size), top_id(st.top_id) {
    pMem = new T[size];
    for (int i = 0; i <= top_id; ++i) {
      pMem[i] = st.pMem[i];
    }
  }
  Stack<T>(Stack<T> &&st) : size(st.size), top_id(st.top_id) {
    pMem = st.pMem;
    st.pMem = nullptr;
    st.size = 0;
    st.top_id = 0;
  }

  ~Stack<T>() { delete[] pMem; }

  Stack<T> &operator=(const Stack<T> &st) {
    if (this != &st) {
      if (this->size != st.size) {
        size = st.size;
        delete[] pMem;
        pMem = new T[size];
      }
      top_id = st.top_id;
      for (int i = 0; i <= top_id; ++i) {
        pMem[i] = st.pMem[i];
      }
    }

    return (*this);
  }
  Stack<T> &operator=(Stack<T> &&st) {
    if (this != &st) {
      size = st.size;
      top_id = st.top_id;
      delete[] pMem;
      pMem = st.pMem;
      st.pMem = nullptr;
      st.size = 0;
      st.top_id = -1;
    }
    return (*this);
  }

  bool operator==(const Stack<T> &st) const noexcept {
    if (size != st.size || top_id != st.top_id) {
      return false;
    }

    for (int i = 0; i <= top_id; ++i) {
      if (pMem[i] != st.pMem[i]) {
        return false;
      }
    }

    return true;
  }
  bool operator!=(const Stack<T> &st) const noexcept { return !(this == st); }

  bool IsFull() const noexcept { return size - 1 == top_id; }
  bool IsEmpty() const noexcept { return -1 == top_id; }

  void push(T el) {
    if (IsFull()) {
      throw "Stack is full for push";
    }
    pMem[++top_id] = el;
  }

  T pop() {
    if (IsEmpty()) {
      throw "Stack is empty for pop";
    }
    return pMem[top_id--];
  }
  void clear() noexcept { top_id = -1; }
};
