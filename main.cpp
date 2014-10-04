#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <stdlib.h>
#include "spec.h"

using namespace std;
class node;
class value {
public:
  bool is_func;
  int val;
  node* func;
  void print() {
    cout << val;
  }
  value(int n) {
    val = n;
    is_func = false;
  } 
  value(node* fn) {
    func = fn;
    is_func = true;
  }
  value() {
    val = 0;
    is_func = false;
    func = nullptr;
  }
};

class scope;

class node {
public:
  bool cons;
  bool func;
  bool syst;
  bool vari;
  value val;
  string f_name;
  vector<node*> args;
  string v_name;
  node(ifstream &in);
  node();
  void print(int n);
  value eval(scope &s);
};

class lazy {
public:
  node *func_node;
  vector<node*> args;
  scope *s;
  lazy(node *_fn, scope &_s) {
    s = &_s;
    func_node = _fn;
  };
  lazy() {
  };
  value delazy();
};

class scope {
public:
  scope* parent;
  map<string, lazy> val;
  lazy find(string name) 
  {
    auto it = val.find(name);
    if(it != val.end()) 
    {
      return it->second;
    }
    else 
    {
      if(parent != nullptr) 
      {
        return parent->find(name);  
      }
      else {
        error("Undefined symbol: "+name);
      }
    }
  }
  scope() 
  {
    parent = nullptr;
  }
};



node::node() {
}

void node::print(int n = 0) {
  print_n("\t", n);
  if(func) {
    cout << f_name << ":\n";
    for(int i = 0; i < args.size(); ++i) {
      args[i] -> print(n+1);
    }
  }
  else if(cons) {
    cout <<"const: ";
    val.print();
    cout << "\n";
  }
  else {
    cout <<"var: "<< v_name <<"\n";
  }
}

node::node(ifstream &in) {
  syst = false;
  func = false;
  cons = false;
  vari = false;
  whitespace(in);
  char c = in.peek();
  if(c == '(') {
    match(in, '(');
    
    func = true;
    f_name = get_name(in);
    if(f_name == "cond" ||
        f_name == "let" ||
        f_name == "\\"  ||
        f_name == "plus") {
      syst = true;
    }
    while(whitespace(in), in.peek() != ')' && !in.eof()) 
    {
      args.push_back(new node(in));
    } 
    
    match(in, ')');
    return;
  }
  if(is_letter(c) || is_digit(c)) {
    if(is_letter(c)) {
      vari = true;
      v_name = get_name(in);
      return;
    }
    if(is_digit(c)) {
      cons = true;
      val = value(get_num(in));
      return;
    }
  }
  cout << "unexpected symbol: " <<(char)in.get()<< "\n";
}

value func_eval(node *f, vector<node*> args, scope& s) {
  return value();
}
value lazy::delazy() {
  return func_node->eval(*s);
}
value node::eval(scope& s) {
  if(cons)
    return val;
  if(vari) {
    return s.find(v_name).delazy();
  }
  if(func) {
    if(syst) {
      if(f_name == "plus") {
        value res;
        res.val = 0;
        for(int i = 0; i<args.size(); ++i) {
          res.val += args[i] -> eval(s).val;
        }
        return res;
      }
      if(f_name == "let") {
        scope s2;
        s2.parent = &s;
        for(int i = 0; i < args.size() - 1; ++i) {
          s2.val[args[i] -> f_name] = lazy(args[i]->args[0], s);
        }
        return args.back()->eval(s2);
      }
    }
    else {
      value f_val = s.find(f_name).delazy();
      if(!f_val.is_func) {
        error("Can't call not function");
      }
      return func_eval(f_val.func, args, s);
    }
  }
  else {
    error("Node without type");
  }
}

int main(int argc, char* argv[])
{
  ifstream in;
  if(argc < 2) {
    cout << "No input files\n";
    return 0;
  }
  in.open(argv[1]);
  node n(in);
  n.print();  
  scope root_scope = scope();
  n.eval(root_scope).print();
  cout << "\n";
  in.close();
  return 0;
}
