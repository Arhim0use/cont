#include <set>
#include <algorithm>

#include <gtest/gtest.h>

#include "../s21_set/s21_set.h"

void random_insert(const int insert_count, int random, s21::set<int> &s21_s, std::set<int> &std_s){
  for (int i = 0; i < insert_count; i++){
    int x = rand() % random;
    s21_s.insert(x);
    std_s.insert(x);
  }
}

TEST(S21_SET, Constructor) {
  s21::set<int> s21_set;
  std::set<int> std_set;
  EXPECT_EQ(s21_set.empty(), std_set.empty());
  EXPECT_EQ(s21_set.size(), std_set.size());
}

TEST(S21_SET, Constructor_initializer_list) {
  s21::set<int> s21_set = {0, 5, 10, 15, 20};
  std::set<int> std_set;
  for(int i = 0; i <= 20; i += 5 ) std_set.insert(i);

  EXPECT_EQ(s21_set.empty(), std_set.empty());
  EXPECT_EQ(s21_set.size(), std_set.size());
  auto s21 = *(s21_set.begin());
  auto std = *(std_set.begin());
  EXPECT_EQ(s21, std);
}

// TEST(S21_SET, Constructor_copy) {
//   s21::set<int> s21_set = {0, 5, 10, 15};
//   s21::set<int> s21_set_copy(s21_set);
//   std::set<int> std_set;
//   for(int i = 0; i <= 15; i += 5 ) std_set.insert(i);
//   std::set<int> std_set_copy(std_set);

//   EXPECT_EQ(s21_set.empty(), std_set.empty());
//   EXPECT_EQ(s21_set.size(), std_set.size());
//   EXPECT_EQ(*s21_set.begin(), *std_set.begin());  

//   EXPECT_EQ(s21_set_copy.empty(), std_set_copy.empty());
//   EXPECT_EQ(s21_set_copy.size(), std_set_copy.size());
//   EXPECT_EQ(*(s21_set_copy.begin()), *(std_set_copy.begin()));
// }

TEST(S21_SET, Constructor_move) {
  s21::set<int> s21_set = {0, 5, 10, 15};
  s21::set<int> s21_set_move(std::move(s21_set));
  std::set<int> std_set;
  for(int i = 0; i <= 15; i += 5 ) std_set.insert(i);
  std::set<int> std_set_move(std::move(std_set));

  EXPECT_EQ(s21_set.empty(), std_set.empty());
  EXPECT_EQ(s21_set.size(), std_set.size());

  EXPECT_EQ(s21_set_move.empty(), std_set_move.empty());
  EXPECT_EQ(s21_set_move.size(), std_set_move.size());
  EXPECT_EQ(*(s21_set_move.begin()), *(std_set_move.begin()));
}

// TEST(S21_SET, Operator_copy) {
//   s21::set<int> s21_set = {0, 5, 10, 15};
  // s21::set<int> s21_set_cp = {0, -5, -10, -15, 5}; 

//   s21_set_cp = s21_set;

//   EXPECT_EQ(s21_set.size(), s21_set_cp.size());

//   for(auto s21_it_2 = s21_set_cp.begin(), s21_it = s21_set.begin();
//                    s21_it != s21_set.end(); s21_it++, s21_it_2++){
//     EXPECT_EQ(*s21_it, *s21_it_2);
//   }
//   EXPECT_FALSE(*s21_set_cp.contains(-10));
// }

TEST(S21_SET, Operator_move) {
  s21::set<int> s21_set = {0, 5, 10, 15};
  s21::set<int> s21_set_move;

  EXPECT_TRUE(s21_set_move.empty());

  s21_set_move = std::move(s21_set);

  EXPECT_TRUE(s21_set.empty());
  EXPECT_EQ(*s21_set_move.begin(), 0);
}

TEST(S21_SET, insert) {
  s21::set<int> s21_set;
  std::set<int> std_set;
  for(int i = 0; i <= 20; i += 5 ) {
    EXPECT_EQ(std_set.insert(i).second, s21_set.insert(i).second);
  }
  EXPECT_EQ(s21_set.empty(), std_set.empty());
  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_EQ(*(s21_set.begin()), *(std_set.begin()));
  EXPECT_TRUE(s21_set.BLM());
  EXPECT_FALSE(s21_set.RedAlert());
}

TEST(S21_SET, insert_5000_random) {
  s21::set<int> s21_set;
  std::set<int> std_set;
  random_insert(5000, 100099, s21_set, std_set);
  EXPECT_EQ(s21_set.empty(), std_set.empty());
  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_EQ(*(s21_set.begin()), *(std_set.begin()));
  EXPECT_TRUE(s21_set.BLM());
  EXPECT_FALSE(s21_set.RedAlert());
}

TEST(S21_SET, insert_many) {
  s21::set<int> s21_set;
  std::set<int> std_set;
  for(int i = 0; i <= 8; i++) {
    std_set.insert(i);
  }
  auto vector = s21_set.insert_many(2,1,3,5,6,4,8,7,8,0);
  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_EQ(*(s21_set.begin()), *(std_set.begin()));
  EXPECT_TRUE(s21_set.BLM());
  EXPECT_FALSE(s21_set.RedAlert());
}

// TEST(S21_SET, erase_easy) {
//   std::vector<int> vector {1,2,0,5,6,-1,-2, 0};
//   s21::set<int> s21_set;
//   std::set<int> std_set;
//   for(size_t i = 0; i <= vector.size(); i++) {
//     EXPECT_EQ(std_set.insert(vector[i]).second, s21_set.insert(vector[i]).second);
//   }
//   std_set.erase(5);
//   s21_set.erase(5);

//   EXPECT_TRUE(s21_set.size() == std_set.size());
//   EXPECT_TRUE(s21_set.contains(6));
//   EXPECT_TRUE(s21_set.BLM());
//   EXPECT_FALSE(s21_set.RedAlert());

//   s21_set.erase(6);
//   EXPECT_TRUE(s21_set.BLM());
//   EXPECT_FALSE(s21_set.RedAlert());
// }

// TEST(S21_SET, erase_hard) {
//   std::vector<int> vector {1,2,0,3,4,5,6,12,13,14,17,16,7,8,11,9,10,20,19,35,31,24,29,28,15,26,31,33,32,22,23,21};
//   s21::set<int> s21_set;
//   std::set<int> std_set;
//   for(size_t i = 0; i <= vector.size(); i++) {
//     EXPECT_EQ(std_set.insert(vector[i]).second, s21_set.insert(vector[i]).second);
//   }
//   std_set.erase(17);
//   s21_set.erase(17);
//   // auto s21_it = s21_set.begin();
//   // for(auto std_it = std_set.begin(); std_it != std_set.end(); ++std_it, ++s21_it) {
//   //   EXPECT_EQ(*s21_it, *std_it);
//   // }

//   EXPECT_TRUE(s21_set.size() == std_set.size());
//   EXPECT_TRUE(s21_set.contains(15));
//   EXPECT_TRUE(s21_set.BLM());
//   EXPECT_FALSE(s21_set.RedAlert());
// }

TEST(S21_SET, clear) {
  s21::set<int> s21_set = {0, 5, 10, 15};

  EXPECT_FALSE(s21_set.empty());

  s21_set.clear();

  EXPECT_TRUE(s21_set.empty());

  s21_set.insert(8);
  EXPECT_EQ(*s21_set.begin(), 8);
}

TEST(S21_SET, find_and_iterator_1) {
  s21::set<int> s21_set;
  std::set<int> std_set;
  for(int i = 0, j = 0; i <= 55; i++, j = i ) {
    if((i % 2) == 0) j = -j;
    std_set.insert(j);
    s21_set.insert(j);
  }

  EXPECT_EQ(s21_set.empty(), std_set.empty());
  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_TRUE(s21_set.BLM());
  EXPECT_FALSE(s21_set.RedAlert());

  auto std_it = std_set.find(41);
  auto s21_it = s21_set.find(41);
  EXPECT_EQ(*(s21_it), *(std_it));
  --s21_it;
  --std_it;
  EXPECT_EQ(*(s21_it), *(std_it));
  EXPECT_EQ(s21_set.find(-41), s21_set.end());
}

TEST(S21_SET, find_and_iterator_2) {
  s21::set<int> s21_set;
  std::set<int> std_set;
  for(int i = 0, j = 0; i <= 55; i++, j = i ) {
    if((i % 2) == 0) j = -j;
    std_set.insert(j);
    s21_set.insert(j);
  }

  EXPECT_EQ(s21_set.empty(), std_set.empty());
  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_TRUE(s21_set.BLM());
  EXPECT_FALSE(s21_set.RedAlert());

  auto std_it = std_set.find(41);
  auto s21_it = s21_set.find(41);
  EXPECT_EQ(*(s21_it), *(std_it));
  ++s21_it;
  ++std_it;
  EXPECT_EQ(*(s21_it), *(std_it));
  EXPECT_EQ(s21_set.find(-41), s21_set.end());
}

TEST(S21_SET, iterator_plus) {
  s21::set<int> s21_set;
  std::set<int> std_set;
  for(int i = 0, j = 0; i <= 11; i++, j = i ) {
    if((i % 2) == 0) j = -j;
    std_set.insert(j);
    s21_set.insert(j);
  }

  EXPECT_EQ(s21_set.size(), std_set.size());
  auto s21_it = s21_set.begin();
  auto s21_it_2 = s21_set.begin();
  EXPECT_TRUE(s21_it == s21_it_2);
  for(auto std_it = std_set.begin(); s21_it != s21_set.end(); s21_it++, std_it++){
    EXPECT_EQ(*s21_it, *std_it);
  }
}

TEST(S21_SET, iterator_minus) {
  s21::set<int> s21_set;
  std::set<int> std_set;
  for(int i = 0, j = 0; i <= 11; i++, j = i ) {
    std_set.insert(j);
    s21_set.insert(j);
  }

  EXPECT_EQ(s21_set.size(), std_set.size());
  auto s21_it = s21_set.find(4);
  auto s21_it_2 = s21_set.find(6);
  s21_it_2--;
  s21_it_2--;
  EXPECT_TRUE(s21_it == s21_it_2);

  s21_it = s21_set.begin();
  s21_it_2 = s21_it;
  s21_it_2--;
  EXPECT_EQ(s21_set.end(), s21_it_2);
}

TEST(S21_SET, conteins_true) {
  s21::set<int> s21_set;
  std::set<int> std_set;
  for(int i = 0, j = 0; i <= 55; i++, j = i ) {
    if((i % 2) == 0) j = -j;
    std_set.insert(j);
    s21_set.insert(j);
  }

  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_TRUE(s21_set.BLM());
  EXPECT_FALSE(s21_set.RedAlert());

  EXPECT_TRUE(s21_set.contains(-40));
  EXPECT_TRUE(s21_set.contains(41));
}

TEST(S21_SET, conteins_false) {
  s21::set<int> s21_set;
  std::set<int> std_set;
  for(int i = 0, j = 0; i <= 55; i++, j = i ) {
    if((i % 2) == 0) j = -j;
    std_set.insert(j);
    s21_set.insert(j);
  }

  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_TRUE(s21_set.BLM());
  EXPECT_FALSE(s21_set.RedAlert());

  EXPECT_FALSE(s21_set.contains(40));
  EXPECT_FALSE(s21_set.contains(-41));
}

TEST(S21_SET, swap) {
  s21::set<int> s21_set = {0, 5, 10, 15};
  s21::set<int> s21_set_2 = {0, -5, -10, -15, 5};

  s21_set_2.swap(s21_set);

  EXPECT_FALSE(s21_set_2.contains(-10));
  EXPECT_TRUE(s21_set.contains(-10));
  EXPECT_TRUE(s21_set_2.contains(10));
}

TEST(S21_SET, merge_different_trees) {
  s21::set<int> s21_set_1;
  s21::set<int> s21_set_2;
  int size = 54;
  for(int i = 0, j = 0; i < size; i++, j = i ) {
    if((i % 2) == 1) s21_set_1.insert(j);
    else s21_set_2.insert(j);
  }
  EXPECT_EQ(s21_set_1.size(), s21_set_2.size());
  EXPECT_EQ(s21_set_1.size(), size / 2);
  EXPECT_TRUE(s21_set_1.BLM());
  EXPECT_FALSE(s21_set_1.RedAlert());
  EXPECT_TRUE(s21_set_2.BLM());
  EXPECT_FALSE(s21_set_2.RedAlert());

  EXPECT_FALSE(s21_set_1.contains(40));
  EXPECT_TRUE(s21_set_1.contains(41));
  EXPECT_FALSE(s21_set_2.contains(41));

  s21_set_2.merge(s21_set_1);

  EXPECT_EQ(s21_set_2.size(), size);
  EXPECT_TRUE(s21_set_2.contains(41));
  EXPECT_TRUE(s21_set_2.BLM());
  EXPECT_FALSE(s21_set_2.RedAlert());
}

TEST(S21_SET, merge_same_tree) {
  s21::set<int> s21_set_1;
  s21::set<int> s21_set_2;
  size_t size = 10;
  for(size_t i = 0, j = 0; i < size; i++, j = i ) {
    s21_set_1.insert(j);
    s21_set_2.insert(j);
  }

  EXPECT_EQ(s21_set_1.size(), s21_set_2.size());
  EXPECT_EQ(s21_set_1.size(), size);
  EXPECT_TRUE(s21_set_1.BLM());
  EXPECT_FALSE(s21_set_1.RedAlert());
  EXPECT_TRUE(s21_set_2.BLM());
  EXPECT_FALSE(s21_set_2.RedAlert());

  EXPECT_TRUE(s21_set_1.contains(0));
  EXPECT_TRUE(s21_set_1.contains(9));
  EXPECT_TRUE(s21_set_2.contains(0));
  EXPECT_TRUE(s21_set_2.contains(9));

  s21_set_2.merge(s21_set_1);

  EXPECT_FALSE(s21_set_2.size() == (size * 2));
  EXPECT_TRUE(s21_set_2.size() == size);
  EXPECT_TRUE(s21_set_2.BLM());
  EXPECT_FALSE(s21_set_2.RedAlert());
}

TEST(S21_SET, merge_self) {
  s21::set<int> s21_set_1;
  size_t size = 10;
  for(size_t i = 0, j = 0; i < size; i++, j = i ) {
    s21_set_1.insert(j);
  }

  s21_set_1.merge(s21_set_1);

  EXPECT_TRUE(s21_set_1.size() == size);
  EXPECT_TRUE(s21_set_1.BLM());
  EXPECT_FALSE(s21_set_1.RedAlert());
}

TEST(S21_SET, merge_partially_different_trees) {
  s21::set<int> s21_set_1;
  s21::set<int> s21_set_2;
  size_t size = 10;
  for(size_t i = 0, j = 0; i < size; i++, j = i ) {
    s21_set_1.insert(j);
    s21_set_2.insert(j);
  }

  s21_set_1.insert(100);
  s21_set_1.insert(-100);

  EXPECT_EQ(s21_set_1.size(), size + 2);
  EXPECT_FALSE(s21_set_2.size() == s21_set_1.size());

  EXPECT_TRUE(s21_set_1.contains(100));
  EXPECT_TRUE(s21_set_1.contains(-100));
  
  EXPECT_FALSE(s21_set_2.contains(100));
  EXPECT_FALSE(s21_set_2.contains(-100));

  s21_set_2.merge(s21_set_1);

  EXPECT_TRUE(s21_set_2.contains(100));
  EXPECT_TRUE(s21_set_2.contains(-100));
  EXPECT_TRUE(s21_set_2.size() == s21_set_1.size());
  EXPECT_TRUE(s21_set_2.BLM());
  EXPECT_FALSE(s21_set_2.RedAlert());
}

TEST(S21_SET, string_test) {
  s21::set<std::string> s21_set;
  std::set<std::string> std_set;

  s21_set.insert("World");
  s21_set.insert("!");

  EXPECT_EQ(std_set.insert("Hello").second, s21_set.insert("Hello").second);

  std_set.insert("World");
  std_set.insert("!");

  EXPECT_TRUE(s21_set.size() == std_set.size());
  EXPECT_EQ(*std_set.find("Hello"), *s21_set.find("Hello"));
  EXPECT_EQ(*std_set.find("hello"), *s21_set.find("hello"));
  EXPECT_EQ(*std_set.cbegin(), *s21_set.cbegin());
  EXPECT_EQ(*std_set.cend(), *s21_set.cend());

}













int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}