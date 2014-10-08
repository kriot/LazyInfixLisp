#pragma once
#include <vector>
#include <string>
using namespace std;
class node;
class scope;

class value {
public:
  bool is_func;
  double val;
  node* func;
  scope* func_scope;
  vector<string> args_order;
  void print();
  value(int n);
  value(node* fn);
  value();
};

