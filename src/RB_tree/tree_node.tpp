#pragma once
#include "RB_tree.h"

namespace s21 {
// template<typename Key> // вариант №1
// struct RB_tree<Key>::TreeNode_{
template<typename Key, typename Value>// вариант №2
struct RB_tree<Key, Value>::TreeNode_{
  
  // using value_type = Key; // вариант №1
  using value_type = std::pair<Key, Value>; // вариант №2
  using node_pointer = TreeNode_ *;
    value_type data_;
    node_pointer parent_;
    node_pointer left_;
    node_pointer right_;
    // Red - 0 Black - 1
    bool color_;

    explicit TreeNode_() 
              : data_(value_type()), parent_(nullptr), left_(nullptr), right_(nullptr), color_(RedN) {}

    explicit TreeNode_(const TreeNode_& other) : data_(other.data_), parent_(other.parent_), 
              left_(other.left_), right_(other.right_), color_(other.color_) {}

    explicit TreeNode_(TreeNode_&& other) : data_(std::move(other.data_)), parent_(std::move(other.parent_)), 
              left_(std::move(other.left_)), right_(std::move(other.right_)), color_(std::move(other.color_)) {}
/*
Если у текущего узла есть правое поддерево,
следующим узлом будет наименьший узел в 
этом правом поддереве (т.е. самый левый узел в правом поддереве).
Если у текущего узла нет правого поддерева, 
следующим узлом будет ближайший предок, 
для которого текущий узел находится в левом поддереве.
*/
  node_pointer NextNode() const noexcept {
    node_pointer next = const_cast<node_pointer>(this);
    if (!next->NextIsN_null(2)){
      next = next->right_;
      while(!next->NextIsN_null(1)) next = next->left_;
    } else if (next->NextIsN_null(2) && !next->NextIsN_null(0)){
      while (!next->NextIsN_null(0) && next != next->parent_->left_){
        next = next->parent_;
      }
      next = next->parent_;
    } 
    else {
      next = next->parent_;
    }
    return next;
  }
/*
Если у текущего узла есть левое поддерево, предыдущим 
узлом будет наибольший узел в этом левом поддереве 
(т.е. самый правый узел в левом поддереве).
Если у текущего узла нет левого поддерева, предыдущим 
узлом будет ближайший предок, для которого текущий 
узел находится в правом поддереве.
*/
  node_pointer PrevNode() const noexcept {
    node_pointer prev = const_cast<node_pointer>(this);
    if (!prev->NextIsN_null(1)){
      prev = prev->left_;
      while(!prev->NextIsN_null(2)) prev = prev->right_;
    } else if (prev->NextIsN_null(1) && !prev->NextIsN_null(0)){
      while(!prev->NextIsN_null(0) && prev != prev->parent_->right_){
        prev = prev->parent_;
      }
      prev = prev->parent_;
    } 
    else {
      prev = prev->parent_;
    }
    return prev;
  }

  void SetColor(bool new_color) noexcept { this->color_ = new_color; }
  // изменить цвет определенной ноды
  void SwitchNodeColor() noexcept { SetColor(!color_); }
  /// int next 0 - parent; 1 - left; 2 - right;
  /// @return 0 - следущая нода не n_null; 1 - следущая нода n_null;
  bool NextIsN_null(int next) noexcept {
    if(!next){
      return this->parent_ == this->parent_->right_;
    } else if(next == 1){
      return this->left_ == this->left_->right_;
    } else if (next == 2){
      return this->right_ == this->right_->right_;
    }
    return false;
  }
};
} // namespace s21