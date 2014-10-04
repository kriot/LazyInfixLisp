#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <stdlib.h>

using namespace std;
class value {
public:
  int type;
  int val;
  void print() {
    cout << val;
  }
};

class node {
public:
  bool cons;
  bool func;
  value val;
  string f_name;
  vector<node> args;
  string v_name;
  node(ifstream &in);
  node();
  void print(int n);
};

node::node() {
}

void print_n(string s, int n) {
  for(int i = 0; i < n; ++i) {
    cout << s;
  }
}

void node::print(int n = 0) {
  print_n("\t", n);
  if(func) {
    cout << f_name << ":\n";
    for(int i = 0; i < args.size(); ++i) {
      args[i].print(n+1);
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

class scope {
public:
  scope* parent;
  map<string, value> val;
  value find(string name) 
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
      else
        return value();
    }
  }
  scope() 
  {
    parent = nullptr;
  }
};

void match(ifstream &in, char c) {
  char v = in.get();
  if(c!=v) {
    cout << "Error: expected '" << c <<"', got '"<< v <<"'\n'";
  }
}

void whitespace(ifstream &in) {
  while(in.peek() == ' ' ||
      in.peek() == '\t' ||
      in.peek() == '\n' ||
      in.peek() == '\r')
  {
    in.get();
  }
}

bool is_letter(char c) {
  return 
    c >= 'a' && c <= 'z' ||
    c >= 'A' && c <= 'Z' ||
    c == '_' ||
    c == '$';
}

bool is_digit(char c) {
  return c >= '0' && c <='9';
}

string get_name(ifstream &in) {
  string res;
  while (is_letter(in.peek())) {
    res.push_back(in.get());
  }
  return res;
}

int get_num(ifstream &in) {
  int res = 0;
  while (is_digit(in.peek())) {
    res *= 10;
    res += in.get() - '0';
  }
  return res;
}

node::node(ifstream &in) {
  whitespace(in);
  char c = in.peek();
  if(c == '(') {
    match(in, '(');
    
    func = true;
    cons = false;
    f_name = get_name(in);

    while(whitespace(in), in.peek() != ')' && !in.eof()) 
    {
      args.push_back(node(in));
    } 
    
    match(in, ')');
    return;
  }
  if(is_letter(c) || is_digit(c)) {
    //operator
    node lp, rp;
    if(is_letter(c)) {
      lp.func = false;
      lp.cons = false;
      lp.v_name = get_name(in);
      (*this) = lp;
      return;
    }
    if(is_digit(c)) {
      func = false;
      cons = true;
      val.val = get_num(in);
      return;
    }
  }
  cout << "unexpected symbol: " <<(char)in.get()<< "\n";
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
  in.close();
  return 0;
}
