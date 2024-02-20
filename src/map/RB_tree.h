#ifndef __S21_TREE_H__
#define __S21_TREE_H__

#include <iostream>

// #include "iterator_bool.h"

namespace s21 {

enum NodeColor { RedN, BlackN };

template <typename Key, typename Value>
class RB_tree {
  struct TreeNode_;

 public:
  template <bool Const>
  class Iterator;

  using key_type = Key;
  using mapped_type = Value;
  using value_type = std::pair<const Key, Value>;
  using reference = value_type&;
  using difference_type = std::ptrdiff_t;
  using iterator_category = std::forward_iterator_tag;
  using const_reference = const value_type&;
  using size_type = std::size_t;
  using iterator = Iterator<false>;
  using const_iterator = Iterator<true>;
  using node_pointer = TreeNode_*;
  using const_node_pointer = const TreeNode_*;

  RB_tree() : root_(nullptr){ Init_n_nul(); }
  ~RB_tree(){
    DeleteTreeRecursive(root_);
    delete n_null_;
  }

  void InsertAll(const value_type& key, node_pointer key_position);
  bool InsertUniq(const value_type& key);
  void Insert(const value_type& key);

  node_pointer DeleteNode(const value_type& key);
  void CleanTree();

  // node_pointer SmallLeftRotate(node_pointer node){
  //   node_pointer parent = node->parent_;
  //   node_pointer grandparent = node->parent_->parent_;
  //   node_pointer uncle = grandparent->left_;
    

  // }

  /// @brief УДАЛИТЬ перед сдачей проекта
  iterator RootIterartor(){
    return iterator (root_);
  }

  iterator begin(){
    node_pointer left = GoLeft();
    return iterator (left); 
  }
  const_iterator cbegin(){
    node_pointer left = GoLeft();
    return const_iterator (left); 
  }
  iterator end(){ return iterator(n_null_); }
  // надо чтоб возвращал ноду n_null если не нашел ноду
  iterator find(const Key& key){ 
    node_pointer node = FindEqData(key);   
    return (node->data_.first == key ? iterator (node) : iterator (n_null_));  
  }


  void PrintTree();
  void PrintTreeRecursive(iterator it, int depth) const ;
  void FullNodeInfo(const_iterator cit) noexcept ;

private:
  node_pointer root_;
  // n_null должна хранить size_t size - размер дерева или при раскрытии ячейки окрывать сайз
  // либо при разыменовании раскрывать size как переменную из дерева
  node_pointer n_null_;

  node_pointer GoLeft();
  node_pointer GoRight();
  node_pointer InitNode();
  node_pointer InitNode(const value_type& key);
  void Init_n_nul();

  /// @return возвращает ноду с одинаковой датой, если не нашел - предпоследнюю 
  node_pointer FindEqData(const Key& first);
  void DeleteTreeRecursive(node_pointer node);
  void NodeTransfer(node_pointer replaceable, node_pointer replacing);
  void LeftOrRight(node_pointer checked, node_pointer insert);
};

template<typename Key, typename Value> template <bool Const>
class RB_tree<Key, Value>::Iterator {
  //* Если Const равно true, то это будет указатель на константный узел
  //* (const list_node *), иначе - указатель на изменяемый узел (list_node *).
  // using node_ = std::conditional_t<Const, const TreeNode_ , TreeNode_>;
  using key_type = Key;
  using mapped_type = Value;
  using value_type = std::pair<const Key, Value>;
  using node_pointer =
      std::conditional_t<Const, const TreeNode_*, TreeNode_*>;

  public:
  Iterator() = delete;
  explicit Iterator(node_pointer node) : node_(node) {}
  ~Iterator() = default;
  
  Iterator& operator++();
  Iterator& operator--();
  Iterator operator++(int);
  Iterator operator--(int);
  
  bool operator==(const Iterator& other);
  bool operator!=(const Iterator& other);

  value_type operator*() { return node_->data_; }
  operator Iterator<true>() { return Iterator<true>(node_); }



  /// @brief УДАЛИТЬ перед финишем проекта
  node_pointer GetNodePointer() const noexcept {
    return const_cast<TreeNode_*>(node_);
  }
  /// @brief УДАЛИТЬ перед финишем проекта
  operator Iterator<false>() const noexcept {
    return Iterator<false>(const_cast<TreeNode_*>(node_));
  }

  friend class RB_tree;

  private:
  node_pointer node_;
};  // class Iterator
}; // namespace s21

#include "tree_node.tpp"
#include "iterator_bool.tpp"
#include "s21_tree.tpp"



#include "s21_common_func.tpp"
#endif // __S21_SET_H__
