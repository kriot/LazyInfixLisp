
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
  lambda_add* add = new lambda_add();
  lambda_sub* sub = new lambda_sub();
  lambda_mul* mul = new lambda_mul();
  lambda_div* div = new lambda_div();
  lambda_cond* cond = new lambda_cond();
  lambda_lambda* flambda = new lambda_lambda(); //Because lambda is reserved by class-name

  val["let"] = lazy(value(let));
  val["+"] = lazy(value(add));
  val["-"] = lazy(value(sub));
  val["*"] = lazy(value(mul));
  val["/"] = lazy(value(div));
  val["cond"] = lazy(value(cond));
  val["\\"] = lazy(value(flambda));
  val["lambda"] = lazy(value(flambda));
}

void scope::print() {
  for(auto i = val.begin(); i != val.end(); i++) {
    cout << "Print:\n";
    cout << i->first << ": ";
//    i->second.print();
    cout <<"\n";
  }
}
