#include "node.h"
#include "scope.h"
#include "lazy.h"

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
  if(has_default_value)
    return default_value;
  return func_node->eval(*s);
}

void lazy::print() {
  //TODO: normal printing
  func_node->print();
}
