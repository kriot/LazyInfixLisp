#include "spec.h"
void print_n(string s, int n) {
  for(int i = 0; i < n; ++i) {
    cout << s;
  }
}

void match(istream &in, char c) {
  char v = in.get();
  if(c!=v) {
    cout << "Error: expected '" << c <<"', got '"<< v <<"'\n'";
    exit(0);
  }
}

void whitespace(istream &in) {
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
    c == '+' ||
    c == '-' ||
    c == '*' ||
    c == '/' ||
    c == '&' ||
    c == '|' ||
    c == '!' ||
    c == '~' ||
    c == '=' ||
    c == '^' ||
    c == '<' ||
    c == '>' ||
    c == '\\';
}

bool is_operator(char c) {
  return 
    c == '+' ||
    c == '-' ||
    c == '*' ||
    c == '/' ||
    c == '&' ||
    c == '|' ||
    c == '!' ||
    c == '~' ||
    c == '=' ||
    c == '<' ||
    c == '>' ||
    c == '^' ||
    c == '%';
}

string get_operator(istream &in) {
  string res = "";
  while(is_operator(in.peek())) {
    res += in.get();
  }
  return res;
}

int get_operator_priority(string c) {
  if(
      c == "*" ||
      c == "/" 
    )
    return 2;
  if(
      c == "+" ||
      c == "-"
    )
    return 3;
  
  return -1;
}

bool is_digit(char c) {
  return c >= '0' && c <='9';
}

string get_name(istream &in, bool allow_op_in_name) {
  string res;
  while (is_letter(in.peek()) && (allow_op_in_name || !is_operator(in.peek()))) {
    res.push_back(in.get());
  }
  return res;
}

int get_num(istream &in) {
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

void put_back(istream &in, string s) {
  for(int i = s.size() - 1; i >= 0; i--) { 
    in.putback(s[i]);
  }
}
