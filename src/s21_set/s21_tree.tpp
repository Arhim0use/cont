

namespace s21{
template<typename Key, typename T>
class RB_tree
{
  struct TreeNode_;
    //* Эти переопределения using помогают в создании гибкого итератора, 
    //* который может быть использован в стандартных контейнерах 
    //* STL и других контекстах, ожидая совместимость с интерфейсом STL.
    using mapped_type = T;
    using key_type = Key;
    using value_type = std::pair<const key_type,mapped_type>;
    using reference = value_type &;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;
    using const_reference = const value_type &;
    using size_type = std::size_t;
    using iterator = iterator<Key, T, false>;
    using const_iterator = iterator<Key, T, true>;
  public:
    RB_tree(/* args */);
    ~RB_tree();
    iterator begin();
    iterator end(){ return nullptr; }
    iterator find(const Key& key);


  private:
    template<Key, T>
    TreeNode_* node_;
}; // class RB_tree

template<bool Const>
class iterator{
  struct TreeNode_;

  //* Если Const равно true, то это будет указатель на константный узел 
  //* (const list_node *), иначе - указатель на изменяемый узел (list_node *).
  // using node_ = std::conditional_t<Const, const TreeNode_ , TreeNode_>;
  using node_pointer = std::conditional_t<Const, const TreeNode_ *, TreeNode_ *>;
public:
  iterator() = delete;
  explicit iterator(node_pointer node) : node_(node) {}
  ~iterator() = default;

  iterator& operator++();
  iterator operator++(int);
  iterator& operator--();
  iterator operator--(int);
  reference operator*() { return node_->data_; }
  bool operator==(const iterator& other) { return node_ == other.node_; }
  bool operator!=(const iterator& other) { return node_ != other.node_; }

private:
  node_pointer node_;
}; // class iterator

template<typename Key, typename T>
struct TreeNode_{
  enum NodeColor { RedN, BlackN };
  using mapped_type = T;
  using key_type = Key;
  using value_type = std::pair<const key_type, mapped_type>;
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
} // namespace s21


template<bool Const>
typename s21::iterator<Const>&
s21::iterator<Const>::operator++(){
  node_ = node_->NextNode();
  return *this;
}

template<bool Const>
typename s21::iterator<Const>
s21::iterator<Const>::operator++(int){
  iterator temp = (*this);
  ++(*this);
  return temp;
}

template<bool Const>
typename s21::iterator<Const>&
s21::iterator<Const>::operator--(){
  node_ = node_->PrevNode();
  return *this;
}

template<bool Const>
typename s21::iterator<Const>&
s21::iterator<Const>::operator--(){
  iterator temp = (*this);
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

// *Set Member functions*

// В этой таблице перечислены основные публичные методы для взаимодействия с классом:

// | Member functions      | Definition                                      |
// |----------------|-------------------------------------------------|
// | `set()`  | default constructor, creates empty set                                 |
// | `set(std::initializer_list<value_type> const &items)`  | initializer list constructor, creates the set initizialized using std::initializer_list<T>    |
// | `set(const set &s)`  | copy constructor  |
// | `set(set &&s)`  | move constructor  |
// | `~set()`  | destructor  |
// | `operator=(set &&s)`      | assignment operator overload for moving object                                |


// *Set Iterators*

// В этой таблице перечислены публичные методы для итерирования по элементам класса (доступ к итераторам):

// | Iterators              | Definition                                                                             |
// |------------------------|----------------------------------------------------------------------------------------|
// | `iterator begin()`            | returns an iterator to the beginning                                                   |
// | `iterator end()`                | returns an iterator to the end                                                         |


// *Set Capacity*

// В этой таблице перечислены публичные методы для доступа к информации о наполнении контейнера:

// | Capacity       | Definition                                      |
// |----------------|-------------------------------------------------|
// | `bool empty()`          | checks whether the container is empty           |
// | `size_type size()`           | returns the number of elements                  |
// | `size_type max_size()`       | returns the maximum possible number of elements |

// *Set Modifiers*

// В этой таблице перечислены публичные методы для изменения контейнера:

// | Modifiers              | Definition                                                                             |
// |------------------------|----------------------------------------------------------------------------------------|
// | `void clear()`                  | clears the contents                                                                    |
// | `std::pair<iterator, bool> insert(const value_type& value)`                 | inserts node and returns iterator to where the element is in the container and bool denoting whether the insertion took place                                        |
// | `void erase(iterator pos)`                  | erases element at pos                                                                        |
// | `void swap(set& other)`                   | swaps the contents                                                                     |
// | `void merge(set& other);`                  | splices nodes from another container                                                   |

// *Set Lookup*

// В этой таблице перечислены публичные методы, осуществляющие просмотр контейнера:

// | Lookup                 | Definition                                                                             |
// |------------------------|----------------------------------------------------------------------------------------|
// | `iterator find(const Key& key)`                   | finds element with specific key                                                        |
// | `bool contains(const Key& key)`               | checks if the container contains element with specific key                             |
