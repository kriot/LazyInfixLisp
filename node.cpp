#include "spec.h"
#include "node.h"
#include "scope.h"

node::node() {
}

void node::print() {
  print(0);
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

value func_eval(value f, vector<node*> args, scope& s) {
  scope s2;
  s2.parent = &s;
  for(int i = 0; i < f.args_order.size(); ++i) {
    s2.val[f.args_order[i]] = lazy(args[i], s);
  }
  return f.func->eval(s2);
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
      if(f_name == "\\") {
        value res;
        res.is_func = true;
        res.args_order.push_back(args[0]->f_name);
        for(int i = 0; i < args[0]->args.size(); ++i) {
          res.args_order.push_back(args[0]->args[i]->v_name);
        }
        res.func = args[1];
        return res;
      }
    }
    else {
      value f_val = s.find(f_name).delazy();
      if(!f_val.is_func) {
        error("Can't call not function");
      }
      return func_eval(f_val, args, s);
    }
  }
  else {
    error("Node without type");
  }
}
