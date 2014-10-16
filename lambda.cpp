#include <vector>
#include <string>
#include <iostream>

#include "lambda.h"
#include "node.h"
#include "scope.h"
#include "value.h"
#include "lazy.h"
#include "spec.h"
using namespace std;

lambda::lambda() {
  func_node = nullptr;
  func_scope = nullptr;
  args_order.resize(0);
}

lambda::lambda(node* _fn, scope* _fs, vector<string> _ao) {
  func_node = _fn;
  func_scope = _fs;
  args_order = _ao;
}

value lambda::eval(vector<node*> args, scope &s) {
  //TODO: Check is func not null
  cout << "Lambda_eval\n";
  scope *s2 = new scope();
  s2 -> parent = func_scope;
  for(int i = 0; i < args_order.size(); ++i) {
    cout << "Adding to scope arg: "<<args_order[i]<<"\n";
    s2 -> val[args_order[i]] = lazy(args[i], s);
  }
  return func_node->eval(*s2);
}

void lambda::print() {
  //TODO: Check the scope or the func is null 
  cout << "Lambda: \n";
  cout << "Scope: \n";
  func_scope -> print(); 
  cout << "Node: \n";
  func_node  -> print();
}

value lambda_let::eval(vector<node*> args, scope &s) {
  scope *s2 = new scope();
  s2 -> parent = &s;
  for(int i = 0; i < args.size() - 1; ++i) {
    if(! args[i] -> node_func -> vari)
      error("Syntax error in let");
    s2 -> val[args[i] -> node_func -> v_name] = lazy(value());
  }
  for(int i = 0; i < args.size() - 1; ++i) {
    if(! args[i] -> node_func -> vari)
      error("Syntax error in let");
    s2 -> val[args[i] -> node_func -> v_name] = lazy(args[i]->args[0], *s2);
  }
  return args.back()->eval(*s2);
}
