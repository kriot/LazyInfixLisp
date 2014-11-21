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
  if(memorize) {
    vector<value> cargs(args.size());
    for(int i = 0; i < args.size(); ++i) {
      cargs[i] = args[i]->eval(s);
    }
    auto it = mem.find(cargs);
    if(it != mem.end())
      return it->second;
    else {
      //TODO: Check is func not null
      scope *s2 = new scope();
      s2 -> parent = func_scope;
      //Adding to scope args:
      for(int i = 0; i < args_order.size(); ++i) {
        s2 -> val[args_order[i]] = lazy(cargs[i]);
      }
      value res = func_node->eval(*s2);
      mem[cargs] = res;
      return res;
    }
  }
  else {
    //TODO: Check is func not null
    scope *s2 = new scope();
    s2 -> parent = func_scope;
    //Adding to scope args:
    for(int i = 0; i < args_order.size(); ++i) {
      s2 -> val[args_order[i]] = lazy(args[i], s);
    }
    return func_node->eval(*s2);
  }
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

// TODO: <, <=, >, >= and other functions

value lambda_add::eval(vector<node*> args, scope &s) {
  value res;
  res.val = 0;
  for(int i = 0; i<args.size(); ++i) {
    res.val += args[i] -> eval(s).val;
  }
  return res;
}
value lambda_sub::eval(vector<node*> args, scope &s) {
  value res;
  res.val = 0;
  if(args.size() == 0)
    return res;
  if(args.size() == 1) {
    res.val = -args[0] -> eval(s).val;
    return res;
  }
  if(args.size() >= 2) {
    res.val = args[0] -> eval(s).val;
    for(int i = 1; i<args.size(); ++i) {
      res.val -= args[i] -> eval(s).val;
    }
    return res;
  }
  return res;
}
value lambda_mul::eval(vector<node*> args, scope &s) {
  value res;
  res.val = 1;
  for(int i = 0; i<args.size() && res.val != 0; ++i) {
    res.val *= args[i] -> eval(s).val;
  }
  return res;
}
value lambda_div::eval(vector<node*> args, scope &s) {
  value res;
  res.val = 1;
  if(args.size() == 0)
    return res;
  if(args.size() == 1) {
    res.val = 1/(args[0] -> eval(s).val);
    return res;
  }
  if(args.size() >= 2) {
    res.val = args[0] -> eval(s).val;
    for(int i = 1; i<args.size(); ++i) {
      res.val /= args[i] -> eval(s).val;
    }
    return res;
  }
  return res;
}
value lambda_lambda::eval(vector<node*> args, scope &s) {
  lambda* f = new lambda();
  f->func_scope = &s;
  
  int start = 0; //Index of argument of list of lambda's arguments

  if(args[0] -> v_name == "mem") {
    f -> memorize = true;
    start = 1;
  }

  if(args.size() != start + 2)
    error("Syntax error in lambda defenition (args are wrong)");

  if(! args[start] -> node_func -> vari)
    error("Syntax error in lambda defenition (args are wrong)");
  f->args_order.push_back(args[start]->node_func->v_name);
  for(int i = 0; i < args[start]->args.size(); ++i) {
    f->args_order.push_back(args[start]->args[i]->v_name);
  }
  f->func_node = args[start+1];
  return value(f);
}
value lambda_cond::eval(vector<node*> args, scope &s) {
  for(int i = 0; i < args.size(); ++i) {
    if(args[i] -> node_func -> eval(s) .val > 0) {
      if(args[i] -> args.size() == 0) 
        error("Syntax error in cond");
      return args[i] -> args[0] -> eval(s); 
    }
  }
  return value();
}
value lambda_read::eval(vector<node*> args, scope &s) {
  value res;
  cin >> res.val;
  return res;
}
value lambda_print::eval(vector<node*> args, scope &s) {
  for(int i = 0; i < args.size(); ++i) {
    cout << args[i] -> eval(s).val << " ";
  }
  cout << "\n";
  return value();
}
