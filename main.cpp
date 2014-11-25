#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <stdlib.h>
using namespace std;

#include "spec.h"
#include "node.h"
#include "value.h"
#include "lazy.h"
#include "value.h"
#include "scope.h"
#include "loadlib.h"

int main(int argc, char* argv[])
{
  ifstream in;
  if(argc < 2) {
    cout << "No input files\n";
    return 0;
  }
  in.open(argv[1]);
  node n(in);
  scope root_scope = scope();
  root_scope.init_root();
  scope* s = &root_scope;
  vector<string> libs = {"sys", "list", "math"};
  for(int i = 0; i < libs.size(); i++)
    s = loadlib(libs[i]+".lillib", s);
  cout <<"\n\nResult:\n";
  n.eval(*s).print();
  in.close();
  return 0;
}
