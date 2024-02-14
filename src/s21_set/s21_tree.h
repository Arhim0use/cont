#ifndef __S21_TREE_H__
#define __S21_TREE_H__

#include <iostream>

// #include "iterator_bool.h"

namespace s21 {

enum NodeColor { RedN, BlackN };

template<typename Key>
class RB_tree
{
  struct TreeNode_;
  
public:

  template<bool Const>
  class Iterator{
      //* Если Const равно true, то это будет указатель на константный узел 
      //* (const list_node *), иначе - указатель на изменяемый узел (list_node *).
      // using node_ = std::conditional_t<Const, const TreeNode_ , TreeNode_>;
      using value_type = Key;
      // using value_type = const Key;
      using reference = value_type &;
      using node_pointer = std::conditional_t<Const, const TreeNode_ *, TreeNode_ *>;
    public:
      Iterator() = delete;
      explicit Iterator(node_pointer node) : node_(node) {}
      ~Iterator() = default;
      Iterator& operator++(){
        node_ = node_->NextNode();
        return *this;
      }
      Iterator operator++(int){
        Iterator temp = (*this);
        ++(*this);
        return temp;
      }
      Iterator& operator--(){
        node_ = node_->PrevNode();
        return *this;
      }
      Iterator operator--(int){
        Iterator temp = (*this);
        --(*this);
        return temp; 
      }
      value_type operator*() { return node_->data_; }

      node_pointer GetNodePointer() const noexcept { return const_cast<TreeNode_*>(node_); }
      bool operator==(const Iterator& other) { return node_ == other.node_; }
      bool operator!=(const Iterator& other) { return node_ != other.node_; }
      operator Iterator<true>(){ return Iterator<true>(node_); }
      operator Iterator<false>() const noexcept { return Iterator<false>(const_cast<TreeNode_*>(node_)); }

      friend class RB_tree;
    private:
      node_pointer node_;
  }; // class Iterator

  using value_type = Key;
  using reference = value_type &;
  using difference_type = std::ptrdiff_t;
  using iterator_category = std::forward_iterator_tag;
  using const_reference = const value_type &;
  using size_type = std::size_t;
  using iterator =  Iterator<false>;
  using const_iterator = Iterator<true>;
  using node_pointer = TreeNode_ *;
  using const_node_pointer = const TreeNode_ *;

  RB_tree() : root_(nullptr){ Init_n_nul(); }
  ~RB_tree() = default;

  void Insert(const value_type& key){
    node_pointer new_node = InitNode(key);
    if (!root_) {
      root_ = new_node;
      root_->color_ = BlackN;
    } else {
      node_pointer temp = FindEqData(key);
      if(temp->data_ > key){
        temp->left_ = new_node;
        new_node->parent_ = temp;
      } else {
        temp->right_ = new_node;
        new_node->parent_ = temp;
      }
      // temp.BalanceTree();
    }
    n_null_->data_++;
    n_null_->parent_ = GoRight();
  }

  void Init_n_nul(){
    n_null_ = InitNode(0);
    n_null_->color_ = BlackN;
    n_null_->left_ = n_null_;
    n_null_->right_ = n_null_;
  }

  node_pointer InitNode(const value_type& key){
    node_pointer new_node = new TreeNode_();
    new_node->left_ = n_null_;
    new_node->right_ = n_null_;
    new_node->parent_ = n_null_;
    new_node->data_ = key;
    return new_node;
  }

  node_pointer SmallLeftRotate(node_pointer node){
    node_pointer parent = node->parent_;
    node_pointer grandparent = node->parent_->parent_;
    node_pointer uncle = grandparent->left_;
    
    bool red = (node->color_ == RedN && parent->color_ == RedN && uncle == RedN);
    if(red){
      parent->left_ = grandparent;
    }
    
  }

  iterator RootIterartor(){
    iterator result (root_);
    return result;
  }

  node_pointer GoLeft(){
    node_pointer temp = const_cast<node_pointer>(root_);
    while (temp->left_  && temp->left_ != n_null_){
      temp = temp->left_;
    }
    return temp;
  }

  node_pointer GoRight(){
    node_pointer temp = const_cast<node_pointer>(root_);
    while (temp->right_ && temp->right_ != n_null_){
      temp = temp->right_;
    }
    return temp;
  }

  iterator begin(){
    node_pointer left = GoLeft();
    iterator it(left);
    return it; 
  }

  const_iterator cbegin(){
    node_pointer left = GoLeft();
    const_iterator it(left);
    return it; 
  }
  iterator end(){ return iterator(n_null_); }
  // надо чтоб возвращал ноду n_null если не нашел ноду
  iterator find(const Key& key){ 
    node_pointer node = FindEqData(key);   
    iterator find_node(node);
    iterator n_null(n_null_);
    return find_node = (node->data_ == key ? find_node : n_null);  
  }

  /// @return возвращает ноду с одинаковой датой, если не нашел - предпоследнюю 
  node_pointer FindEqData(const Key& key){
    node_pointer eq_node = root_;
    while (eq_node->data_ != key) {
      bool key_less = eq_node->data_ > key;
      if(!key_less && eq_node->right_ != n_null_) {
        eq_node = eq_node->right_;
      } else if(key_less && eq_node->left_!= n_null_) {
        eq_node = eq_node->left_;
      } else if ((!key_less && eq_node->right_ == n_null_) || (key_less && eq_node->left_ == n_null_) 
        || (eq_node->right_ == n_null_ && eq_node->left_ == n_null_)){
        break;
      }
    }
    return eq_node;
  }
  
  void PrintTree(){
    int i = 1;
    for (auto it = begin(); it != end(); it++, i++){
      std::cout << *it << ' ';
    }
    std::cout << '\n';
  }
  void PrintTreeRecursive(iterator it, int depth) const {
    node_pointer node = it.GetNodePointer();
    if (node == n_null_) return;

    // Печать правого поддерева
    iterator right(node->right_);
    PrintTreeRecursive(right, depth + 1);

    // Печать текущего узла
    std::cout << std::string(depth, ' ') << node->data_ << std::endl;

    iterator left(node->left_);
    // Печать левого поддерева
    PrintTreeRecursive(left, depth + 1);
  }
  
  void FullNodeInfo(const_iterator cit) noexcept {
    node_pointer node = const_cast<node_pointer>(cit.GetNodePointer());
    std::cout << "this:\t" << *cit << " \t" << node << " color " << node->color_ << "\n";
    if(node->parent_ /*&& node->parent_ != n_null_*/)
      std::cout << "parent:\t" << node->parent_->data_ << " \t" << node->parent_ << " color " << node->parent_->color_ << "\n";
    if(node->left_ /*&& node->left_ != n_null_*/)
      std::cout << "left:\t" << node->left_->data_ << " \t" << node->left_ << " color " << node->left_->color_ << "\n";
    if(node->right_ /*&& node->right_ != n_null_*/)
      std::cout << "right:\t" << node->right_->data_ << " \t" << node->right_ << " color " << node->right_->color_ << "\n";
  }

private:
  node_pointer root_;
  // n_null должна хранить size_t size - размер дерева
  node_pointer n_null_;

};
}; // namespace s21

#include "tree_node.tpp"
#include "s21_tree.tpp"
#endif // __S21_SET_H__
