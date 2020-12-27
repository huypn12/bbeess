#include <gtest/gtest.h>

#include <vector>

class TestHpd : public ::testing::Test {
 protected:
  void SetUp() override {
    // Load sample data set calculated by PyMC3
  }
  void TearDown() override;
};

TEST(TestHpd, TestUnimodal) {}

TEST(TestHpd, TestMultimodal) {}