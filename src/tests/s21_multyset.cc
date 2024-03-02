#include <multiset>

#include <gtest/gtest.h>

#include "../s21_multiset/s21_multiset.h"

void random_insert(const int insert_count, int random, s21::multiset<int> &s21_s, std::multiset<int> &std_s){
  for (int i = 0; i < insert_count; i++){
    int x = rand() % random;
    s21_s.insert(x);
    std_s.insert(x);
  }
}

TEST(S21_multiset, Constructor) {
  s21::multiset<int> s21_multiset;
  std::multiset<int> std_multiset;
  EXPECT_EQ(s21_multiset.empty(), std_multiset.empty());
  EXPECT_EQ(s21_multiset.size(), std_multiset.size());
}

TEST(S21_multiset, Constructor_initializer_list) {
  s21::multiset<int> s21_multiset = {0, 15, 14, 20, 20, 15, 20};
  EXPECT_FALSE(s21_multiset.empty());
  EXPECT_TRUE(s21_multiset.size() == 7);
  int arr[s21_multiset.size()] = {0, 14, 15, 15, 20, 20, 20};
  auto it = s21_multiset.begin();
  for (size_t i = 0; i < s21_multiset.size(); i++, ++it){
    EXPECT_EQ(*it, arr[i]);
  }
  
}

// TEST(S21_multiset, Constructor_copy) {
//   s21::multiset<int> s21_multiset = {0, 5, 10, 15};
//   s21::multiset<int> s21_multiset_copy(s21_multiset);
//   std::multiset<int> std_multiset;
//   for(int i = 0; i <= 15; i += 5 ) std_multiset.insert(i);
//   std::multiset<int> std_multiset_copy(std_multiset);

//   EXPECT_EQ(s21_multiset.empty(), std_multiset.empty());
//   EXPECT_EQ(s21_multiset.size(), std_multiset.size());
//   EXPECT_EQ(*s21_multiset.begin(), *std_multiset.begin());  

//   EXPECT_EQ(s21_multiset_copy.empty(), std_multiset_copy.empty());
//   EXPECT_EQ(s21_multiset_copy.size(), std_multiset_copy.size());
//   EXPECT_EQ(*(s21_multiset_copy.begin()), *(std_multiset_copy.begin()));
// }

TEST(S21_multiset, Constructor_move) {
  s21::multiset<int> s21_multiset = {0, 5, 10, 15};
  s21::multiset<int> s21_multiset_move(std::move(s21_multiset));
  std::multiset<int> std_multiset;
  for(int i = 0; i <= 15; i += 5 ) std_multiset.insert(i);
  std::multiset<int> std_multiset_move(std::move(std_multiset));

  EXPECT_EQ(s21_multiset.empty(), std_multiset.empty());
  EXPECT_EQ(s21_multiset.size(), std_multiset.size());

  EXPECT_EQ(s21_multiset_move.empty(), std_multiset_move.empty());
  EXPECT_EQ(s21_multiset_move.size(), std_multiset_move.size());
  EXPECT_EQ(*(s21_multiset_move.begin()), *(std_multiset_move.begin()));
}

// TEST(S21_multiset, Operator_copy) {
//   s21::multiset<int> s21_multiset = {0, 5, 10, 15};
  // s21::multiset<int> s21_multiset_cp = {0, -5, -10, -15, 5}; 

//   s21_multiset_cp = s21_multiset;

//   EXPECT_EQ(s21_multiset.size(), s21_multiset_cp.size());

//   for(auto s21_it_2 = s21_multiset_cp.begin(), s21_it = s21_multiset.begin();
//                    s21_it != s21_multiset.end(); s21_it++, s21_it_2++){
//     EXPECT_EQ(*s21_it, *s21_it_2);
//   }
//   EXPECT_FALSE(*s21_multiset_cp.contains(-10));
// }

TEST(S21_multiset, insert_5000_random) {
  s21::multiset<int> s21_multiset;
  std::multiset<int> std_multiset;
  size_t size_mset = 5000;
  random_insert(size_set, 100099, s21_multiset, std_multiset);
  EXPECT_EQ(s21_multiset.empty(), std_multiset.empty());
  EXPECT_EQ(s21_multiset.size(), std_multiset.size());
  EXPECT_EQ(s21_multiset.size(), size_mset);
  EXPECT_EQ(*(s21_multiset.begin()), *(std_multiset.begin()));
  EXPECT_TRUE(s21_multiset.BLM());
  EXPECT_FALSE(s21_multiset.RedAlert());
}

TEST(S21_SET, erase) {
  std::vector<int> vector {1,2,0,5,6,-1,-2, 0};
  s21::set<int> s21_set;
  std::set<int> std_set;
  for(size_t i = 0; i <= vector.size(); i++) {
    EXPECT_EQ(std_set.insert(vector[i]).second, s21_set.insert(vector[i]).second);
  }
  std_set.erase(0);
  s21_set.erase(0);

  EXPECT_TRUE(s21_set.size() == std_set.size());
  EXPECT_TRUE(s21_set.contains(0));
  EXPECT_EQ(*std_set.find(0), *s21_set.find(0));

  EXPECT_TRUE(s21_set.BLM());
  EXPECT_FALSE(s21_set.RedAlert());
}

TEST(S21_multiset, merge) {
  s21::multiset<int> s21_multiset_1 = {5,3,5,5,5};
  s21::multiset<int> s21_multiset_2 = {1,1,2,2,0};
  size_t old_size_mset_1 = s21_multiset_1.size()
  EXPECT_EQ(s21_multiset_1.size(), s21_multiset_2.size());

  s21_multiset_1.merge(s21_multiset_2);
  EXPECT_EQ(s21_multiset_1.size(), s21_multiset_2.size() + old_size_mset_1);
  EXPECT_EQ(*(s21_multiset_1.begin()), *(s21_multiset_2.begin()));
  EXPECT_TRUE(s21_multiset_1.BLM());
  EXPECT_FALSE(s21_multiset_1.RedAlert());
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}