#ifndef CPP2_S21_CONTAINERS_MAP_MAP_H_
#define CPP2_S21_CONTAINERS_MAP_MAP_H_

#include <limits.h>
#include <math.h>
#include <stddef.h>

#include <functional>
#include <initializer_list>
#include <iostream>

#include "../RB_tree/RB_tree.h"

namespace s21 {
template <class Key, class Value, class Compare = std::less<Key>,
          class Allocator = std::allocator<std::pair<const Key, Value>>>
class map : RB_tree<Key, Value> {
 public:
  using size_type = std::size_t;
  using key_type = Key;
  using mapped_type = Value;
  using value_type = std::pair<const Key, Value>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using difference_type = std::ptrdiff_t;
  using iterator = typename RB_tree<Key, Value>::Iterator<false>;
  using const_iterator = typename RB_tree<Key, Value>::Iterator<true>;
  // struct Compare {
  //   bool operator()(const_reference value1, const_reference value2) {
  //     return value1.first < value2.first;
  //   }
  // };
  using tree_type = RB_tree<key_type, mapped_type>;

 public:
  // Constructors
  map() : tree_(new tree_type{}), size_(0) {}

  // map(const map &other) : size_(other.size_) { tree_ = other.tree_; }

  // map(map &&other) noexcept : tree_(new tree_type(std::move(*other.tree_)))
  // {}

  // // map(std::initializer_list<value_type>& items) {}

  ~map() { delete tree_; }

  // bool operator==(const map& other) {
  //   return
  // }

  // // Assignment Operators
  // map &operator=(const map &other) {
  //   tree_ = other.tree_;
  //   size_ = other.size_;
  //   return *this;
  // }

  // map &operator=(map &&other) {
  //   tree_ = std::move(other.tree_);
  //   size_ = other.size_;
  // }

  // map &operator=(std::initializer_list<value_type> &items) {}

  // Access Operators
  // Value &at(const Key &key) {}

  // Value &operator[](
  //     const Key &key) { /* Insert if key doesn't exist, then return reference
  //     */
  // }

  // const Value &at(const Key &key) const { /* Const version of at */
  // }

  // const Value &operator[](const Key &key) const { /* Const version of
  // operator[]
  // */
  // }

  // // Iterators
  iterator begin() { /* Begin iterator */
    return tree_->begin();
  }

  iterator end() { return tree_->end(); }

  // reverse_iterator rbegin() { return reverse_iterator(end()); }

  // reverse_iterator rend() { return reverse_iterator(begin()); }

  // const_iterator cbegin() const { /* Const begin iterator */
  // }

  // const_iterator cend() const { /* Const end iterator */
  // }

  // const_reverse_iterator crbegin() const {
  //   return const_reverse_iterator(cend());
  // }

  // const_reverse_iterator crend() const {
  //   return const_reverse_iterator(cbegin());
  // }

  // Capacity
  bool empty() const { return size_ == 0; }

  size_type size() const noexcept { return size_; }

  size_type max_size() const noexcept {
    return std::numeric_limits<difference_type>::max() / sizeof(RB_tree<Key, Value>);
  }

  //   size_type max_size() const noexcept { return
  // std::numeric_limits<difference_type>::max(); }

  // size_type max_size() const noexcept { return pow(2, 61) / 10; }
  // size_type max_size() const noexcept { return size_; }

  // size_type max_size() const noexcept { return
  // std::numeric_limits<size_type>::max(); }

  // Modifiers
  // void clear();
   /* std::pair<iterator, bool> */void insert(const value_type& value){
    tree_->InsertUniq(value);
   }
   /* std::pair<iterator, bool> */ void insert(const Key& key, const Value& obj){
    tree_->InsertUniq(std::make_pair(key, obj));

   }

   void fullnodeinfo(iterator it){
    tree_->FullNodeInfo(it);
   }
   iterator nnullIterartor(){
    return tree_->NNullIterartor();
   }
  //  std::pair<iterator, bool> insert_or_assign(const Key& key, const Value&
  //  obj); void erase(iterator pos);
  // void swap(map &other);
  // void merge(map &other);

  // Lookup
  // size_type count(const key_type &x) const {}
  bool blHight(){ return tree_->checkBlackHeight(); }
  bool redAlert(){ return tree_->hasConsecutiveReds(); }
  iterator find(const key_type &x) { return tree_->find(x);}

  // const_iterator find(const key_type &x) const {}

  // bool contains(const key_type &key) const {}

  // // Bonus Part
  // template <typename... Args>
  // map<std::pair<iterator, bool>> insert_many(const iterator pos,
  //                                            Args &&...args);

  // temporary helper
  void PrintMap() {
    std::cout << "Printing map:" << std::endl;
    for (const auto print : *this) {
      std::cout << "key = " << (print.first) << ", value = " << (print.second) << std::endl;
    }
  }
  void PrintMapRecursive(){
    tree_->PrintTreeRecursive(tree_->RootIterartor(), 0);
    auto it = tree_->NNullIterartor();
    std::cout << (*it).first << "\n";
  }

 private:
  tree_type *tree_;
  size_type size_;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_MAP_MAP_H_