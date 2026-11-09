#include <iostream>

template <typename T> class Container {
  int size;
  int capacity;
  T *pMem;

  void resizeBuffer(int newCapacity) {
    if (newCapacity < size)
      newCapacity = size;
    if (newCapacity == 0) {
      delete[] pMem;
      pMem = nullptr;
      capacity = 0;
      return;
    }
    T *tmp = new T[newCapacity];
    for (int i = 0; i < size; ++i) {
      tmp[i] = pMem[i];
    }
    delete[] pMem;
    pMem = tmp;
    capacity = newCapacity;
  }

public:
  Container(int s = 10) {
    if (s < 0)
      throw "Size < 0";
    size = 0;
    capacity = s;
    pMem = (capacity > 0) ? new T[capacity] : nullptr;
  }

  ~Container() { delete[] pMem; }

  Container(const Container &c) : size(c.size), capacity(c.capacity) {
    pMem = (capacity > 0) ? new T[capacity] : nullptr;
    for (int i = 0; i < size; ++i) {
      pMem[i] = c.pMem[i];
    }
  }

  Container(Container &&c) noexcept {
    size = c.size;
    capacity = c.capacity;
    pMem = c.pMem;
    c.size = 0;
    c.capacity = 0;
    c.pMem = nullptr;
  }

  Container<T> &operator=(const Container<T> &c);
  Container<T> &operator=(Container<T> &&c) noexcept;

  bool operator==(const Container<T> &c) const;
  bool operator!=(const Container<T> &c) const;

  int GetSize() const { return size; }
  int GetCapacity() const { return capacity; }

  const T &operator[](int id) const;
  T &operator[](int id);

  void append(T elem);
  void pop();
  void insert(T elem, int id);
  void del(int id);
  void clear();

  friend std::ostream &operator<<(std::ostream &out, const Container<T> &c) {
    if (c.GetSize() > 0) {
      for (int i = 0; i < c.GetSize() - 1; ++i)
        out << c[i] << '-';
      out << c[c.GetSize() - 1];
    }
    return out;
  }

  friend std::istream &operator>>(std::istream &in, Container<T> &c) {
    for (int i = 0; i < c.GetSize(); ++i)
      in >> c[i];
    return in;
  }
};

template <typename T>
Container<T> &Container<T>::operator=(const Container<T> &c) {
  if (this != &c) {
    if (capacity < c.size) {
      delete[] pMem;
      capacity = c.capacity;
      pMem = new T[capacity];
    }
    size = c.size;
    for (int i = 0; i < size; ++i) {
      pMem[i] = c.pMem[i];
    }
  }
  return *this;
}

template <typename T>
Container<T> &Container<T>::operator=(Container<T> &&c) noexcept {
  if (this != &c) {
    delete[] pMem;
    size = c.size;
    capacity = c.capacity;
    pMem = c.pMem;

    c.size = 0;
    c.capacity = 0;
    c.pMem = nullptr;
  }
  return *this;
}

template <typename T>
bool Container<T>::operator==(const Container<T> &c) const {
  if (size != c.size) {
    return false;
  }
  for (int i = 0; i < size; ++i) {
    if (pMem[i] != c.pMem[i]) {
      return false;
    }
  }
  return true;
}

template <typename T>
bool Container<T>::operator!=(const Container<T> &c) const {
  return !(*this == c);
}

template <typename T> T &Container<T>::operator[](int id) {
  if (id < 0 || id >= size) {
    throw "Out of range index";
  }
  return pMem[id];
}

template <typename T> const T &Container<T>::operator[](int id) const {
  if (id < 0 || id >= size) {
    throw "Out of range index";
  }
  return pMem[id];
}

template <typename T> void Container<T>::append(T elem) {
  if (size >= capacity) {
    int newCapacity = (capacity == 0) ? 1 : capacity * 2;
    resizeBuffer(newCapacity);
  }
  pMem[size++] = elem;
}

template <typename T> void Container<T>::pop() {
  if (size <= 0) {
    throw "Deleting from empty Container";
  }
  size--;
}

template <typename T> void Container<T>::insert(T elem, int id) {
  if (id < 0 || id > size) {
    throw "Out of range index";
  }

  if (size >= capacity) {
    int newCapacity = (capacity == 0) ? 1 : capacity * 2;
    resizeBuffer(newCapacity);
  }

  for (int i = size; i > id; --i) {
    pMem[i] = pMem[i - 1];
  }

  pMem[id] = elem;
  ++size;
}

template <typename T> void Container<T>::del(int id) {
  if (id < 0 || id >= size) {
    throw "Out of range index";
  }

  for (int i = id; i < size - 1; ++i) {

    pMem[i] = pMem[i + 1];
  }
  --size;
}

template <typename T> void Container<T>::clear() { size = 0; }
