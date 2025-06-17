#pragma once
#include "bst.hpp"
#include <stdexcept>

template <class K, class V>
class Map {
 private:
  struct Pair {
    K key;
    V value;

    explicit Pair(const K& k) : key(k), value() {}

    bool operator<(const Pair& other) const {
      return key > other.key;
    }
  };

 public:
  Map();

  V& operator[](const K& key);
  const V& operator[](const K& key) const;
  bool remove(const K& key);

 private:
  BST<Pair> data;
};


template <class K, class V>
Map<K, V>::Map() {}

template <class K, class V>
V& Map<K, V>::operator[](const K& key) {
  typename BST<Pair>::TreeNode* node = data.find_node(Pair(key));

  if (node == nullptr) {
    data.insert(Pair(key));
    node = data.find_node(Pair(key));
  }

  return node->data.value;
}

template <class K, class V>
const V& Map<K, V>::operator[](const K& key) const {
  typename BST<Pair>::TreeNode* node = data.find_node(Pair(key));

  if (node == nullptr) {
    throw std::out_of_range("Chave não encontrada no Map.");
  }

  return node->data.value;
}

template <class K, class V>
bool Map<K, V>::remove(const K& key) {
  return data.remove(Pair(key));
}
