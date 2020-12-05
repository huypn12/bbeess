#include <ginac/ex.h>
#include <ginac/ginac.h>
#include <ginac/numeric.h>

void TestTrigonometricExpressions() {
  GiNaC::symbol x("x"), y("y");
  GiNaC::symtab table;
  table["x"] = x;
  table["y"] = y;
  GiNaC::parser reader(table);
  GiNaC::ex e = reader("2*x+sin(y)");
  // assert
  auto vals = GiNaC::lst{x == 2, y == 4};
  auto f = GiNaC::evalf(e.subs(vals));
  auto expected_str = "4+sin(4)";

  auto result = GiNaC::ex_to<GiNaC::numeric>(f).to_double();
  if (GiNaC::is_a<GiNaC::numeric>(f)) {
  }
}

void TestPolynomialExpressions() {}

void TestFractionExpressions() {}
