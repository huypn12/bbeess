#include <ginac/ex.h>
#include <ginac/ginac.h>
#include <ginac/numeric.h>
#include <gtest/gtest.h>

TEST(TestGinac, TestAvailable) {
  GiNaC::symtab table;
  GiNaC::symbol x("x"), y("y");
  table["x"] = x;
  table["y"] = y;
  GiNaC::parser reader(table);
  GiNaC::ex e = reader("2*x+sin(y)");
  std::cout << "Symbolic expression: " << e << std::endl;
  auto vals = GiNaC::lst{x == 2, y == 4};
  auto f = GiNaC::evalf(e.subs(vals));

  EXPECT_TRUE(GiNaC::is_a<GiNaC::numeric>(f));
  auto result = GiNaC::ex_to<GiNaC::numeric>(f).to_double();
  EXPECT_DOUBLE_EQ(result, 1.0);
}