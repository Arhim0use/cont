
#include "s21_tree.h"

namespace s21{
template<typename Key, bool Const>
class Iterator{
  friend class RB_tree<Key>;
protected:
  struct TreeNode_;

  //* Если Const равно true, то это будет указатель на константный узел 
  //* (const list_node *), иначе - указатель на изменяемый узел (list_node *).
  // using node_ = std::conditional_t<Const, const TreeNode_ , TreeNode_>;
  // using iterator = Iterator;
  using value_type = Key;
  using reference = value_type &;
  using node_pointer = std::conditional_t<Const, const TreeNode_ *, TreeNode_ *>;
public:
  Iterator() = delete;
  explicit Iterator(node_pointer node) : node_(node) {}
  ~Iterator() = default;

  Iterator& operator++();
  Iterator operator++(int);
  Iterator& operator--();
  Iterator operator--(int);
  reference operator*() { return node_->data_; }
  bool operator==(const Iterator& other) { return node_ == other.node_; }
  bool operator!=(const Iterator& other) { return node_ != other.node_; }

private:
  node_pointer node_;
}; // class Iterator

template<typename Key>
struct RB_tree<Key>::TreeNode_{
  enum NodeColor { RedN, BlackN };
  using value_type = Key;
  using node_pointer = TreeNode_ *;
    value_type data_;
    TreeNode_ *parent_, *right_, *left_;
    // Red - 0 Black - 1
    bool RedBlack_;

    explicit TreeNode_() 
              : data_(value_type()), parent_(nullptr), left_(nullptr), right_(nullptr), RedBlack_(RedN) {}

    explicit TreeNode_(const TreeNode_& other) : data_(other.data_), parent_(other.parent_), 
              left_(other.left_), right_(other.right_), RedBlack_(other.RedBlack_) {}

    explicit TreeNode_(TreeNode_&& other) : data_(std::move(other.data_)), parent_(std::move(other.parent_)), 
              left_(std::move(other.left_)), right_(std::move(other.right_)), RedBlack_(std::move(other.RedBlack_)) {}
/*
Если у текущего узла есть правое поддерево,
следующим узлом будет наименьший узел в 
этом правом поддереве (т.е. самый левый узел в правом поддереве).
Если у текущего узла нет правого поддерева, 
следующим узлом будет ближайший предок, 
для которого текущий узел находится в левом поддереве.
*/
    node_pointer NextNode() const noexcept {
      node_pointer next = const_cast<node_pointer>(this);
      if (next->right_){
        next = next->right_;
        while(next->left_) next = next->left_;
      } else if (!next->right_ && next->parent_){
        while (next->parent_ && next != next->parent_->left_){
          next = next->parent_;
        }
        next = next->parent_;
      }
      return next;
    }
/*
Если у текущего узла есть левое поддерево, предыдущим 
узлом будет наибольший узел в этом левом поддереве 
(т.е. самый правый узел в левом поддереве).
Если у текущего узла нет левого поддерева, предыдущим 
узлом будет ближайший предок, для которого текущий 
узел находится в правом поддереве.
*/
    node_pointer PrevNode(){
      node_pointer prev = const_cast<node_pointer>(this);
      if (prev->left_){
        prev = prev->left_;
        while(prev->right_) prev = prev->right_;
      } else if (!prev->left_ && prev->parent_){
        while(prev->parent_ && prev != prev->parent_->right_){
          prev = prev->parent_;
        }
        prev = prev->parent_;
      }
      return prev;
    }
  };
}; // namespace s21


template<typename T, bool Const>
typename s21::Iterator<T, Const>&
s21::Iterator<T, Const>::operator++(){
  node_ = node_->NextNode();
  return *this;
}

template<typename T, bool Const>
typename s21::Iterator<T, Const>
s21::Iterator<T, Const>::operator++(int){
  Iterator temp = (*this);
  ++(*this);
  return temp;
}

template<typename T, bool Const>
typename s21::Iterator<T, Const>&
s21::Iterator<T, Const>::operator--(){
  node_ = node_->PrevNode();
  return *this;
}

template<typename T, bool Const>
typename s21::Iterator<T, Const>
s21::Iterator<T, Const>::operator--(int){
  Iterator temp = (*this);
  --(*this);
  return temp; 
}




// | Member type            | Definition                                                                             |
// |------------------------|----------------------------------------------------------------------------------------|
// | `key_type`               | `Key` the first template parameter (Key)                                                     |
// | `value_type`             | `Key` value type (the value itself is a key)                                                    |
// | `reference`              | `value_type &` defines the type of the reference to an element                                                             |
// | `const_reference`        | `const value_type &` defines the type of the constant reference                                         |
// | `iterator`               | internal class `SetIterator<T>` or `BinaryTree::iterator` as the internal iterator of tree subclass; defines the type for iterating through the container                                                 |
// | `const_iterator`         | internal class `SetConstIterator<T>` or `BinaryTree::const_iterator` as the internal const iterator of tree subclass; defines the constant type for iterating through the container                                           |
// | `size_type`              | `size_t` defines the type of the container size (standard type is size_t) |
