
#include "s21_tree.h"

// namespace s21{





// }; // namespace s21


// template<typename T>
// void s21::RB_tree<T>::PrintTree(){
//   Iterator<false> it(GoLeft());
//   for (int i = 0; it != nullptr; ++it, i++){
//     std::cout << *it << ' ';
//     if(!(i % 5)) std::cout << '\n';
//   }
// }


// | Member type            | Definition                                                                             |
// |------------------------|----------------------------------------------------------------------------------------|
// | `key_type`               | `Key` the first template parameter (Key)                                                     |
// | `value_type`             | `Key` value type (the value itself is a key)                                                    |
// | `reference`              | `value_type &` defines the type of the reference to an element                                                             |
// | `const_reference`        | `const value_type &` defines the type of the constant reference                                         |
// | `iterator`               | internal class `SetIterator<T>` or `BinaryTree::iterator` as the internal iterator of tree subclass; defines the type for iterating through the container                                                 |
// | `const_iterator`         | internal class `SetConstIterator<T>` or `BinaryTree::const_iterator` as the internal const iterator of tree subclass; defines the constant type for iterating through the container                                           |
// | `size_type`              | `size_t` defines the type of the container size (standard type is size_t) |
