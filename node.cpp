#include "spec.h"
#include "node.h"
#include "scope.h"

node::node() {
}

const int max_pr = 4;

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
  whitespace(in);
  char c = in.peek();
  if(c == '{')
  {
    match(in, '{');
    get_operator_tree(in, n);
    whitespace(in);
    match(in, '}');
  }
  else
  {
    if(pr == 0)
    {
      *n = node(in, false);
      return;
    }
    node *lp = new node();
    get_operator_tree(in, lp, pr-1);

    whitespace(in);
    string op = get_operator(in);
    put_back(in, op);
    int op_pr = get_operator_priority(op);
    if(op_pr != -1 && op_pr <= pr)
    {  
      node *fn = new node(in);
      node *rp = new node();
      get_operator_tree(in, rp, pr);
      n -> node_func = fn;
      n -> args.push_back(lp);
      n -> args.push_back(rp);
      n -> func = true;
    }
    else 
    {
      *n = *lp;
    }
  }
}

node::node(ifstream &in, bool allow_op_in_name /*= true*/) {
  func = false;
  cons = false;
  vari = false;
  v_name = "";
  whitespace(in);
  char c = in.peek();
  if(c == '(') {
    match(in, '(');
    
    func = true;

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
      v_name = get_name(in, allow_op_in_name);
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
    return;
  }
  char unc = in.get();
  cout << "unexpected symbol: " <<unc << " ("<<(int)unc<< ")\n";
}

value func_eval(node* node_func, vector<node*> args, scope& s) {
  value f_val = node_func->eval(s);
  if(f_val.type != 1) {
    error("Can't call not function");
  }

  return f_val.func -> eval(args, s);
}

value node::eval(scope& s) {
  if(cons)
    return val;
  if(vari) {
    return s.find(v_name).delazy();
  }
  if(func) {
    return func_eval(node_func, args, s);
  }
  else {
    error("Node without type");
  }
}
