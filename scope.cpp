
#include <string>
#include <map>
#include <vector>
#include "scope.h"
#include "lazy.h"
#include "spec.h"

lazy scope::find(string name) 
{
  cout << "Scope 'find' request: "<<name<<"\n";
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
bool scope::has(string name) 
{
  cout << "Scope 'has' request: "<<name<<"\n";
  auto it = val.find(name);
  if(it != val.end()) 
  {
    return true;
  }
  else 
  {
    if(parent != nullptr) 
    {
      return parent->has(name);  
    }
    else {
      return false;
    }
  }
}
scope::scope() 
{
  parent = nullptr;
}
void scope::init_root() {
  lambda_let* let = new lambda_let();
  cout <<"Plet: "<< let <<"\n";
  val["let"] = lazy(value((lambda*)let));
  vector<string> a = {"+","plus", "-", "*", "/", "let", "cond", "\\"};
  for(int i = 0; i < a.size(); ++i) {
    string name = a[i];
   /* 
    value sys_f;
    sys_f.is_func = true;
    sys_f.func = new node();
    sys_f.func -> syst = true;
    sys_f.func -> v_name = name;
    val[name] = lazy(sys_f);*/
  }
}

void scope::print() {
  for(auto i = val.begin(); i != val.end(); i++) {
    cout << "Print:\n";
    cout << i->first << ": ";
//    i->second.print();
    cout <<"\n";
  }
}
