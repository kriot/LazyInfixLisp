#pragma once
#include <vector>
#include <string>
#include "lambda.h"
using namespace std;
class node;
class scope;

class value {
public:
  char type;       
  double val;   //type 0
  lambda* func;  //type 1 
  void print();
  value();
  value(double n);
  value(lambda* fn);
  bool operator<(const value v2) const;
};

