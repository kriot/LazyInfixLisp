#pragma once
#include <vector>
#include <string>
using namespace std;
class node;

class value {
public:
  bool is_func;
  int val;
  node* func;
  vector<string> args_order;
  void print();
  value(int n);
  value(node* fn);
  value();
};

