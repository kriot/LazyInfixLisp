#include <iostream>
#include "value.h"
#include "node.h"
#include "scope.h"
#include "lambda.h"

void value::print() {
  if(type == 0) {
    cout << "Number: ";
    cout << val;
    cout << "\n";
  }
  else if(type == 1){
    func -> print();
  }
}
value::value() {
  type = 0; //By default is number zero
  
  val = 0;
  func = nullptr;
}

value::value(double n) {
  type = 0;
  val = n;
  func = nullptr;
}

value::value(lambda* fn) {
  type = 1;
  func = fn;
  val = 0;
}

bool value::operator<(const value v2) const {
  if(type != v2.type) 
    return type < v2.type;
  if(type == 0)
    return val < v2.val;
  if(type == 1)
    return ((long long)func) < ((long long)v2.func);
} 
