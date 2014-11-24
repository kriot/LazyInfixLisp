#include <string>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
void print_n(string s, int n);
void match(istream &in, char c);
void whitespace(istream &in);
void error(string s);
bool is_letter(char c);
bool is_digit(char c);
bool is_operator(char c); 
string get_operator(istream& in);
int get_operator_priority(string c);
string get_name(istream &in, bool allow_op_in_name);
int get_num(istream &in);
void put_back(istream &in, string s);
