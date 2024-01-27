#include <iostream>
#include <list>
#include <stack>

#include "s21_stack.h"
// #include "../../../CPP1_s21_matrixplus-1/src/s21_matrix_oop.h"

int main() {
  std::stack<int> stk, stk2;
  s21::stack<int> s21stk, s21stk2;
  // S21Matrix A(2, 2);
  // int A = 10;

  try
  {
    s21stk.push(5);
    s21stk.push(2);
    s21stk.push(56);
    s21stk.push(87);
    // // while (!s21stk.empty())
    // // {
    // //  s21stk.pop();
    // // }
    s21stk.push(87);
    //  s21stk.pop();
     s21stk.pop();
     s21stk.pop();
    // s21stk.push(87);
    s21stk.emplace(100); 
    int a = s21stk.top();
    int x = s21stk.size();
    
    s21stk2 = std::move(s21stk);
    a = s21stk2.top();

    std::cout << x << ' ' << a << " | " << s21stk.empty() << ' ';
  }
  catch(const std::exception& e)
  {
    std::cout << "e.what()" << '\n';
  }

  return 0;
}
