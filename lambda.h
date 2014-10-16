#pragma once
#include <vector>
#include <string>
using namespace std;
class node;
class scope;
class value;

class lambda {
public:
  node* func_node;
  scope* func_scope;
  vector<string> args_order;
  virtual value eval(vector<node*> args, scope &s);
  void print();
  lambda();
  lambda(node* _fn, scope* _fs, vector<string> _ao);
};

class lambda_let : public lambda {
  value eval(vector<node*> args, scope &s);
};
