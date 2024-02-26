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
bool RB_tree<Key, Value>::checkBlackHeight() {
  if (root_ == n_null_) return true;
  // node_pointer node = root_;
  std::stack<std::pair<node_pointer, int>> stack;
  std::vector<int> blackHeights;
  // int blackHeight = 0;
  stack.push({root_, 0});

  while (!stack.empty()) {
    auto [node, blackHeight] = stack.top();
    stack.pop();

    if (node->color_ == BlackN) {
      blackHeight++;
    }

    if (node->left_ == n_null_ && node->right_ == n_null_) {
      // Если текущий узел - лист, проверяем, уникальна ли его черная высота
      if (std::find(blackHeights.begin(), blackHeights.end(), blackHeight) == blackHeights.end()) {
        blackHeights.push_back(blackHeight);
      }
      if (blackHeights.size() > 2 || (blackHeights.size() == 2 && std::abs(blackHeights[0] - blackHeights[1]) > 1)) {
        return false;
      }
    } else {
      if (node->right_ != n_null_) {
        stack.push({node->right_, blackHeight});
      }
      if (node->left_ != n_null_) {
        stack.push({node->left_, blackHeight});
      }
    }
  }

  return true;
}

template <typename Key, typename Value>
bool RB_tree<Key, Value>::hasConsecutiveReds() const {
  bool alert = false;
  return checkConsecutiveReds(root_, alert);
}

template <typename Key, typename Value>
bool RB_tree<Key, Value>::checkConsecutiveReds(node_pointer node, bool alert) const {
  if(alert) return true; 
  if (node == n_null_) return (alert = false);

  // Проверяем, является ли текущий узел и его родитель красными
  if (node->parent_ != n_null_ && node->color_ == RedN && node->parent_->color_ == RedN) {
      return (alert = true);
  }

  // Рекурсивно проверяем левое и правое поддеревья
  return checkConsecutiveReds(node->left_, alert) || checkConsecutiveReds(node->right_, alert);
}


} // namespace s21