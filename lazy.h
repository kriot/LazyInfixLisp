#pragma once
#include "node.h"

class scope;
class lazy {
public:
  node *func_node;
  vector<node*> args;
  scope *s;
  bool has_default_value;
  value default_value;
  lazy(node *_fn, scope &_s);
  lazy(value v);
  lazy();
  value delazy();
};
