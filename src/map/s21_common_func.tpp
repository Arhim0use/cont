#include "RB_tree.h"

namespace s21{

  template <typename Key, typename Value>
  void RB_tree<Key, Value>::PrintTree(){
    int i = 1;
    for (auto it = begin(); it != end(); it++, i++){
      std::cout << *it << ' ';
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
    std::cout << std::string(depth, ' ') << node->data_.first << " ";
    std::cout << (node->data_.second);
    std::cout << std::endl;

    iterator left(node->left_);
    // Печать левого поддерева
    PrintTreeRecursive(left, depth + 1);
  }
  
  template <typename Key, typename Value>
  void RB_tree<Key, Value>::FullNodeInfo(const_iterator cit) noexcept {
    node_pointer node = const_cast<node_pointer>(cit.GetNodePointer());
    std::cout << "this:\t" << *cit << " \t" << node << " color " << node->color_ << "\n";
    if(node->parent_ )
      std::cout << "parent:\t" << node->parent_->data_.first << " \t" << node->parent_ << " color " << node->parent_->color_ << "\n";
    if(node->left_ )
      std::cout << "left:\t" << node->left_->data_.first << " \t" << node->left_ << " color " << node->left_->color_ << "\n";
    if(node->right_ )
      std::cout << "right:\t" << node->right_->data_.first << " \t" << node->right_ << " color " << node->right_->color_ << "\n";
  }

} // namespace s21