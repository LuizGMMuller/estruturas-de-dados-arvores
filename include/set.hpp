#pragma once
#include "avl.hpp"

template <class T>
class Set {
 public:
  Set();

  bool insert(const T& value);
  bool remove(const T& value);
  bool search(const T& value) const;

 private:
  AVL<T> data;
};


template <class T>
Set<T>::Set() {}

template <class T>
bool Set<T>::insert(const T& value) {
  return data.insert(value);
}

template <class T>
bool Set<T>::remove(const T& value) {
  return data.remove(value);
}

template <class T>
bool Set<T>::search(const T& value) const {
  return data.contain(value);
}