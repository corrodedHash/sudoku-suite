#include <z3++.h>
#include <iostream>
void solve()
{
  z3::context c;
  z3::expr ebase = c.parse_file("test.smt2");
  z3::solver s(c);
  s.add(ebase);
  s.add(c.int_const("a_1_1") == 6);
  s.add(c.int_const("a_1_2") == 5);
  s.add(c.int_const("a_2_2") == 7);
  s.add(c.int_const("a_2_5") == 9);
  s.add(c.int_const("a_3_5") == 3);
  s.add(c.int_const("a_3_9") == 8);
  s.add(c.int_const("a_4_3") == 9);
  s.add(c.int_const("a_4_9") == 1);
  s.add(c.int_const("a_5_2") == 8);
  s.add(c.int_const("a_5_4") == 6);
  s.add(c.int_const("a_6_4") == 7);
  s.add(c.int_const("a_6_7") == 3);
  s.add(c.int_const("a_7_3") == 3);
  s.add(c.int_const("a_7_4") == 4);
  s.add(c.int_const("a_8_3") == 1);
  s.add(c.int_const("a_9_8") == 7);
  s.add(c.int_const("a_9_9") == 5);
  s.check();
  z3::model m = s.get_model();
  std::cout << m << "\n";
  // traversing the model
  for (unsigned i = 0; i < m.size(); i++) {
    z3::func_decl v = m[i];
    // this problem contains only constants
    assert(v.arity() == 0);
    std::cout << v.name() << " = " << m.get_const_interp(v) << "\n";
  }
}
int main(int argc, char** args){
  solve();
}
