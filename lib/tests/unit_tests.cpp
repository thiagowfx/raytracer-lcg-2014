#include <gtest/gtest.h>

/********** INCLUDES *********/
#include "ViewPlane.h"

#include <iostream>
using namespace Raytracer;
using namespace std;

/********** CONSTANTS **********/
const char* filename = "settings.out";
const bool MYBOOL = true;
const unsigned MYUNSIGNED = 1000;
const int MYINT = -1000;
const double MYDOUBLE = -0.01;

template<class T>
void save_xml(const T &t, const char* filename) {
  std::ofstream ofs(filename);
  boost::archive::xml_oarchive oa(ofs);
  oa << BOOST_SERIALIZATION_NVP(t);
}

template<class T>
void load_xml(T &t, const char* filename) {
  std::ifstream ifs(filename);
  boost::archive::xml_iarchive ia(ifs);
  ia >> BOOST_SERIALIZATION_NVP(t);
}

/********** VIEWPLANE **********/
class ViewPlaneTest : public ::testing::Test {
protected:
  virtual void SetUp() {
    vp = new ViewPlane();
    vp->set_hres(MYUNSIGNED);
    vp->set_vres(MYUNSIGNED);
    vp->set_pixel_size(MYDOUBLE);
    vp->set_gamma(MYDOUBLE);
    vp->set_out_of_gamut(MYBOOL);
    vp->set_max_depth(MYUNSIGNED);
    vp_test = new ViewPlane();
  }

  virtual void TearDown() {
    delete vp;
    delete vp_test;
  }

  ViewPlane *vp;
  ViewPlane *vp_test;
};

TEST_F(ViewPlaneTest, serialization) {
  save_xml<ViewPlane>(*vp, filename);
  load_xml<ViewPlane>(*vp_test, filename);
  EXPECT_TRUE(*vp == *vp_test);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
