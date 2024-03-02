#include "RB_tree.h"

namespace s21{

  template <typename Key, typename Value>
  void RB_tree<Key, Value>::PrintTree(){
    int i = 1;
    for (auto it = begin(); it != end(); it++, i++){
      std::cout << (*it).first << ' ';
    }
    std::cout << '\n';
  }

  template <typename Key, typename Value>
  void RB_tree<Key, Value>::PrintTreeRecursive(iterator it, int depth) const {
    node_pointer node = it.GetNodePointer();
    if (node == n_null_) return;

    // Печать правого поддерева
    iterator right(node->right_);
    PrintTreeRecursive(right, depth + 1);

    // Печать текущего узла
    std::cout << " d:" << depth;
    std::cout << " ";
    std::cout << std::string(depth, ' ') << node->data_.first << " ";
    std::cout << " c:" << (node->color_ == 0 ? "red" : "black");
    std::cout << " ";
    std::cout << (node->data_.second);
    std::cout << std::endl;

    iterator left(node->left_);
    // Печать левого поддерева
    PrintTreeRecursive(left, depth + 1);
  }
  
  template <typename Key, typename Value>
  void RB_tree<Key, Value>::FullNodeInfo(const_iterator cit) noexcept {
    node_pointer node = const_cast<node_pointer>(cit.GetNodePointer());
    std::cout << "this:\t" << (*cit).first << " \t" << node << " color " << node->color_ << "\n";
    if(node->parent_ )
      std::cout << "parent:\t" << node->parent_->data_.first << " \t" << node->parent_ << " color " << node->parent_->color_ << "\n";
    if(node->left_ )
      std::cout << "left:\t" << node->left_->data_.first << " \t" << node->left_ << " color " << node->left_->color_ << "\n";
    if(node->right_ )
      std::cout << "right:\t" << node->right_->data_.first << " \t" << node->right_ << " color " << node->right_->color_ << "\n";
  }


//ВЫШЕ_УДАЛИТЬ
//НИЖЕ___НЕ_УДАЛЯТЬ___НИЖЕ___НЕ_УДАЛЯТЬ___НИЖЕ___НЕ_УДАЛЯТЬ___НИЖЕ___НЕ_УДАЛЯТЬ___НИЖЕ___НЕ_УДАЛЯТЬ___НИЖЕ___НЕ_УДАЛЯТЬ___НИЖЕ___НЕ_УДАЛЯТЬ___НИЖЕ___НЕ_УДАЛЯТЬ___НИЖЕ___НЕ_УДАЛЯТЬ___НИЖЕ___НЕ_УДАЛЯТЬ___НИЖЕ___НЕ_УДАЛЯТЬ___
template <typename Key, typename Value>
bool RB_tree<Key, Value>::CheckBlackHeight() const noexcept {
  if (root_ == nullptr || root_ == n_null_) {
      return true;
  }
  int minBlackHeight = 0;
  int maxBlackHeight = 0;
  minBlackHeight = FindMinBlackHeight(root_, minBlackHeight);
  maxBlackHeight = FindMaxBlackHeight(root_, maxBlackHeight);

  return abs(maxBlackHeight - minBlackHeight) <= 1;
}

template <typename Key, typename Value>
int RB_tree<Key, Value>::FindMinBlackHeight(node_pointer node, int currentHeight) const {
  if (node == n_null_) return currentHeight;
  if (node->color_) currentHeight++; 
  int leftHeight = FindMinBlackHeight(node->left_, currentHeight);
  int rightHeight = FindMinBlackHeight(node->right_, currentHeight);
  return std::min(leftHeight, rightHeight);
}

template <typename Key, typename Value>
int RB_tree<Key, Value>::FindMaxBlackHeight(node_pointer node, int currentHeight) const {
  if (node == n_null_) return currentHeight;
  if (node->color_) currentHeight++; 
  int leftHeight = FindMinBlackHeight(node->left_, currentHeight);
  int rightHeight = FindMinBlackHeight(node->right_, currentHeight);
  return std::max(leftHeight, rightHeight);
}

template <typename Key, typename Value>
bool RB_tree<Key, Value>::hasConsecutiveReds() const {
  bool alert = false;
  return CheckRedFamily(root_, alert);
}

template <typename Key, typename Value>
bool RB_tree<Key, Value>::CheckRedFamily(node_pointer node, bool alert) const noexcept {
  if(alert) return true; 
  if (node == n_null_) return (alert = false);

  // Проверяем, является ли текущий узел и его родитель красными
  if (node->parent_ != n_null_ && node->color_ == RedN && node->parent_->color_ == RedN) {
      return (alert = true);
  }

  // Рекурсивно проверяем левое и правое поддеревья
  return CheckRedFamily(node->left_, alert) || CheckRedFamily(node->right_, alert);
}


} // namespace s21