#ifndef __S21_TREE_H__
#define __S21_TREE_H__

namespace s21 {
template<typename T>
class s21_tree
{
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = std::size_t;
public:
  s21_tree(/* args */);
  ~s21_tree();
  iterator begin();
  iterator end(){ return nullptr; }
  iterator find(const Key& key);


private:
  template<typename Key_T, typename Value_T,  bool Const>
    class iterator{
      enum NodeColor { RedN, BlackN };
      struct TreeNode_;

      //* Если Const равно true, то это будет указатель на константный узел 
      //* (const list_node *), иначе - указатель на изменяемый узел (list_node *).
      // using t_node_ = std::conditional_t<Const, const TreeNode_ , TreeNode_>;
      using node_pointer = std::conditional_t<Const, const TreeNode_ *, TreeNode_ *>;
      using pointer = std::conditional_t<Const, const Value_T *, Value_T *>;
      using reference = std::conditional_t<Const, const Value_T &, Value_T &>;

    public:
      iterator() = delete;
      explicit iterator(node_pointer node) : node_(node) {}
      ~iterator() = default;

      iterator& operator++();
      iterator operator++(int);
      iterator& operator--();
      iterator operator--(int);
      reference operator*() { return data_; }
      bool operator==(const iterator& other) { return node_ == other.node_; }
      bool operator!=(const iterator& other) { return node_ != other.node_; }

    private:
      node_pointer node_;
      struct TreeNode_{
        value_type data_ = data();

        TreeNode_ *parent_;
        TreeNode_ *right_;
        TreeNode_ *left_;
        // Red - 0 Black - 1
        bool RedBlack_;

        explicit TreeNode_(value_type data = data(), TreeNode_ parent = nullptr, TreeNode_ left = nullptr, TreeNode_ right = nullptr) 
                  : data_(data), parent_(parent), left_(left), right_(right), RedBlack_(RedN) {}

        explicit TreeNode_(const TreeNode_& other) : data_(other.data_), parent_(other.parent_), 
                  left_(other.left_), right_(other.right_), RedBlack_(other.RedBlack_) {}

        explicit TreeNode_(TreeNode_&& other) : data_(std::move(other.data_)), parent_(std::move(other.parent_)), 
                  left_(std::move(other.left_)), right_(std::move(other.right_)), RedBlack_(std::move(other.RedBlack_)) {}
        
      }

      TreeNode_ nextNode();
      TreeNode_ prevNode();

    }; // class iterator
  
  /* data */
};
}

#include "s21_tree.tpp"
#endif // __S21_SET_H__

