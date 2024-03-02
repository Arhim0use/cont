#include "s21_set.h"

namespace s21{
template <typename Key, class Compare, class Allocator>
set<Key, Compare, Allocator>::set() : tree_(new tree_type()), size_(0) {}

template <typename Key, class Compare, class Allocator>
set<Key, Compare, Allocator>::set(std::initializer_list<value_type> const &items) : tree_(new tree_type()), size_(0) {
  for (auto &&item : items) insert(item);
}

template <typename Key, class Compare, class Allocator>
set<Key, Compare, Allocator>::set(const set &s) : tree_(new tree_type(*s.tree_))
  //  *tree_ = RB_tree<Key, char>(*(s.tree_));
  // tree_(new tree_type())
, size_(s.size_) {
  
  // if(this != &s)
  // tree_->CopyTree(*(s.tree_));
  // *tree_ = *s.tree_;
  // RB_tree<Key, char>(s.tree_);
}

template <typename Key, class Compare, class Allocator>
set<Key, Compare, Allocator>::set(set &&s) : tree_(s.tree_), size_(s.size_) {
  s.tree_ = nullptr;
  s.size_ = 0;
}

template <typename Key, class Compare, class Allocator>
set<Key, Compare, Allocator>::~set() {
  delete tree_;
  size_ = 0;
}

template <typename Key, class Compare, class Allocator>
set<Key, Compare, Allocator>& set<Key, Compare, Allocator>::operator=(set &&s){
  if(this != &s){
    delete tree_;
    tree_ = s.tree_;
    size_ = s.size_;
    s.tree_ = nullptr;
    s.size_ = 0;
  }
  return *this;
}

template <typename Key, class Compare, class Allocator>
set<Key, Compare, Allocator> set<Key, Compare, Allocator>::operator=(const set &s){
  if(this != &s){
    delete tree_;
    *tree_ = *(s.tree_);
    size_ = s.size_;
  }
  return *this;
}

template <typename Key, class Compare, class Allocator>
bool set<Key, Compare, Allocator>::empty() { return size_ == 0; }

template <typename Key, class Compare, class Allocator>
std::size_t set<Key, Compare, Allocator>::size(){ return size_; }

template <typename Key, class Compare, class Allocator>
std::pair<typename set<Key, Compare, Allocator>::iterator, bool> 
set<Key, Compare, Allocator>::insert(const Key &value){
  std::pair<iterator,bool> pair = tree_->InsertUniq({value, 0});
  if(!pair.second) size_++;
  return {set::iterator (pair.first), !pair.second};
}

template <typename Key, class Compare, class Allocator>
void set<Key, Compare, Allocator>::merge(set& other){ 
  if(this != &other){
    for (auto other_it = other.begin(); other_it != other.end(); ++other_it){
      insert(*other_it);
    }
  }
}

template <typename Key, class Compare, class Allocator>
void set<Key, Compare, Allocator>::swap(set& other){
  if (this != &other){
    tree_type *temp = other.tree_;
    other.tree_ = tree_;
    tree_ = temp;

    size_type temp_size = other.size_;
    other.size_ = size_;
    size_ = temp_size;
  }
}

template <typename Key, class Compare, class Allocator>
void set<Key, Compare, Allocator>::clear(){
  tree_->CleanTree();
  size_ = 0;
}

template <typename Key, class Compare, class Allocator>
typename set<Key, Compare, Allocator>::iterator 
set<Key, Compare, Allocator>::begin(){ return set::iterator (tree_->begin()); }
template <typename Key, class Compare, class Allocator>
typename set<Key, Compare, Allocator>::iterator 
set<Key, Compare, Allocator>::end(){ return set::iterator(tree_->end()); }
template <typename Key, class Compare, class Allocator>
typename set<Key, Compare, Allocator>::iterator 
set<Key, Compare, Allocator>::find(const Key& key){ return set::iterator (tree_->find(key)); }

template <typename Key, class Compare, class Allocator>
typename set<Key, Compare, Allocator>::const_iterator 
set<Key, Compare, Allocator>::cbegin(){ return set::const_iterator (tree_->begin()); }
template <typename Key, class Compare, class Allocator>
typename set<Key, Compare, Allocator>::const_iterator 
set<Key, Compare, Allocator>::cend(){ return set::const_iterator(tree_->end()); }

template <typename Key, class Compare, class Allocator>
bool set<Key, Compare, Allocator>::contains(const Key& key){ return (tree_->FindEqData(key).second); }

template <typename Key, class Compare, class Allocator>
bool set<Key, Compare, Allocator>::RedAlert(){ return tree_->hasConsecutiveReds(); } // проверка красных пар child-parent

template <typename Key, class Compare, class Allocator>
bool set<Key, Compare, Allocator>::BLM(){ return tree_->CheckBlackHeight(); } // проверка одинаковости черных высот






} // namespace s21