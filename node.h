#pragma once
#include <vector>
#include <fstream>

using namespace std;
#include "value.h"

class scope;

class node {
public:
  bool cons;
  bool func;
  bool vari;
  value val;
  vector<node*> args;
  node* node_func;
  string v_name;
  node(ifstream &in);
  node();
  void print(int n);
  void print();
  value eval(scope &s);
};

