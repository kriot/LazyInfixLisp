#include <iostream>
#include "value.h"
#include "node.h"
#include "scope.h"
#include "lambda.h"

void value::print() {
  if(type == 0) {
    cout << "Number: ";
    cout << val;
    cout << "\n";
  }
  else if(type == 1){
    func -> print();
  }
}
value::value() {
  cout << "Val by default\n";
  type = 0; //By default is number zero
  
  val = 0;
  func = nullptr;
}

value::value(double n) {
  cout << "Val by double\n";
  type = 0;
  val = n;
  func = nullptr;
}

value::value(lambda* fn) {
  cout << "Val by fn\n";
  type = 1;
  func = fn;
  val = 0;
}
