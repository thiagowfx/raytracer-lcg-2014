#include <gtest/gtest.h>

// my includes
#include "ViewPlane.h"
using namespace Raytracer;

// test fixture
class ViewPlaneTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    vp = new ViewPlane();
    vp->set_hres(150);
  }

  virtual void TearDown() {}

  ViewPlane *vp;
};

TEST_F(ViewPlaneTest, Random) {
  EXPECT_EQ(vp->hres, 150);
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
