

namespace s21{
template<typename Key_T, typename Value_T>
class RB_tree
{
    //* Эти переопределения using помогают в создании гибкого итератора, 
    //* который может быть использован в стандартных контейнерах 
    //* STL и других контекстах, ожидая совместимость с интерфейсом STL.
    using value_type = Value_T;
    using key_type = Key_T;
    using reference = value_type &;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;
    using const_reference = const value_type &;
    using size_type = std::size_t;
    using iterator = iterator<Key_T, Value_T, false>;
    using const_iterator = iterator<Key_T, Value_T, true>;
  public:
    RB_tree(/* args */);
    ~RB_tree();
    iterator begin();
    iterator end(){ return nullptr; }
    iterator find(const Key& key);


  private:
    template<typename Key_T, typename Value_T,  bool Const>
    class iterator;
}; // class RB_tree

template<typename Key_T, typename Value_T,  bool Const>
class iterator{
  enum NodeColor { RedN, BlackN };
  struct TreeNode_;

  using value_type = Value_T;
  using key_type = Key_T;
  //* Если Const равно true, то это будет указатель на константный узел 
  //* (const list_node *), иначе - указатель на изменяемый узел (list_node *).
  // using node_ = std::conditional_t<Const, const TreeNode_ , TreeNode_>;
  using node_pointer = std::conditional_t<Const, const TreeNode_ *, TreeNode_ *>;
  using pointer = std::conditional_t<Const, const Value_T *, Value_T *>;
  using reference = std::conditional_t<Const, const Value_T &, Value_T &>;

public:
  iterator() = delete;
  explicit iterator(node_pointer node) : node_(node) {}
  ~iterator() = default;

  iterator& operator++(){
    nextNode();
    return *this;
  }
  iterator operator++(int);
  iterator& operator--();
  iterator operator--(int);
  reference operator*() { return data_; }
  bool operator==(const iterator& other) { return node_ == other.node_; }
  bool operator!=(const iterator& other) { return node_ == other.node_; }

private:
  node_pointer node_;
  struct TreeNode_{
    value_type data_ = data();
    Key_T key_ = key();

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
    
    node_pointer nextNode() const noexcept {
      TreeNode_ *result = (*this);
      if (right_){
        result = right_;
        for (;result->left_; result = left_);
      } else if (!right_ && parent_){
         result = 
      } else if (parent_ == nullptr && right_ == nullptr){
        result = nullptr;
      }
      return result;
    }
    node_pointer prevNode(){

    }
  }

}; // class iterator
} // namespace s21


template<typename Key_T, typename Value_T,  bool Const>
typename s21::iterator<Key_T, Value_T, Const>&
s21::iterator<Key_T, Value_T, Const>::operator++(){
  nextNode();
  return *this;
}

      // iterator operator++(int);
      // iterator& operator--();
      // iterator operator--(int);


// template <typename T, bool Const>
// class StackIterator;

// template <typename T>
// class stack;

// template <typename T, bool Const>
// class StackIterator {
//   friend class stack;
//   struct StackNode_;
//   //* Эти переопределения using помогают в создании гибкого итератора, 
//   //* который может быть использован в стандартных контейнерах 
//   //* STL и других контекстах, ожидая совместимость с интерфейсом STL.
//   using iterator = StackIterator;
//   //* Если Const равно true, то это будет указатель на константный узел 
//   //* (const list_node *), иначе - указатель на изменяемый узел (list_node *).
//   using node_pointer = std::conditional_t<Const, const StackNode_ *, StackNode_ *>;
//   using difference_type = std::ptrdiff_t;
//   using value_type = T;
//   using pointer = std::conditional_t<Const, const T *, T *>;
//   using reference = std::conditional_t<Const, const T &, T &>;
//   using iterator_category = std::forward_iterator_tag;

//   public:
//     iterator() = delete;
//     explicit iterator(node_pointer node) : node_(node){}
//     ~iterator() = default;
    
//     reference operator*() noexcept const { return node_->data_; }








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
