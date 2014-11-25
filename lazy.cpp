#include "node.h"
#include "scope.h"
#include "lazy.h"
#include <iostream>

lazy::lazy(node *_fn, scope &_s) {
  has_default_value = false;
  s = &_s;
  func_node = _fn;
};

lazy::lazy() {
  has_default_value = false;
};

lazy::lazy(value v) {
  has_default_value = true;
  default_value = v;
}

value lazy::delazy() {
  if(has_default_value) {
    return default_value;
  }
  default_value = func_node->eval(*s);
  has_default_value = true;
  return default_value;
}

void lazy::print() {
  //TODO: normal printing
  func_node->print();
}
