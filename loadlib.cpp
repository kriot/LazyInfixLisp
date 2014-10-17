#include <string>
#include <vector>
#include <fstream>
#include "lazy.h"
#include "scope.h"
#include "node.h"
#include "value.h"
#include "spec.h"

using namespace std;
scope* loadlib(string file, scope* s)
{
  ifstream in(file.c_str());
  node n(in);
  if(!n.func || n.node_func->v_name!="let")
    error("Library file is invalid. "+file);
  auto args = n.args;
  
  scope *s2 = new scope();
  s2 -> parent = s;
  for(int i = 0; i < args.size(); ++i) {
    if(! args[i] -> node_func -> vari)
      error("Syntax error in let");
    s2 -> val[args[i] -> node_func -> v_name] = lazy(value());
  }
  for(int i = 0; i < args.size(); ++i) {
    if(! args[i] -> node_func -> vari)
      error("Syntax error in let");
    s2 -> val[args[i] -> node_func -> v_name] = lazy(args[i]->args[0], *s2);
  }

  return s2;
}
