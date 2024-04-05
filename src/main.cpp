#include "s21_containers.h"

int main (){

    s21::map<int, int> m1 {{1,1},{2,2},{2,2}};
    s21::map<int, int> m2(m1);

    if (m2 == m1) std::cout << "hello";

}