#include <gtest/gtest.h>

/********** INCLUDES *********/
#include "BBox.h"
#include "Ray.h"
#include "RGBColor.h"
#include "ViewPlane.h"

using namespace Raytracer;
using namespace std;

// https://stackoverflow.com/questions/12851126/serializing-eigens-matrix-using-boost-serialization
// https://stackoverflow.com/questions/18382457/eigen-and-boostserialize/23407209#23407209
namespace boost {
  template<class Archive, typename _Scalar, int _Rows, int _Cols, int _Options, int _MaxRows, int _MaxCols>
  inline void serialize(Archive & ar,
                        Eigen::Matrix<_Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols> & t,
                        const unsigned int file_version) {
    ar & boost::serialization::make_array(t.data(), t.size());
  }
}

/********** CONSTANTS **********/
const bool MYBOOL = true;
const unsigned MYUNSIGNED = 1000;
const int MYINT = -1000;
const double MYDOUBLE = -0.1;
const Vector3d MYEIGEN = Vector3d(MYDOUBLE, MYDOUBLE, MYDOUBLE);

class RayTest : public ::testing::Test {
protected:
  virtual void SetUp() {
    ray = new Ray();
    ray->origin = MYEIGEN;
    ray->direction = MYEIGEN;
    ray_test = new Ray();
  }

  virtual void TearDown() {
    delete ray;
    delete ray_test;
  }

  Ray *ray;
  Ray *ray_test;
};

TEST_F(RayTest, serialization) {
  const char* filename = "Ray.xml";
  save_xml<Ray>(*ray, filename);
  load_xml<Ray>(*ray_test, filename);
  EXPECT_TRUE(*ray == *ray_test);
}


class RGBColorTest : public ::testing::Test {
protected:
  virtual void SetUp() {
    c = new RGBColor();
    c->r = MYDOUBLE;
    c->g = MYDOUBLE;
    c->b = MYDOUBLE;
    c_test = new RGBColor();
  }

  virtual void TearDown() {
    delete c;
    delete c_test;
  }

  RGBColor *c;
  RGBColor *c_test;
};

TEST_F(RGBColorTest, serialization) {
  const char* filename = "RGBColor.xml";
  save_xml<RGBColor>(*c, filename);
  load_xml<RGBColor>(*c_test, filename);
  EXPECT_TRUE(*c == *c_test);
}


class BBoxTest : public ::testing::Test {
protected:
  virtual void SetUp() {
    b = new BBox(MYDOUBLE,MYDOUBLE,MYDOUBLE,MYDOUBLE,MYDOUBLE,MYDOUBLE);
    b_test = new BBox();
  }

  virtual void TearDown() {
    delete b;
    delete b_test;
  }

  BBox *b;
  BBox *b_test;
};

TEST_F(BBoxTest, serialization) {
  const char* filename = "BBox.xml";
  save_xml<BBox>(*b, filename);
  load_xml<BBox>(*b_test, filename);
  EXPECT_TRUE(*b == *b_test);
}


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
  const char* filename = "ViewPlane.xml";
  save_xml<ViewPlane>(*vp, filename);
  load_xml<ViewPlane>(*vp_test, filename);
  EXPECT_TRUE(*vp == *vp_test);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
