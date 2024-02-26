#ifndef __S21_TREE_H__
#define __S21_TREE_H__

#include <iostream>
#include <stack>

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
  using const_reference = const value_type&;
  using size_type = std::size_t;
  using iterator = Iterator<false>;
  using const_iterator = Iterator<true>;
  using node_pointer = TreeNode_*;

  RB_tree() : root_(nullptr){ Init_n_nul(); }
  ~RB_tree(){
    DeleteTreeRecursive(root_);
    delete n_null_;
  }

  /// @brief УДАЛИТЬ перед сдачей проекта
  iterator RootIterartor(){
    return iterator (root_);
  }
  iterator NNullIterartor(){
    return iterator (n_null_);
  }

  node_pointer InsertAll(const value_type& key, node_pointer key_position);
  std::pair<iterator, bool> InsertUniq(const value_type& key);
  void Insert(const value_type& key);

  node_pointer DeleteNode(const value_type& key);
  void CleanTree();
  void DeleteTreeRecursive(node_pointer node);

  inline iterator begin();
  inline const_iterator cbegin();
  inline iterator end();
  inline const_iterator cend();
  inline iterator find(const Key& key);


  void PrintTree();
  void PrintTreeRecursive(iterator it, int depth) const ;
  void FullNodeInfo(const_iterator cit) noexcept ;

  // 1 -  если черная высота между ветками дельта 1; 0 - если высота между ветками не равна
  bool checkBlackHeight();
  // 1 - если есть пара сын-отец красные, 0 - если все хорошо
  bool hasConsecutiveReds() const;

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
  std::pair<node_pointer, bool> FindEqData(const Key& first) const;
  void NodeTransfer(node_pointer replaceable, node_pointer replacing);
  void LeftOrRight(node_pointer checked, node_pointer insert);

  /// @param  L_R 0 - left 1 - right
  void SmallRotate(node_pointer node, bool L_R);
  /// @param  L_R 0 - left 1 - right
  void BigRotate(node_pointer node, bool L_R);
  void BalanceAfterIncert(node_pointer node);
  node_pointer GetUncle(node_pointer node);
  node_pointer GetGrandparent(node_pointer node);
  node_pointer GetSibling(node_pointer node);

    // Рекурсивная вспомогательная функция для проверки
  bool checkConsecutiveReds(node_pointer node, bool alert) const;
};

template<typename Key, typename Value> template <bool Const>
class RB_tree<Key, Value>::Iterator {

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
#include "RB_tree.tpp"

#include "s21_common_func.tpp"
#endif // __S21_SET_H__

