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

  RB_tree();
  RB_tree(const RB_tree& other);
  RB_tree(RB_tree&& other);
  ~RB_tree();

  RB_tree &operator=(RB_tree&& other);
  RB_tree operator=(const RB_tree& other);

  /// @brief УДАЛИТЬ перед сдачей проекта
  iterator RootIterartor(){
    return iterator (root_);
  }
  iterator NNullIterartor(){
    return iterator (n_null_);
  }
  void PrintTree();
  void PrintTreeRecursive(iterator it, int depth) const ;
  void FullNodeInfo(const_iterator cit) noexcept ;

  // Рекурсивно копирует дерево;
  void CopyTree(const RB_tree& other);
  node_pointer CopyNodeRecursive(const node_pointer &other_node, const node_pointer &other_n_null);
  
  // Вставляет элемент(пару) в позицию за key_position
  node_pointer InsertAll(const value_type& key, node_pointer key_position);
  /// @brief Вставляет только уникальные
  /// @return итератор на вставленный элемент или равный по key и bool был равный key или нет
  std::pair<iterator, bool> InsertUniq(const value_type& key);
  // Вставляет в любом случае
  void Insert(const value_type& key);

  /// @return возвращает ноду с одинаковой датой, если не нашел - предпоследнюю, и bool был равный key или нет
  std::pair<node_pointer, bool> FindEqData(const Key& first) const noexcept;

  node_pointer DeleteNode(const key_type& key);
  void CleanTree();
  void DeleteTreeRecursive(node_pointer node);

  inline iterator begin() noexcept;
  inline const_iterator cbegin() noexcept;
  inline iterator end() noexcept;
  inline const_iterator cend() noexcept;
  inline iterator find(const Key& key) noexcept;

  // 1 -  если черная высота между ветками дельта 1; 0 - если высота между ветками не равна
  bool CheckBlackHeight() const noexcept;
  // 1 - если есть пара сын-отец красные, 0 - если все хорошо
  bool hasConsecutiveReds() const;

private:
  node_pointer root_;
  // n_null должна хранить size_t size - размер дерева или при раскрытии ячейки окрывать сайз
  // либо при разыменовании раскрывать size как переменную из дерева
  node_pointer n_null_;

  /// @brief идет на лево до конца дерева
  node_pointer GoLeft() noexcept;
  /// @brief идет на право до конца дерева
  node_pointer GoRight() noexcept;
  /// @brief создает ноду с дефолтным конструктором
  node_pointer InitNode();
  /// @brief копирует в ноду кей
  node_pointer InitNode(const value_type& key);
  void Init_n_nul();

  /// @brief заменяет ссылки на родственников той ноды что встает вместо удаляемой (вместо левой, встаёт правая)
  void NodeTransfer(node_pointer replaceable, node_pointer replacing) noexcept;
  
  /// @brief Смотрит checked стоит слева или справа от checked.parent и на место checked ставит insert
  void LeftOrRight(node_pointer checked, node_pointer insert) noexcept;

  /// @param  L_R 0 - left 1 - right
  void SmallRotate(node_pointer node, bool L_R) noexcept;
  /// @param  L_R 0 - left 1 - right
  void BigRotate(node_pointer node, bool L_R) noexcept;
  void BalanceAfterIncert(node_pointer node) noexcept;
  // возвращает Дядю
  node_pointer GetUncle(node_pointer node) noexcept;
  // возвращает Деда
  node_pointer GetGrandparent(node_pointer node) noexcept;
  // возвращает Брата
  node_pointer GetSibling(node_pointer node) noexcept;

  // Рекурсивная вспомогательная функция для проверки
  bool CheckRedFamily(node_pointer node, bool alert) const noexcept;

  int FindMinBlackHeight(node_pointer node, int currentHeight) const;

  int FindMaxBlackHeight(node_pointer node, int currentHeight) const;

}; // class RB_tree

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
  
  Iterator& operator++() noexcept;
  Iterator& operator--() noexcept;
  Iterator operator++(int) noexcept;
  Iterator operator--(int) noexcept;
  
  inline bool operator==(const Iterator& other) const;
  inline bool operator!=(const Iterator& other) const;

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
} // namespace s21

#include "tree_node.tpp"
#include "iterator_bool.tpp"
#include "RB_tree.tpp"

#include "s21_common_func.tpp"
#endif // __S21_SET_H__

