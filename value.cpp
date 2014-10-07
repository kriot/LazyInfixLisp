#include <iostream>
#include "value.h"
#include "node.h"
#include "scope.h"

void value::print() {
  if(is_func) {
    cout << "Lambda: \n";
    cout << "Scope: \n";
    func_scope -> print(); 
    func->print();
  }
  else {
    cout << val;
  }
}
value::value(int n) {
  val = n;
  is_func = false;
} 
value::value(node* fn) {
  func = fn;
  is_func = true;
}
value::value() {
  val = 0;
  is_func = false;
  func = nullptr;
}
