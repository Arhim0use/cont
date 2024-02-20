#include "RB_tree.h"

namespace s21 {

template<typename Key, typename Value> template <bool Const>
typename RB_tree<Key, Value>::Iterator<Const> &RB_tree<Key, Value>::Iterator<Const>::operator++(){
  node_ = node_->NextNode();
  return *this;
}

template<typename Key, typename Value> template <bool Const>
typename RB_tree<Key, Value>::Iterator<Const> &RB_tree<Key, Value>::Iterator<Const>::operator--(){
  node_ = node_->PrevNode();
  return *this;
}

template<typename Key, typename Value> template <bool Const>
typename RB_tree<Key, Value>::Iterator<Const> RB_tree<Key, Value>::Iterator<Const>::operator++(int){
  Iterator temp = (*this);
  ++(*this);
  return temp;
}

template<typename Key, typename Value> template <bool Const>
typename RB_tree<Key, Value>::Iterator<Const> RB_tree<Key, Value>::Iterator<Const>::operator--(int){
  Iterator temp = (*this);
  --(*this);
  return temp;
}

template<typename Key, typename Value> template <bool Const>
bool RB_tree<Key, Value>::Iterator<Const>::operator==(const Iterator& other){
  return node_ == other.node_;
}

template<typename Key, typename Value> template <bool Const>
bool RB_tree<Key, Value>::Iterator<Const>::operator!=(const Iterator& other){
  return node_ != other.node_;
}
} // namespace s21 