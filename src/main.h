#pragma once
#include <map>
#include <set>
#include <iostream>

#include "map/map.h"

void print_set(std::set<int> &a);
void print_s21_map(s21::map<int, std::string> &t);
void r_print_s21_map(s21::map<int, std::string> &t);
void test_origin();
void test_1();
void test_2();
void test_3();
void test_4();
void test_5();
void test_6();
void test_big_random();

void random_insert(const int size_of_tree, int random, s21::map<int, std::string> &t);
