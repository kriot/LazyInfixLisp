#include <string>
#include <fstream>
#include <iostream>
using namespace std;
void print_n(string s, int n);
void match(ifstream &in, char c);
void whitespace(ifstream &in);
void error(string s);
bool is_letter(char c);
bool is_digit(char c);
string get_name(ifstream &in);
int get_num(ifstream &in);

