#include "main.h"




using namespace s21;

int main (){

  // test_origin();
  // test_from_testfile();
  test_0();
  test_1();
  test_2();
  test_3();
  // test_4();
  test_5();
  test_6();
  // test_s21_set_1();
  // test_copy_rbtree();
  test_big_random();


  return 0;
}

// void test_from_testfile(){
//   s21::set<int> s21_set = {1,2,0,3,4,5,6,12,13,14,17,16,7,8,11,9,10,20,19,35,31,24,29,28,15,26,31,33,32,22,23,21};

//   s21_set.PrintTreeRecursive();

//   std::cout << "\n";
//   // s21_set.PrintTreeRecursive();
//   s21_set.DeleteNode(17);

//   s21_set.FullNodeInfo(15);
//   std::cout << "\n";
//   s21_set.FullNodeInfo(16);
//   std::cout << "\n";
//   std::cout << "\n" << s21_set.RedAlert();
//   std::cout << "\n" << s21_set.BLM();
//   std::cout << "\n";

//   s21_set.PrintTreeRecursive();
// }

// void test_s21_set_1(){

//   s21::set<std::string> s21_set;
//   std::set<std::string> std_set;

//   s21_set.insert("World");
//   s21_set.insert("!");

//   if(std_set.insert("Hello").second == s21_set.insert("Hello").second) 
//     std::cout << "insert ok\n";

//   std_set.insert("World");
//   std_set.insert("!");

//   if(s21_set.size() == std_set.size())
//     std::cout << "size ok\n";
//   else
//     std::cout << std_set.size() << "|||" << s21_set.size() <<"size \n";
//   if(*std_set.find("Hello") == *s21_set.find("Hello"))
//     std::cout << "find Hello ok\n";
//   if(*std_set.find("hello") == *s21_set.find("hello"))
//     std::cout << "find hello ok\n";
//   if(*std_set.cbegin() == *s21_set.cbegin())
//     std::cout << *std_set.cbegin() << "|||" <<  *s21_set.cbegin() << "cbegin ok\n";
//   if(*std_set.cend() ==  *s21_set.cend())
//     std::cout<< *std_set.cend() << "cend ok\n";
//   else
//     std::cout << *std_set.cend() << "|||" << *s21_set.cend() <<"cend \n";


// s21_set.PrintTreeRecursive();
//   // auto s21_it_2 = s21_set.find(6);

//   // s21_it = s21_set.begin();
//   // s21_it_2 = s21_it;
//   // s21_it_2--;
//   // s21_it_2--;
//   // std::cout << *s21_it << " " << *s21_it_2;

// }

// void test_copy_rbtree(){
//   s21::set<int> t;
//   const int size = 50;
//   // // double arr[size] = {0};
//   for(int i = 0; i < size; i++) t.insert(i);


//   t.PrintTreeRecursive();


// std::cout<< "\n" << "black h eq =" <<t.BLM();
// std::cout<< "\n" << "Red Al  =" <<t.RedAlert();
  
// }
void random_insert(const int insert_count, int random, s21::set<int> &s21_s){
  for (int i = 0; i < insert_count; i++){
    int x = rand() % random;
    s21_s.insert(x);
  }
}
void test_big_random(){
  s21::set<int> t;
  const int size_of_tree = 50;
  int random = 1000;

  random_insert(size_of_tree, random, t);
  
  // t.PrintTreeRecursive();
  std::cout<< "\n";
  std::cout<< "bl hight eq " << t.BLM() << "\n";
  std::cout<< "red alert " << t.RedAlert();

}

// void random_insert(const int size_of_tree, int random, s21::map<int, std::string> &t)
// {
//   for (int i = 0; i < size_of_tree; i++)
//   {
//     int x = rand() % random;
//     t.insert(x, "");
//   }
// }
 
void test_0(){
  s21::set<int> t;

  std::cout<< "ПУСТОЕ ДЕРЕВО bl hight eq " << t.BLM() << "\n";


}
void test_6(){
  s21::set<int> t;
  const int size = 20;
  double arr[size] = {0};
  for(int i = 0; i < size; i++) arr[i] = 100 + i;

  t.insert( 105);
  t.insert( 106);
  t.insert( 107);
  t.insert( 108);
  t.insert( 109);

  t.insert( 110);
  t.insert( 111);
  t.insert( 113);
  t.insert( 114);
  t.insert( 115);

  t.insert( 119);
  t.insert( 118);
  t.insert( 117);
  t.insert( 112);
  t.insert( 116);

  t.insert( 100);
  t.insert( 101);
  t.insert( 102);
  t.insert( 103);
  t.insert( 104);


  // t.PrintTreeRecursive();
  // print_s21_map(t);
  // r_print_s21_map(t);
  std::cout<< "bl hight eq " << t.BLM() << "\n";
  std::cout<< "red alert " << t.RedAlert();
  bool equal = true;
  auto it = t.begin();
  for(int i = 0; i < size && equal; i++, ++it) equal = arr[i] == (*it) ;


  if(!equal) std::cout << "NOT EQUAL\n";
}
 
void test_5(){
  s21::set<int> t;
  const int size = 20;
  double arr[size] = {0};
  for(int i = 0; i < size; i++) arr[i] = 100 + i;

  t.insert( 110);
  t.insert( 111);
  t.insert( 112);
  t.insert( 113);
  t.insert( 114);
  
  t.insert( 115);
  t.insert( 116);
  t.insert( 117);
  t.insert( 118);
  t.insert( 119);

  t.insert( 100);
  t.insert( 101);
  t.insert( 102);
  t.insert( 103);
  t.insert( 104);

  t.insert( 109);
  t.insert( 108);
  t.insert( 107);
  t.insert( 106);
  t.insert( 105);


  // t.PrintTreeRecursive();
  // print_s21_map(t);
  // r_print_s21_map(t);
  std::cout<< "bl hight eq " << t.BLM() << "\n";
  std::cout<< "red alert " << t.RedAlert() << "\n";
  bool equal = true;
  auto it = t.begin();
  for(int i = 0; i < size && equal; i++, ++it) equal = arr[i] == (*it) ;

  // t.fullnodeinfo(t.find(103));
  // std::cout << "\n";
  // t.fullnodeinfo(t.find(104));
  // std::cout << "\n";
  // t.fullnodeinfo(t.find(106));
  if(!equal) std::cout << "NOT EQUAL\n";
} 


void test_2() {
  s21::set<int> t;

  const size_t size = 14;
  double arr[size] = {0};
  for(size_t i = -4; i < size; i++) arr[i] = 100 + i;

  t.insert( 100);
  t.insert( 101);
  t.insert( 102);
  t.insert( 104);

  t.insert( 103);
  t.insert( 105);
  t.insert( 106);
  t.insert( 107);
  t.insert( 108);
  t.insert( 109);
  t.insert( 96);
  t.insert( 97);
  t.insert( 98);
  t.insert( 99);


  // t.fullnodeinfo(--(--(t.nnullIterartor())));
  auto it = t.begin();
 
// БАТЯ ОДИН НА ДВОИХ!!!
  // t.fullnodeinfo(t.find(99));
  //   std::cout << "\n";
  // t.fullnodeinfo((it = t.find(98)));
  // // ++it;
  //   std::cout << "\n";
  // t.fullnodeinfo(t.find(97));
  // print_s21_map(t);
  
  bool equal = true;
  it = t.begin();
  for(size_t i = 0; i < t.size() && equal; i++, ++it) {
    equal = t.contains(arr[i]) ;
    equal = t.size() == size;
  }
  // t.PrintTreeRecursive();
  std::cout<< "bl hight eq " << t.BLM() << "\n";
  std::cout<< "red alert " << t.RedAlert() << "\n";
  if(!equal) std::cout << "NOT EQUAL\n";

}

void test_1(){
  s21::set<int> t;

  // const size_t size = 9;
  // double arr[size] = {0};
  // for(size_t i = 0; i < size; i++) arr[i] = 100 + i;

  t.insert( 100);
  // t.insert( 104, "");

  t.insert( 170);
  t.insert( 160);
  t.insert( 120);
  t.insert( 180);
  t.insert( 150);
  t.insert( 190);
  t.insert( 130);
  t.insert( 110);
  t.insert( 155);
  t.insert( 157);


  std::cout << "\n";
  // t.PrintTreeRecursive();
  // t.fullnodeinfo(t.find(155));
  // print_s21_map(t);
  // r_print_s21_map(t);
  std::cout<< "bl hight eq " << t.BLM() << "\n";
  std::cout<< "red alert " << t.RedAlert() << "\n";
  // bool equal = true;
  // auto it = t.begin();
  // for(int i = 0; i < size && equal; i++, ++it) equal = arr[i] == (*it).first ;
  // if(!equal) std::cout << "NOT EQUAL\n";
}

void test_3(){
  s21::set<size_t> t;

  const size_t size = 75;
  for(size_t i = 0; i < size; i++) t.insert( i);


  std::cout << "\n";
  // t.PrintTreeRecursive();
  // t.fullnodeinfo(t.find(155));
  // print_s21_map(t);
  // r_print_s21_map(t);
  std::cout<< "bl hight eq " << t.BLM() << "\n";
  std::cout<< "red alert " << t.RedAlert() << "\n";
} 
void test_origin (){
  // std::set<int> a;
  std::set<int> t;

  if(1){
    t.insert( 8);
    t.insert( 2);
    t.insert( 7);

    // // малый левый поворот
    // t.insert( 2, "");
    // t.insert( 8, "");
    // t.insert( 7, "");
    // t.fullnodeinfo(--(--(t.nnullIterartor())));
    auto it = t.begin();
    auto data = *it;
    std::cout<< data << "\n";
    ++it;
    std::cout<< (*it) << "\n";
    ++it;
    std::cout<< (*it) << "\n";
    ++it;
    std::cout<< (*it) << "\n";
    // t.fullnodeinfo(it);
  }
}


void print_set(std::set<int> &a){
  for (auto it = a.begin(); it != a.end(); ++it)
  {
    std::cout << *it << " ";
  }
}


// void print_s21_map(s21::map<int, std::string> &t)
// {
//   for (auto i = t.begin(); i != t.end(); ++i)
//   {
//     std::cout << (*i).first << " ";
//   }
//   std::cout << "\n";
// }
// void r_print_s21_map(s21::map<int, std::string> &t)
// {
//   auto i = t.end();
//   i--;
//   for (; i != t.begin(); --i)
//   {
//     std::cout << (*i).first << " ";
//   }
//     std::cout << (*i).first << " ";
//   std::cout << "\n";
// }

void set_print(s21::set<int> &s)
{
  for (auto it = s.begin(); it != s.end(); ++it)
  {
    std::cout << (*it) << " ";
  }
}