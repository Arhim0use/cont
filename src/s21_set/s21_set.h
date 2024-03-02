#ifndef CPP2_S21_CONTAINERS_S21_SET_H_
#define CPP2_S21_CONTAINERS_S21_SET_H_


#include <limits.h>
#include <math.h>
#include <stddef.h>

#include <vector>
#include <functional>
#include <initializer_list>
#include <iostream>

#include "../RB_tree/RB_tree.h"

namespace s21 {
template <typename Key, class Compare = std::less<Key>,
          class Allocator = std::allocator<std::pair<const Key, char>>>
class set  : RB_tree<Key, char>
{

  using value_type = Key;
  // using value_type = std::pair<const Key, char>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using tree_type = RB_tree<value_type, char>;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using iterator_category = std::forward_iterator_tag;
  using Base = RB_tree<Key, char>;

public:
  template <bool Const>
  class SetIterator;
  using iterator = SetIterator<false>;
  using const_iterator = SetIterator<true>;

  set();
  set(std::initializer_list<value_type> const &items);
  set(const set &s);
  set(set &&s);
  ~set();
  
  set &operator=(set &&s);
  set operator=(const set &s);

  bool empty();
  size_type size();
  size_type max_size();

  void clear();

  std::pair<iterator, bool> insert(const value_type& value);
  template<typename... Args>
  std::vector<std::pair<iterator,bool>> insert_many(Args&&... items);
  void erase(iterator pos);
  void erase(const value_type& value);
  
  void swap(set& other);
  void merge(set& other);

  iterator begin();
  iterator end();
  const_iterator cbegin();
  const_iterator cend();
  
  iterator find(const Key& key);
  bool contains(const Key& key);

  bool RedAlert(); // проверка красных пар child-parent
  bool BLM(); // проверка одинаковости черных высот

  void PrintTreeRecursive() { tree_->PrintTreeRecursive(tree_->RootIterartor(), 0); }
  void DeleteNode(const Key& key);
  void FullNodeInfo(const Key& key);


private:
  tree_type *tree_;
  size_type size_;
}; // class set

// Наследование класса итератора для перегрузки оператора * для доступа к ключу из класса сет
template <typename Key, class Compare, class Allocator> template <bool Const>
class set<Key, Compare, Allocator>::SetIterator : 
public set<Key, Compare, Allocator>::RB_tree<Key, char>::template Iterator<Const> {
public:
    using BaseIterator = typename Base::template Iterator<Const>;

    SetIterator(const BaseIterator& baseIterator)
    : BaseIterator(baseIterator) {}

    value_type operator*() {
        return BaseIterator::operator*().first; 
    }
}; // class set<Key, Compare, Allocator>::SetIterator

} // namespace s21

#include "s21_set.tpp"
#endif // CPP2_S21_CONTAINERS_S21_SET_H_
