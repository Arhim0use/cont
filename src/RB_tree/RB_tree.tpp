
#include "RB_tree.h"

namespace s21{

struct TreeNode_;  
template <bool Const>
class Iterator;

using node_pointer = TreeNode_ *;
using iterator = Iterator<false>;
using const_iterator = Iterator<true>;

template <typename Key, typename Value>
RB_tree<Key, Value>::RB_tree() : root_(nullptr) { Init_n_nul(); }
template <typename Key, typename Value>
RB_tree<Key, Value>::RB_tree(const RB_tree& other) : root_(nullptr) {
  Init_n_nul();
  CopyTree(other);
}
template <typename Key, typename Value>
RB_tree<Key, Value>::RB_tree(RB_tree&& other) : root_(nullptr) {
  this->DeleteTreeRecursive(root_);
  delete n_null_;
  root_ = other.root_;
  n_null_ = other.n_null_;
  other.root_ = nullptr;
  other.n_null_ = nullptr;
}
template <typename Key, typename Value>
RB_tree<Key, Value>::~RB_tree() {
  DeleteTreeRecursive(root_);
  delete n_null_;
}

template <typename Key, typename Value>
RB_tree<Key, Value>& RB_tree<Key, Value>::operator=(RB_tree&& other){
  if (this != &other){
    DeleteTreeRecursive(root_);
    delete n_null_;
    root_ = other.root_; 
    n_null_ = other.n_null_;
    other.root_ = nullptr;
    other.n_null_ = nullptr;
  } 
  return *this;
}

template <typename Key, typename Value>
RB_tree<Key, Value> RB_tree<Key, Value>::operator=(const RB_tree& other){
  if (this != &other){
    CleanTree();
    CopyTree(other);

  }
    return *this;
}

template <typename Key, typename Value>
typename RB_tree<Key, Value>::node_pointer
RB_tree<Key, Value>::CopyNodeRecursive(const node_pointer &other_node, const node_pointer &other_n_null)  {
  if (other_node == other_n_null) return n_null_;

  node_pointer new_node = InitNode();
  new_node->data_ = other_node->data_;
  new_node->color_ = other_node->color_;
  new_node->left_ = CopyNodeRecursive(other_node->left_, other_n_null);
  if (new_node->left_ != n_null_) new_node->left_->parent_ = new_node;
  new_node->right_ = CopyNodeRecursive(other_node->right_, other_n_null);
  if (new_node->right_ != n_null_) new_node->right_->parent_ = new_node;

  return new_node;
}

template <typename Key, typename Value>
void RB_tree<Key, Value>::CopyTree(const RB_tree& other) {
  DeleteTreeRecursive(root_); 
  // if(!root_) root_ = new TreeNode_();
  root_ = CopyNodeRecursive(other.root_, other.n_null_);
  if (root_ != n_null_) root_->parent_ = n_null_;
  n_null_->parent_ = GoRight();
}

template <typename Key, typename Value>
typename RB_tree<Key, Value>::node_pointer
RB_tree<Key, Value>::GoLeft() noexcept {
  node_pointer temp = const_cast<node_pointer>(root_);
  while (temp->left_  && temp->left_ != n_null_){
    temp = temp->left_;
  }
  return temp;
}

template <typename Key, typename Value>
typename RB_tree<Key, Value>::node_pointer
RB_tree<Key, Value>::GoRight() noexcept {
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
void RB_tree<Key, Value>::DeleteTreeRecursive(node_pointer node){
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

// template <typename Key, typename Value>
// void RB_tree<Key, Value>::NodeTransfer(node_pointer node, node_pointer prev) noexcept {
//   prev->parent_ = node->parent_;

//   if(prev != node->left_) prev->left_ = node->left_;
//   if(prev != node->right_) prev->right_ = node->right_;

//   if(prev->left_ != n_null_) prev->left_->parent_ = prev.parent;
//   if(prev->right_ != n_null_) prev->right_->parent_ = prev;
//   if(prev->parent_ != n_null_) LeftOrRight(node, prev);
// }

template <typename Key, typename Value>
void RB_tree<Key, Value>::NodeTransfer(node_pointer replaceable, node_pointer replacing) noexcept {
  replacing->parent_ = replaceable->parent_;
  if(replacing != replaceable->left_) replacing->left_ = replaceable->left_;
  if(replacing != replaceable->right_) replacing->right_ = replaceable->right_;
  if(replacing->left_ != n_null_) replacing->left_->parent_ = replacing->parent_;
  if(replacing->right_ != n_null_) replacing->right_->parent_ = replacing;
  if(replacing->parent_ != n_null_) LeftOrRight(replaceable, replacing);
}

template <typename Key, typename Value>
void RB_tree<Key, Value>::LeftOrRight(node_pointer checked, node_pointer insert) noexcept {
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

template<typename Key, typename Value>
std::pair<typename RB_tree<Key, Value>::node_pointer, bool> 
RB_tree<Key, Value>::FindEqData(const Key& first) const noexcept { 
  node_pointer eq_node = root_;
  std::pair<node_pointer, bool> exit = {eq_node, true};
  if(!eq_node){
    exit = std::make_pair(n_null_, false);
  } else {
    while (eq_node->data_.first != first) {
      bool key_less = eq_node->data_.first > first;
      if(!key_less && eq_node->right_ != n_null_) {
        eq_node = eq_node->right_;
      } else if(key_less && eq_node->left_!= n_null_) {
        eq_node = eq_node->left_;
      } else if ((!key_less && eq_node->right_ == n_null_) || (key_less && eq_node->left_ == n_null_) 
        || (eq_node->right_ == n_null_ && eq_node->left_ == n_null_)){
        exit = {eq_node, false};
        break;
      }
    }
    if (exit.second) exit.first = eq_node;
  }
  return exit;
}

template <typename Key, typename Value>
typename RB_tree<Key, Value>::node_pointer
RB_tree<Key, Value>::DeleteNode(const key_type& key){
  std::pair<node_pointer, bool> pair = FindEqData(key);
  node_pointer node = pair.first;
  node_pointer prev = node->PrevNode();
  if (pair.second == true){
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
  return prev;
}

template <typename Key, typename Value>
void RB_tree<Key, Value>::CleanTree(){
  DeleteTreeRecursive(root_);
  root_ = n_null_;
  n_null_->data_.first = 0;
}

template <typename Key, typename Value>
typename RB_tree<Key, Value>::node_pointer
RB_tree<Key, Value>::InsertAll(const value_type& key, node_pointer key_position){
  node_pointer new_node = InitNode(key);
  if (!root_ || root_ == n_null_) {
    root_ = new_node;
    root_->color_ = BlackN;
  } else {
    node_pointer temp = key_position;
    if(temp->data_.first > key.first){
      // if (temp->left_ != n_null_){ // по идее нужна только нижняя подобная конструкция 
      //   temp->left_->parent_ = new_node;
      //   new_node->left_ = temp->left_;
      // }
      temp->left_ = new_node;
      new_node->parent_ = temp;
    } else {
      // if (temp->right_ != n_null_){ // <= key insert if duplicates and node does't a leaf
      //   temp->right_->parent_ = new_node;
      //   new_node->right_ = temp->right_;
      // }
      temp->right_ = new_node;
      new_node->parent_ = temp;
    }
    BalanceAfterIncert(new_node);
    root_->color_ = BlackN;
  }
  n_null_->parent_ = GoRight();
  return new_node;
}

template<typename Key, typename Value>
std::pair<typename RB_tree<Key, Value>::iterator, bool> 
RB_tree<Key, Value>::InsertUniq(const value_type& key){
  std::pair<node_pointer, bool> pair = FindEqData(key.first);
  node_pointer node = pair.first;
  if(pair.second == false) node = InsertAll(key, pair.first);
  return {iterator(node), pair.second};
}

template <typename Key, typename Value>
void RB_tree<Key, Value>::Insert(const value_type& key){ InsertAll(key, FindEqData(key.first).first); }

template<class Key, class Value> 
inline typename RB_tree<Key, Value>::iterator 
RB_tree<Key, Value>::find(const Key& key) noexcept { 
  std::pair<node_pointer, bool> pair = FindEqData(key); 
  return (pair.second ? iterator (pair.first) : iterator (n_null_));  
}

template<class Key, class Value> 
inline typename RB_tree<Key, Value>::iterator 
RB_tree<Key, Value>::end() noexcept { return iterator(n_null_); }

template<class Key, class Value> 
inline typename RB_tree<Key, Value>::iterator 
RB_tree<Key, Value>::begin() noexcept { return iterator(GoLeft()); }

template<class Key, class Value> 
inline typename RB_tree<Key, Value>::const_iterator 
RB_tree<Key, Value>::cend() noexcept { return const_iterator(n_null_); }

template<class Key, class Value> 
inline typename RB_tree<Key, Value>::const_iterator 
RB_tree<Key, Value>::cbegin() noexcept { return const_iterator(GoLeft()); }

template <typename Key, typename Value>
void RB_tree<Key, Value>::SmallRotate(node_pointer node, bool L_R) noexcept {
  node_pointer grandparent = GetGrandparent(node);
  node_pointer parent = node->parent_;
  node_pointer n_child = L_R ? node->left_ : node->right_; 
  if(grandparent != n_null_) LeftOrRight(parent, node);
  node->parent_ = grandparent;
  parent->parent_ = node;
  if (L_R){
    parent->right_ = n_child; 
    node->left_ = parent;
  } else {
    parent->left_ = n_child;
    node->right_ = parent;
  }
  if(n_child != n_null_) n_child->parent_ = parent;
}

template <typename Key, typename Value>
void RB_tree<Key, Value>::BigRotate(node_pointer node, bool L_R) noexcept {
  node_pointer grandparent = GetGrandparent(node);
  node_pointer parent = node->parent_;
  node_pointer grandgrandparent = grandparent->parent_;
  if(grandgrandparent != n_null_)
    LeftOrRight(grandparent, parent);
  parent->parent_ = grandgrandparent;
  grandparent->parent_ = parent;  

  node_pointer p_child = L_R ? parent->right_ : parent->left_;
  if (p_child != n_null_) p_child->parent_ = grandparent;
  if(L_R){
    parent->right_ = grandparent;
    grandparent->left_ = p_child;
  } else {
    parent->left_ = grandparent;
    grandparent->right_ = p_child;
  }

  if(grandparent == root_){
    root_ = parent;
  } 
  if(parent != root_) parent->SwitchNodeColor();
  if(grandparent != root_)grandparent->SwitchNodeColor(); 
}

template <typename Key, typename Value>
void RB_tree<Key, Value>::BalanceAfterIncert(node_pointer node) noexcept {
  if(node->parent_->color_ == RedN){
    node_pointer parent = node->parent_;
    if(GetGrandparent(node)->color_ == BlackN){
      if (GetUncle(node)->color_ == RedN){
        GetGrandparent(node)->SwitchNodeColor();
        GetUncle(node)->SwitchNodeColor();
        parent->SwitchNodeColor();
        BalanceAfterIncert(GetGrandparent(node));
      } else {
        if(GetGrandparent(node)->left_ == parent && parent->right_ == node){
          SmallRotate(node, 1);
          if(parent != n_null_) BalanceAfterIncert(parent);
        } else if(GetGrandparent(node)->right_ == parent && parent->left_ == node){
          SmallRotate(node, 0);
          if(parent != n_null_) BalanceAfterIncert(parent);
        } else if (GetGrandparent(node)->left_ == parent && parent->left_ == node){
          BigRotate(node, 1);
        } else if (GetGrandparent(node)->right_ == parent && parent->right_ == node){
          BigRotate(node, 0);
        }
      }  
    }
  }
}

template <typename Key, typename Value>
typename RB_tree<Key, Value>::node_pointer
RB_tree<Key, Value>::GetUncle(node_pointer node) noexcept {
  if (node->parent_ == n_null_ || node->parent_->parent_ == n_null_) {
    return n_null_;  // The node does not have an uncle
  }
  if (node->parent_ == node->parent_->parent_->left_) {
    return node->parent_->parent_->right_;
  } else {
    return node->parent_->parent_->left_;
  }
}

template <typename Key, typename Value>
typename RB_tree<Key, Value>::node_pointer
RB_tree<Key, Value>::GetGrandparent(node_pointer node) noexcept {
  if (node->parent_ == n_null_) {
    return n_null_; 
  }
  return node->parent_->parent_;
}

template <typename Key, typename Value>
typename RB_tree<Key, Value>::node_pointer
RB_tree<Key, Value>::GetSibling(node_pointer node) noexcept {
  if (node == node->parent_->left_) {
    return node->parent->right_;
  } else {
    return node->parent->left_;
  }
}

} // namespace s21


