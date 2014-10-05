#include <string>
#include <map>
#include "lazy.h"

class scope {
public:
  scope* parent;
  map<string, lazy> val;
  lazy find(string name);
  scope(); 
};
