#include "node.h"
#include "scope.h"
#include "lazy.h"

lazy::lazy(node *_fn, scope &_s) {
  s = &_s;
  func_node = _fn;
};

lazy::lazy() {
};

value lazy::delazy() {
  return func_node->eval(*s);
}
