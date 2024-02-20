
#include "RB_tree.h"

namespace s21{

struct TreeNode_;
using node_pointer = TreeNode_ *;

template <typename Key, typename Value>
typename RB_tree<Key, Value>::node_pointer
RB_tree<Key, Value>::GoLeft(){
  node_pointer temp = const_cast<node_pointer>(root_);
  while (temp->left_  && temp->left_ != n_null_){
    temp = temp->left_;
  }
  return temp;
}

template <typename Key, typename Value>
typename RB_tree<Key, Value>::node_pointer
RB_tree<Key, Value>::GoRight(){
  node_pointer temp = const_cast<node_pointer>(root_);
  while (temp->right_ && temp->right_ != n_null_){
    temp = temp->right_;
  }
  return temp;
}

template <typename Key, typename Value>
typename RB_tree<Key, Value>::node_pointer
RB_tree<Key, Value>::InitNode(){
  node_pointer new_node = new TreeNode_();
  new_node->left_ = n_null_;
  new_node->right_ = n_null_;
  new_node->parent_ = n_null_;
  return new_node;
}

template <typename Key, typename Value>
typename RB_tree<Key, Value>::node_pointer
RB_tree<Key, Value>::InitNode(const value_type& key){
  node_pointer new_node = InitNode();
  new_node->data_ = key;
  return new_node;
}

template <typename Key, typename Value>
void RB_tree<Key, Value>::Init_n_nul(){
  n_null_ = InitNode();
  n_null_->color_ = BlackN;
  n_null_->left_ = n_null_;
  n_null_->right_ = n_null_;
}

template <typename Key, typename Value>
void RB_tree<Key, Value>::DeleteTreeRecursive(node_pointer node) {
  if (node && node != n_null_) {
    DeleteTreeRecursive(node->left_);
    DeleteTreeRecursive(node->right_);
    if (node->parent_ != n_null_) {
      // Если у узла есть родитель, обнуляем ссылку на этот узел у родителя
      if (node->parent_->left_ == node) node->parent_->left_ = n_null_;
      else if (node->parent_->right_ == node) node->parent_->right_ = n_null_;
    }
    delete node;
  }
}

template <typename Key, typename Value>
void RB_tree<Key, Value>::NodeTransfer(node_pointer replaceable, node_pointer replacing){
  replacing->parent_ = replaceable->parent_;
  if(replacing != replaceable->left_)replacing->left_ = replaceable->left_;
  if(replacing != replaceable->right_)replacing->right_ = replaceable->right_;
  if(replacing->left_ != n_null_) replacing->left_->parent_ = replacing;
  if(replacing->right_ != n_null_) replacing->right_->parent_ = replacing;
  if(replacing->parent_ != n_null_) { LeftOrRight(replaceable, replacing);
    // if (replacing->parent_->data_ < replacing->data_){
    //   replacing->parent_->right_ = replacing;
    // } else {
    //   replacing->parent_->left_ = replacing;
    // }
  }
}

template <typename Key, typename Value>
void RB_tree<Key, Value>::LeftOrRight(node_pointer checked, node_pointer insert){
  node_pointer parent = checked->parent_;
  if(checked == parent->left_){
    parent->left_ = insert;
    insert->parent_ = parent;
  } else if (checked == parent->right_){
    parent->right_ = insert;
    insert->parent_ = parent;
  } else if (checked == root_){
    root_ = insert;
    insert->parent_ = n_null_;
  }
}

template <typename Key, typename Value>
typename RB_tree<Key, Value>::node_pointer
RB_tree<Key, Value>::FindEqData(const Key& first){
  node_pointer eq_node = root_;
  if(eq_node){
    while (eq_node->data_.first != first) {
      bool key_less = eq_node->data_.first > first;
      if(!key_less && eq_node->right_ != n_null_) {
        eq_node = eq_node->right_;
      } else if(key_less && eq_node->left_!= n_null_) {
        eq_node = eq_node->left_;
      } else if ((!key_less && eq_node->right_ == n_null_) || (key_less && eq_node->left_ == n_null_) 
        || (eq_node->right_ == n_null_ && eq_node->left_ == n_null_)){
        break;
      }
    }
  } else {
    eq_node = n_null_;
  }
  return eq_node;
}

template <typename Key, typename Value>
typename RB_tree<Key, Value>::node_pointer
RB_tree<Key, Value>::DeleteNode(const value_type& key){
  node_pointer node = FindEqData(key.first);
  node_pointer prev = node->PrevNode();
  if (node->data_.first == key.first){
    // если это крайний лист дерева
    if (node->left_ == n_null_ && node->right_ == n_null_){
      LeftOrRight(node, n_null_);
    // если только один ил листов n_null
    } else if ((node->left_ != n_null_ && node->right_ == n_null_) || 
              (node->left_ == n_null_ && node->right_ != n_null_)){
      if (node->left_ != n_null_){
        LeftOrRight(node, node->left_);
      } else {
        LeftOrRight(node, node->right_);
      }
    // если нода - с левым и правым сыном не n_null
    } else if(node->left_ != n_null_ && node->right_ != n_null_ ){
      if (node->left_ != prev) prev->parent_->right_ = prev->left_;
      NodeTransfer(node, prev);
      if(node == root_) root_ = prev;
    }
    delete node;
    n_null_->data_.first--;
  } 
  // else {
  //   node = n_null_;
  // }
  return prev;
}

template <typename Key, typename Value>
void RB_tree<Key, Value>::CleanTree(){
  DeleteTreeRecursive(root_);
  root_ = n_null_;
  n_null_->data_.first = 0;
}

template <typename Key, typename Value>
void RB_tree<Key, Value>::InsertAll(const value_type& key, node_pointer key_position){
  node_pointer new_node = InitNode(key);
  if (!root_) {
    root_ = new_node;
    root_->color_ = BlackN;
  } else {
    node_pointer temp = key_position;
    if(temp->data_.first > key.first){
      temp->left_ = new_node;
      new_node->parent_ = temp;
    } else {
      temp->right_ = new_node;
      new_node->parent_ = temp;
    }
    // temp.BalanceTree();
  }
  n_null_->data_.first++;
  n_null_->parent_ = GoRight();
}

template <typename Key, typename Value>
bool RB_tree<Key, Value>::InsertUniq(const value_type& key){
  node_pointer key_pos = FindEqData(key.first);
  bool key_not_found = key.first != key_pos->data_.first; 
  if(key_not_found) InsertAll(key, key_pos);
  return key_not_found;
}

template <typename Key, typename Value>
void RB_tree<Key, Value>::Insert(const value_type& key){ InsertAll(key, FindEqData(key.first)); }


}; // namespace s21




// | Member type            | Definition                                                                             |
// |------------------------|----------------------------------------------------------------------------------------|
// | `key_type`               | `Key` the first template parameter (Key)                                                     |
// | `value_type`             | `Key` value type (the value itself is a key)                                                    |
// | `reference`              | `value_type &` defines the type of the reference to an element                                                             |
// | `const_reference`        | `const value_type &` defines the type of the constant reference                                         |
// | `iterator`               | internal class `SetIterator<T>` or `BinaryTree::iterator` as the internal iterator of tree subclass; defines the type for iterating through the container                                                 |
// | `const_iterator`         | internal class `SetConstIterator<T>` or `BinaryTree::const_iterator` as the internal const iterator of tree subclass; defines the constant type for iterating through the container                                           |
// | `size_type`              | `size_t` defines the type of the container size (standard type is size_t) |
