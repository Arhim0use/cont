#include "main.h"
// #include "s21_set/s21_tree.h"



using namespace s21;

int main (){

  // test_origin();
  // test_1();
  // test_2();
  // test_3();
  // test_4();
  // test_5();
  // test_6();
  test_big_random();


  return 0;
}

void test_big_random(){
  s21::map<int, std::string> t;
  const int size_of_tree = 100;
  int random = 1000;

  random_insert(size_of_tree, random, t);
  
  std::cout<< "\n";
  t.PrintMapRecursive();
  print_s21_map(t);
  r_print_s21_map(t);
  std::cout<< "bl hight eq " << t.blHight() << "\n";
  std::cout<< "red alert " << t.redAlert();

}

void random_insert(const int size_of_tree, int random, s21::map<int, std::string> &t)
{
  for (int i = 0; i < size_of_tree; i++)
  {
    int x = rand() % random;
    t.insert(x, "");
  }
}

void test_6(){
  s21::map<int, std::string> t;
  const int size = 20;
  double arr[size] = {0};
  for(int i = 0; i < size; i++) arr[i] = 100 + i;

  t.insert( 105, "");
  t.insert( 106, "");
  t.insert( 107, "");
  t.insert( 108, "");
  t.insert( 109, "");

  t.insert( 110, "");
  t.insert( 111, "");
  t.insert( 113, "");
  t.insert( 114, "");
  t.insert( 115, "");

  t.insert( 119, "");
  t.insert( 118, "");
  t.insert( 117, "");
  t.insert( 112, "");
  t.insert( 116, "");

  t.insert( 100, "");
  t.insert( 101, "");
  t.insert( 102, "");
  t.insert( 103, "");
  t.insert( 104, "");


  t.PrintMapRecursive();
  print_s21_map(t);
  r_print_s21_map(t);
  std::cout<< "bl hight eq " << t.blHight() << "\n";
  std::cout<< "red alert " << t.redAlert();
  bool equal = true;
  auto it = t.begin();
  for(int i = 0; i < size && equal; i++, ++it) equal = arr[i] == (*it).first ;


  if(!equal) std::cout << "NOT EQUAL\n";
}

void test_5(){
  s21::map<int, std::string> t;
  const int size = 20;
  double arr[size] = {0};
  for(int i = 0; i < size; i++) arr[i] = 100 + i;

  t.insert( 110, "");
  t.insert( 111, "");
  t.insert( 112, "");
  t.insert( 113, "");
  t.insert( 114, "");
  
  t.insert( 115, "");
  t.insert( 116, "");
  t.insert( 117, "");
  t.insert( 118, "");
  t.insert( 119, "");

  t.insert( 100, "");
  t.insert( 101, "");
  t.insert( 102, "");
  t.insert( 103, "");
  t.insert( 104, "");

  t.insert( 109, "");
  t.insert( 108, "");
  t.insert( 107, "");
  t.insert( 106, "");
  t.insert( 105, "");


  t.PrintMapRecursive();
  print_s21_map(t);
  r_print_s21_map(t);
  std::cout<< "bl hight eq " << t.blHight() << "\n";
  std::cout<< "red alert " << t.redAlert();
  bool equal = true;
  auto it = t.begin();
  for(int i = 0; i < size && equal; i++, ++it) equal = arr[i] == (*it).first ;

  t.fullnodeinfo(t.find(103));
  std::cout << "\n";
  t.fullnodeinfo(t.find(104));
  std::cout << "\n";
  // t.fullnodeinfo(t.find(106));
  if(!equal) std::cout << "NOT EQUAL\n";
}


// здесь был есть баг
void test_2() {
  s21::map<int, std::string> t;

  const int size = 14;
  double arr[size] = {0};
  for(int i = -4; i < size; i++) arr[i] = 100 + i;

  t.insert( 100, "");
  t.insert( 101, "");
  t.insert( 102, "");
  t.insert( 104, "");

  t.insert( 103, "");
  t.insert( 105, "");
  t.insert( 106, "");
  t.insert( 107, "");
  t.insert( 108, "");
  t.insert( 109, "");
  t.insert( 96, "");
  t.insert( 97, "");
  t.insert( 98, "");
  t.insert( 99, "");


  // for (int i = 0; i < 105; i++){
  //   int x = rand() % 1118;

  //   t.insert(x, "");
  // }

  // t.fullnodeinfo(--(--(t.nnullIterartor())));
  auto it = t.begin();
 
// БАТЯ ОДИН НА ДВОИХ!!!
  t.fullnodeinfo(t.find(99));
    std::cout << "\n";
  t.fullnodeinfo((it = t.find(98)));
  // ++it;
    std::cout << "\n";
  t.fullnodeinfo(t.find(97));
  print_s21_map(t);
  
  bool equal = true;
  it = t.begin();
  for(int i = 0; i < size && equal; i++, ++it) equal = arr[i] == (*it).first ;

  t.PrintMapRecursive();
  std::cout<< "bl hight eq " << t.blHight() << "\n";
  std::cout<< "red alert " << t.redAlert() << "\n";
  if(!equal) std::cout << "NOT EQUAL\n";

}



void test_1(){
  s21::map<int, std::string> t;

  const int size = 9;
  double arr[size] = {0};
  for(int i = 0; i < size; i++) arr[i] = 100 + i;

  t.insert( 100, "");
  // t.insert( 104, "");

  t.insert( 170, "");
  t.insert( 160, "");
  t.insert( 120, "");
  t.insert( 180, "");
  t.insert( 150, "");
  t.insert( 190, "");
  t.insert( 130, "");
  t.insert( 110, "");
  t.insert( 155, "");
  t.insert( 157, "");


  std::cout << "\n";
  t.PrintMapRecursive();
  t.fullnodeinfo(t.find(155));
  print_s21_map(t);
  r_print_s21_map(t);
  std::cout<< "bl hight eq " << t.blHight() << "\n";
  std::cout<< "red alert " << t.redAlert() << "\n";
  // bool equal = true;
  // auto it = t.begin();
  // for(int i = 0; i < size && equal; i++, ++it) equal = arr[i] == (*it).first ;
  // if(!equal) std::cout << "NOT EQUAL\n";
}

// void test_3(){
//   RB_tree<int> a;
//   a.Insert(0);
//   // std::cout << *it << '\n';
//   for (int i = 0; i < 8; i++){
//     int x = rand() % 18;
//     if ((i % 2) == 0) x = -x;
//     std::cout << ": " << x << " ";
//     a.Insert(x);
//   }
//     std::cout << "\n" ;
//   a.PrintTree();
//     std::cout << "\n" ;
//   a.PrintTreeRecursive(a.RootIterartor(), 0);
//   // auto it = a.RootIterartor();
//   // ++it;
//   // ++it;
//   // a.FullNodeInfo(it);


//   // it = a.find(0);
//   // std::cout << *it << '\n';

// }
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


  // int zero = 0;
  // std::cout << a.size();
  // a.insert(zero - 5);
  // a.insert(zero + 1);
  // a.insert(zero + 2);
  // a.clear();
  // auto it = a.begin();
  // // it--;
  // std::cout << *it;

  // for (int i = 0; i < 15; i++){
  //   int x = rand() % 18;
  //   if ((i % 2) == 0) 
  //     x = -x;
  //   a.emplace(x);
  // }
  // print_set(a);

}


void print_set(std::set<int> &a){
  for (auto it = a.begin(); it != a.end(); ++it)
  {
    std::cout << *it << " ";
  }
}


void print_s21_map(s21::map<int, std::string> &t)
{
  for (auto i = t.begin(); i != t.end(); ++i)
  {
    std::cout << (*i).first << " ";
  }
  std::cout << "\n";
}
void r_print_s21_map(s21::map<int, std::string> &t)
{
  auto i = t.end();
  i--;
  for (; i != t.begin(); --i)
  {
    std::cout << (*i).first << " ";
  }
    std::cout << (*i).first << " ";
  std::cout << "\n";
}
