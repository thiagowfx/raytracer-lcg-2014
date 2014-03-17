/* Test Includes */
#include <gtest/gtest.h>


/* Project Includes */
#include <cstdio>
#include "RGBColor.h"

/* Class example */
class RGBColorTest : public ::testing::Test {

 protected:
  RGBColor c1, c2, c3;
  
  virtual void SetUp() {
    c1 = RGBColor(0.1, 0.1, 0.1);
    c2 = RGBColor(0.2, 0.2, 0.2);
  }

  virtual void TearDown() {
  }

};


/* Test Fixture Example (that is, test of a class) */
TEST_F(RGBColorTest, operatorPlus) {
  c3 = c1 + c2;
  EXPECT_EQ( RGBColor(0.3, 0.3, 0.3), c3);
}

/* Single Test Example
 * The first argument is 'something bigger', the second one is a subitem of it
 */
// TEST(RGBColorTest, operatorPlus) {
//   RGBColor c1(0.1, 0.1, 0.1), c2(0.2, 0.2, 0.2);
//   RGBColor c3 = c1 + c2;  
//   EXPECT_EQ(c3, RGBColor(0.3, 0.3, 0.3));
// }


/* Mandatory to all tests
 * No need to create several files, just use this one
 */
int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
