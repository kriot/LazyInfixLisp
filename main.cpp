#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <stdlib.h>

using namespace std;
class value {
  int type;
};

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

string get_name(ifstream &in) {
  string res;
  while (is_letter(in.peek())) {
    res.push_back(in.get());
  }
  return res;
}

string get_arg(ifstream &in) {
  string res;
  int n = 0;
  whitespace(in);
  while(!(in.peek() == ' ' && n == 0)) {
    char c = in.get();
    if(c=='(') ++n;
    if(c==')') --n;
    if(n == -1) {
      in.unget();
      break;
    }
    if(c==EOF) 
    {
      cout << "Error: expected ')'\n";
      exit(0);
    }
    res.push_back(c);
  }
  return res;
}

value evaluate_func(ifstream &in, scope s) {
  match(in, '(');
  string name = get_name(in);
  vector<string> args;
  while(in.peek() != ')' && !in.eof()) 
  {
    args.push_back(get_arg(in));
  } 

  cout << "Exec: "<<name<<"\nArgs:\n";

  for(int i = 0; i < args.size(); i++) {
    cout << "\t" << args[i] <<"\n";
  }

  match(in, ')');
}

value evaluate(ifstream &in, scope s) {
  cout <<"evaluate\n";
  char c = in.peek();
  if(c == '(') {
    return evaluate_func(in, s);
  }
  if(is_letter(c)) {
//    return evaluate_operator(in, s);
  }
  if(c == EOF) {
    return value();
  }
  in.get();
  return evaluate(in, s);
}

int main(int argc, char* argv[])
{
  ifstream in;
  if(argc < 2) {
    cout << "No input files\n";
    return 0;
  }
  in.open(argv[1]);
  evaluate(in, scope());  
  in.close();
  return 0;
}
