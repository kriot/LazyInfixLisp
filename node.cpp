#include "spec.h"
#include "node.h"
#include "scope.h"

node::node() {
}

const int max_pr = 22;

void node::print() {
  print(0);
}
void node::print(int n = 0) {
  print_n("\t", n);
  if(func) {
    if(node_func->vari)
      cout << node_func->v_name << ":\n";
    else if(node_func->func)
      cout << "Anonymous func:\n";
    else if(node_func->cons) {
      node_func -> val.print();
      cout << " (Not function):\n";
    }
    else 
      cout << "Undef token:\n";
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

void get_operator_tree(ifstream &in, node *n, int pr = max_pr) {
  if(pr == 0)
  {
    *n = node(in);
    return;
  }
  node *lp = new node();
  get_operator_tree(in, lp, pr-1);
  node *fn = new node();
 // fn -> v_name = get_operator(in);
  node *rp = new node();
  get_operator_tree(in, rp, pr);
  n -> node_func = fn;
  n -> args.push_back(lp);
  n -> args.push_back(rp);
  n -> func = true;
}

node::node(ifstream &in) {
  syst = false;
  func = false;
  cons = false;
  vari = false;
  v_name = "";
  whitespace(in);
  char c = in.peek();
  if(c == '(') {
    match(in, '(');
    
    func = true;
//    f_name = get_name(in);
    node_func = (new node(in));
    string f_name = node_func->v_name;
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
  if(c == '{') {
    get_operator_tree(in, this);
  }
  cout << "unexpected symbol: " <<(char)in.get()<< "\n";
}

value lambda_eval(value f, vector<node*> args, scope& s) {
  scope s2;
  s2.parent = &s;
  for(int i = 0; i < f.args_order.size(); ++i) {
    s2.val[f.args_order[i]] = lazy(args[i], s);
  }
  return f.func->eval(s2);
}

value func_eval(node* node_func, vector<node*> args, scope& s) {
  value f_val = node_func->eval(s);
  if(!f_val.is_func) {
    error("Can't call not function");
  }

  if(f_val.func -> syst)
  {
    string f_name = f_val.func -> v_name;
    if(f_name == "plus" || f_name == "+") {
      value res;
      res.val = 0;
      for(int i = 0; i<args.size(); ++i) {
        res.val += args[i] -> eval(s).val;
      }
      return res;
    }
    if(f_name == "*") {
      value res;
      res.val = 1;
      for(int i = 0; i<args.size() && res.val != 0; ++i) {
        res.val *= args[i] -> eval(s).val;
      }
      return res;
    }
    if(f_name == "/") {
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
    if(f_name == "sub" || f_name == "-") {
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
    if(f_name == "let") {
      scope s2;
      s2.parent = &s;
      for(int i = 0; i < args.size() - 1; ++i) {
        if(! args[i] -> node_func -> vari)
          error("Syntax error in let");
        s2.val[args[i] -> node_func -> v_name] = lazy(args[i]->args[0], s);
      }
      return args.back()->eval(s2);
    }
    if(f_name == "\\") {
      value res;
      res.is_func = true;
      if(! args[0] -> node_func -> vari)
        error("Syntax error in lambda defenition (args are wrong)");
      res.args_order.push_back(args[0]->node_func->v_name);
      for(int i = 0; i < args[0]->args.size(); ++i) {
        res.args_order.push_back(args[0]->args[i]->v_name);
      }
      res.func = args[1];
      return res;
    }
    if(f_name == "cond") {
      for(int i = 0; i < args.size(); ++i) {
        if(args[i] -> node_func -> eval(s) .val > 0) {
          if(args[i] -> args.size() == 0) 
            error("Syntax error in cond");
          return args[i] -> args[0] -> eval(s); 
        }
      }
      return value();
    }
  }
  else
    return lambda_eval(f_val, args, s);
}

value node::eval(scope& s) {
  if(cons)
    return val;
  if(vari) {
    return s.find(v_name).delazy();
  }
  if(func) {
    if(syst) {
    }
    else {
      return func_eval(node_func, args, s);
    }
  }
  else {
    error("Node without type");
  }
}
