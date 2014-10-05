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
  scope root_scope = scope();
  n.eval(root_scope).print();
  cout << "\n";
  in.close();
  return 0;
}
