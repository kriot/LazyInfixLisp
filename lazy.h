#pragma once
#include "node.h"

class scope;
class lazy {
public:
  node *func_node;
  vector<node*> args;
  scope *s;
  lazy(node *_fn, scope &_s);
  lazy();
  value delazy();
};
