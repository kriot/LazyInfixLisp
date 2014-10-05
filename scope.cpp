
#include <string>
#include <map>
#include <vector>
#include "scope.h"
#include "lazy.h"
#include "spec.h"

lazy scope::find(string name) 
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
    else {
      error("Undefined symbol: "+name);
    }
  }
}
scope::scope() 
{
  parent = nullptr;
}
