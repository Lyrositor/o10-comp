//#include <iostream>
//#include <comp/ast.h>
//
//int main() {
//  std::cout << comp::ast::create_node() << "\n";
//  return 0;
//}

#include "../lib/expr.h"
#include <iostream>

int main(void) {
  Expression * e;
  map<string,double> var;
  var["x"] = 5.;
  var["y"] = -4.;

  e = new OperateurPlus(new OperateurDiv(new Valeur(2),new Variable("x")), new Variable("y"));
  cout<<"Valeur de l'expression : "<<e->Evaluation(var)<<endl;
  return 0;
}
