#include "spec.h"
void print_n(string s, int n) {
  for(int i = 0; i < n; ++i) {
    cout << s;
  }
}

void match(ifstream &in, char c) {
  char v = in.get();
  if(c!=v) {
    cout << "Error: expected '" << c <<"', got '"<< v <<"'\n'";
    exit(0);
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
    c == '$' ||
    c == '\\';
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

void error(string s) {
  cout << "Error: " << s <<"\n";
  exit(0); 
}
