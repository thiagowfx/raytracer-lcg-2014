#include <gtest/gtest.h>
#include <math.h>
#include "RGBColor.h"

double squareRoot(const double a) {
  double b = sqrt(a);
  if(b != b) { // nan check
    return -1.0;
  }else{
    return sqrt(a);
  }
}

TEST(SquareRootTest, PositiveNos) {
  ASSERT_EQ(6, squareRoot(36.0));
  ASSERT_EQ(18.0, squareRoot(324.0));
  ASSERT_EQ(25.4, squareRoot(645.16));
  ASSERT_EQ(0, squareRoot(0.0));
}

TEST(SquareRootTest, NegativeNos) {
  ASSERT_EQ(-1.0, squareRoot(-15.0));
  ASSERT_EQ(-1.0, squareRoot(-0.2));
}

TEST(RGBColorTest, operatorPlus) {
  RGBColor c1(0.1, 0.1, 0.1), c2(0.2, 0.2, 0.2);
  RGBColor c3 = c1 + c2;
  
  EXPECT_EQ(c3, RGBColor(0.3, 0.3, 0.3));
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
