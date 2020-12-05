#include <ginac/ex.h>
#include <ginac/ginac.h>
#include <ginac/numeric.h>

void TestGinac() {
  GiNaC::symbol x("x"), y("y");
  GiNaC::symtab table;
  table["x"] = x;
  table["y"] = y;
  GiNaC::parser reader(table);
  GiNaC::ex e = reader("2*x+sin(y)");
  std::cout << "Symbolic expression: " << e << std::endl;
  auto vals = GiNaC::lst{x == 2, y == 4};
  auto f = GiNaC::evalf(e.subs(vals));
  if (GiNaC::is_a<GiNaC::numeric>(f)) {
    auto result = GiNaC::ex_to<GiNaC::numeric>(f).to_double();
    std::cout << "Eval: " << result << std::endl;
  }
}

int main() {
  TestGinac();
  return 0;
}
