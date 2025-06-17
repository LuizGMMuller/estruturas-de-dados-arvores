#pragma once
#include <utility>
#include <vector>
#include <algorithm>
#include <cmath>

template <class T>
class AVL {
 private:
  struct TreeNode {
    T data;
    TreeNode* left;
    TreeNode* right;
    int height;

    TreeNode(const T& value) : data(value), left(nullptr), right(nullptr), height(0) {}

    ~TreeNode() {
      delete left;
      delete right;
    }

    TreeNode* max() {
      TreeNode* current = this;
      while (current->right)
        current = current->right;
      return current;
    }

    TreeNode* min() {
      TreeNode* current = this;
      while (current->left)
        current = current->left;
      return current;
    }
  };

  TreeNode* root;

  int height(TreeNode* node) const {
    return node ? node->height : -1;
  }

  void balance(TreeNode*& node) {
    if (!node) return;

    int balanceFactor = height(node->left) - height(node->right);

    if (balanceFactor > 1) {
      if (height(node->left->left) >= height(node->left->right)) {
        rotateRight(node);
      } 
      else {
        rotateLeft(node->left);
        rotateRight(node);
      }
    }
    else if (balanceFactor < -1) {
      if (height(node->right->right) >= height(node->right->left)) {
        rotateLeft(node);
      } 
      else {
        rotateRight(node->right);
        rotateLeft(node);
      }
    }
    else {
      node->height = std::max(height(node->left), height(node->right)) + 1;
    }
  }

  void rotateLeft(TreeNode*& node) {
    TreeNode* newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;
    node->height = std::max(height(node->left), height(node->right)) + 1;
    newRoot->height = std::max(height(newRoot->right), node->height) + 1;
    node = newRoot;
  }

  void rotateRight(TreeNode*& node) {
    TreeNode* newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;
    node->height = std::max(height(node->left), height(node->right)) + 1;
    newRoot->height = std::max(height(newRoot->left), node->height) + 1;
    node = newRoot;
  }

  bool insert(TreeNode*& node, const T& value) {
    if (!node) {
      node = new TreeNode(value);
      return true;
    }

    if (value < node->data) {
      if (!insert(node->left, value))
        return false;
    }
    else if (value > node->data) {
      if (!insert(node->right, value))
        return false;
    } 

    balance(node);
    return true;
  }

  bool remove(TreeNode*& node, const T& value) {
    if (!node)
      return false;

    if (value < node->data) {
      if (!remove(node->left, value))
        return false;
    } 
    else if (value > node->data) {
      if (!remove(node->right, value))
        return false;
    } 
    else {
      if (!node->left) {
        TreeNode* old = node;
        node = node->right;
        old->left = old->right = nullptr;
        delete old;
      } 
      else if (!node->right) {
        TreeNode* old = node;
        node = node->left;
        old->left = old->right = nullptr;
        delete old;
      } 
      else {
        TreeNode* successor = node->right->min();
        node->data = successor->data;
        remove(node->right, successor->data);
      }
    }

    if (node)
      balance(node);
    return true;
  }

  bool contain(const TreeNode* const node, const T& value) const {
    if (!node)
      return false;
    if (value < node->data){
      return contain(node->left, value);
    }
    else if (value > node->data){
      return contain(node->right, value);
    }
    else{
      return true;
    }
  }

  void in_order(const TreeNode* const node, std::vector<T>& result) const {
    if (!node){
      return;
    }
    in_order(node->left, result);
    result.push_back(node->data);
    in_order(node->right, result);
  }

  void pre_order(const TreeNode* const node, std::vector<T>& result) const {
    if (!node){
      return;
    }
    result.push_back(node->data);
    pre_order(node->left, result);
    pre_order(node->right, result);
  }

  void post_order(const TreeNode* const node, std::vector<T>& result) const {
    if (!node){
      return;
    }
    post_order(node->left, result);
    post_order(node->right, result);
    result.push_back(node->data);
  }

 public:
  AVL() : root(nullptr) {}

  ~AVL() {
    delete root;
  }

  bool insert(const T& value) {
    return insert(root, value);
  }

  bool remove(const T& value) {
    return remove(root, value);
  }

  bool contain(const T& value) const {
    return contain(root, value);
  }

  std::vector<T> in_order() const {
    std::vector<T> result;
    in_order(root, result);
    return result;
  }

  std::vector<T> pre_order() const {
    std::vector<T> result;
    pre_order(root, result);
    return result;
  }

  std::vector<T> post_order() const {
    std::vector<T> result;
    post_order(root, result);
    return result;
  }

  bool is_balanced() const {
    return is_balanced(root).first;
  }

  std::pair<bool, int> is_balanced(TreeNode* node) const {
    if (!node) return {true, -1};

    auto left = is_balanced(node->left);
    auto right = is_balanced(node->right);

    bool balanced =
        left.first && right.first && std::abs(left.second - right.second) <= 1;
    int node_height = 1 + std::max(left.second, right.second);

    return {balanced, node_height};
  }
};