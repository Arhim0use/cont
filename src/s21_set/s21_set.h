#ifndef __S21_SET_H__
#define __S21_SET_H__

#include "s21_tree.h"

namespace s21 {
template<typename Key>
class set
{
  struct TreeNode;
  using key_type = Key; 
  using value_type = key_type;
  using reference = value_type &;
  using difference_type = std::ptrdiff_t;
  using iterator_category = std::forward_iterator_tag;
  using const_reference = const reference;
  using size_type = std::size_t;
  //* Если Const равно true, то это будет указатель на константный узел 
  //* (const list_node *), иначе - указатель на изменяемый узел (list_node *).
  // using node_ = std::conditional_t<Const, const TreeNode_ , TreeNode_>;
  using iterator = iterator<value_type, false>; // ?
  using const_iterator = iterator<value_type, true>; // ?

// | `iterator`               | internal class `SetIterator<T>` or `BinaryTree::iterator` as the internal iterator of tree subclass;
//  defines the type for iterating through the container|
// | `const_iterator`         | internal class `SetConstIterator<T>` or `BinaryTree::const_iterator` as the internal const iterator of tree subclass;
// defines the constant type for iterating through the container|

public:
  set();
  set(std::initializer_list<value_type> const &items);
  set(const set &s);
  set(set &&s);
  ~set();
  operator=(set &&s);

  bool empty();
  size_type size();
  size_type max_size();

  void clear();
  std::pair<iterator, bool> insert(const value_type& value);
  void erase(iterator pos);
  void swap(set& other);
  void merge(set& other);
  iterator begin();
  iterator end(){ return nullptr; }
  iterator find(const Key& key);
  bool contains(const Key& key);
private:
    template<value_type>
    TreeNode_* node_;
}; // class set
} // namespace s21

#endif // __S21_SET_H__




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
