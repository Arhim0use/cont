#ifndef __S21_TREE_H__
#define __S21_TREE_H__

namespace s21 {
template<typename Key>
class RB_tree
{
  template<bool Const>
  class Iterator;
  protected:
  struct TreeNode_;
  
  using value_type = Key;
  using reference = value_type &;
  using difference_type = std::ptrdiff_t;
  using iterator_category = std::forward_iterator_tag;
  using const_reference = const value_type &;
  using size_type = std::size_t;
  using iterator = std::conditional_t<false, Iterator<false>, Iterator<false>>;
  using const_iterator = std::conditional_t<true, Iterator<true>, Iterator<true>>;
  using node_pointer = TreeNode_ *;
  using const_node_pointer = const TreeNode_ *;

public:
  RB_tree(/* args */);
  ~RB_tree();
  iterator begin();
  iterator end(){ return nullptr; }
  iterator find(const Key& key);

private:
  node_pointer node_;
};
} // namespace s21
#include "s21_tree.tpp"
#endif // __S21_SET_H__

