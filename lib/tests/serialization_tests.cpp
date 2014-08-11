#include <gtest/gtest.h>

/********** INCLUDES *********/
#include "Camera.h"
#include "AmbientOccluder.h"
#include "Ambient.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "Emissive.h"
#include "Reflective.h"
#include "Phong.h"
#include "Matte.h"
#include "BBox.h"
#include "PerfectSpecular.h"
#include "Lambertian.h"
#include "GlossySpecular.h"
#include "Ray.h"
#include "RGBColor.h"
#include "ViewPlane.h"

using namespace Raytracer;
using namespace std;

// https://stackoverflow.com/questions/12851126/serializing-eigens-matrix-using-boost-serialization
// https://stackoverflow.com/questions/18382457/eigen-and-boostserialize/23407209#23407209
// https://stackoverflow.com/questions/12580579/how-to-use-boostserialization-to-save-eigenmatrix
namespace boost {
  namespace serialization {
    template<class Archive, typename _Scalar, int _Rows, int _Cols, int _Options, int _MaxRows, int _MaxCols>
    inline void serialize(Archive & ar,
                          Eigen::Matrix<_Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols> & t,
                          const unsigned int file_version) {
      ar & boost::serialization::make_array(t.data(), t.size());
      /*
        size_t rows = t.rows(), cols = t.cols();
        ar & rows;
        ar & cols;
        if( rows * cols != t.size() )
        t.resize( rows, cols );

        for(size_t i=0; i<t.size(); i++)
        ar & t.data()[i];
      */
    }
  }
}

/********** CONSTANTS **********/
const bool MYBOOL = true; // FIXME
const unsigned MYUNSIGNED = 1000;
const int MYINT = -1000;
const double MYDOUBLE = -0.1;
const Vector3d MYVECTOR3D = Vector3d(MYDOUBLE, MYDOUBLE, MYDOUBLE);
const RGBColor MYRGBCOLOR = RGBColor(0.3, 0.3, 0.3);


class PerfectSpecularTest : public ::testing::Test {
protected:
  virtual void SetUp() {
    ps = new PerfectSpecular();
    ps->set_kr(MYDOUBLE);
    ps->set_cr(MYRGBCOLOR);
    ps_test = new PerfectSpecular();
  }

  virtual void TearDown() {
    delete ps;
    delete ps_test;
  }

  PerfectSpecular *ps;
  PerfectSpecular *ps_test;
};

TEST_F(PerfectSpecularTest, XmlSerialization) {
  const char* filename = "PerfectSpecular.xml";
  save_xml<PerfectSpecular>(*ps, filename);
  load_xml<PerfectSpecular>(*ps_test, filename);
  EXPECT_TRUE(*ps == *ps_test);
}

TEST_F(PerfectSpecularTest, BinarySerialization) {
  const char* filename = "PerfectSpecular.bin";
  save_binary<PerfectSpecular>(*ps, filename);
  load_binary<PerfectSpecular>(*ps_test, filename);
  EXPECT_TRUE(*ps == *ps_test);
}

class LambertianTest : public ::testing::Test {
protected:
  virtual void SetUp() {
    lamb = new Lambertian();
    lamb->set_kd(MYDOUBLE);
    lamb->set_cd(MYRGBCOLOR);
    lamb_test = new Lambertian();
  }

  virtual void TearDown() {
    delete lamb;
    delete lamb_test;
  }

  Lambertian *lamb;
  Lambertian *lamb_test;
};

TEST_F(LambertianTest, XmlSerialization) {
  const char* filename = "Lambertian.xml";
  save_xml<Lambertian>(*lamb, filename);
  load_xml<Lambertian>(*lamb_test, filename);
  EXPECT_TRUE(*lamb == *lamb_test);
}

TEST_F(LambertianTest, BinarySerialization) {
  const char* filename = "Lambertian.bin";
  save_binary<Lambertian>(*lamb, filename);
  load_binary<Lambertian>(*lamb_test, filename);
  EXPECT_TRUE(*lamb == *lamb_test);
}

class GlossySpecularTest : public ::testing::Test {
protected:
  virtual void SetUp() {
    gs = new GlossySpecular();
    gs->set_ks(MYDOUBLE);
    gs->set_exp(MYDOUBLE);
    gs->set_cs(MYRGBCOLOR);
    gs_test = new GlossySpecular();
  }

  virtual void TearDown() {
    delete gs;
    delete gs_test;
  }

  GlossySpecular *gs;
  GlossySpecular *gs_test;
};

TEST_F(GlossySpecularTest, XmlSerialization) {
  const char* filename = "GlossySpecular.xml";
  save_xml<GlossySpecular>(*gs, filename);
  load_xml<GlossySpecular>(*gs_test, filename);
  EXPECT_TRUE(*gs == *gs_test);
}

TEST_F(GlossySpecularTest, BinarySerialization) {
  const char* filename = "GlossySpecular.bin";
  save_binary<GlossySpecular>(*gs, filename);
  load_binary<GlossySpecular>(*gs_test, filename);
  EXPECT_TRUE(*gs == *gs_test);
}

class RayTest : public ::testing::Test {
protected:
  virtual void SetUp() {
    ray = new Ray();
    ray->origin = MYVECTOR3D;
    ray->direction = MYVECTOR3D;
    ray_test = new Ray();
  }

  virtual void TearDown() {
    delete ray;
    delete ray_test;
  }

  Ray *ray;
  Ray *ray_test;
};

TEST_F(RayTest, XmlSerialization) {
  const char* filename = "Ray.xml";
  save_xml<Ray>(*ray, filename);
  load_xml<Ray>(*ray_test, filename);
  EXPECT_TRUE(*ray == *ray_test);
}

TEST_F(RayTest, BinarySerialization) {
  const char* filename = "Ray.bin";
  save_binary<Ray>(*ray, filename);
  load_binary<Ray>(*ray_test, filename);
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

TEST_F(RGBColorTest, XmlSerialization) {
  const char* filename = "RGBColor.xml";
  save_xml<RGBColor>(*c, filename);
  load_xml<RGBColor>(*c_test, filename);
  EXPECT_TRUE(*c == *c_test);
}

TEST_F(RGBColorTest, BinarySerialization) {
  const char* filename = "RGBColor.bin";
  save_binary<RGBColor>(*c, filename);
  load_binary<RGBColor>(*c_test, filename);
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

TEST_F(BBoxTest, XmlSerialization) {
  const char* filename = "BBox.xml";
  save_xml<BBox>(*b, filename);
  load_xml<BBox>(*b_test, filename);
  EXPECT_TRUE(*b == *b_test);
}

TEST_F(BBoxTest, BinarySerialization) {
  const char* filename = "BBox.bin";
  save_binary<BBox>(*b, filename);
  load_binary<BBox>(*b_test, filename);
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

TEST_F(ViewPlaneTest, XmlSerialization) {
  const char* filename = "ViewPlane.xml";
  save_xml<ViewPlane>(*vp, filename);
  load_xml<ViewPlane>(*vp_test, filename);
  EXPECT_TRUE(*vp == *vp_test);
}

TEST_F(ViewPlaneTest, BinarySerialization) {
  const char* filename = "ViewPlane.bin";
  save_binary<ViewPlane>(*vp, filename);
  load_binary<ViewPlane>(*vp_test, filename);
  EXPECT_TRUE(*vp == *vp_test);
}


class MatteTest : public ::testing::Test {
protected:
  virtual void SetUp() {
    matte = new Matte(MYRGBCOLOR);
    matte->set_ka(MYDOUBLE);
    matte->set_kd(MYDOUBLE);
    matte_test = new Matte();
  }

  virtual void TearDown() {
    delete matte;
    delete matte_test;
  }

  Matte *matte;
  Matte *matte_test;
};

TEST_F(MatteTest, XmlSerialization) {
  const char* filename = "Matte.xml";
  save_xml<Matte>(*matte, filename);
  load_xml<Matte>(*matte_test, filename);
  EXPECT_TRUE(*matte == *matte_test);
}

TEST_F(MatteTest, BinarySerialization) {
  const char* filename = "Matte.bin";
  save_binary<Matte>(*matte, filename);
  load_binary<Matte>(*matte_test, filename);
  EXPECT_TRUE(*matte == *matte_test);
}


class PhongTest : public ::testing::Test {
protected:
  virtual void SetUp() {
    phong = new Phong(MYRGBCOLOR);
    phong->set_ka(MYDOUBLE);
    phong->set_kd(MYDOUBLE);
    phong->set_ks(MYDOUBLE);
    phong->set_exp(MYDOUBLE);
    phong_test = new Phong();
  }

  virtual void TearDown() {
    delete phong;
    delete phong_test;
  }

  Phong *phong;
  Phong *phong_test;
};

TEST_F(PhongTest, XmlSerialization) {
  const char* filename = "Phong.xml";
  save_xml<Phong>(*phong, filename);
  load_xml<Phong>(*phong_test, filename);
  EXPECT_TRUE(*phong == *phong_test);
}

TEST_F(PhongTest, BinarySerialization) {
  const char* filename = "Phong.bin";
  save_binary<Phong>(*phong, filename);
  load_binary<Phong>(*phong_test, filename);
  EXPECT_TRUE(*phong == *phong_test);
}

class ReflectiveTest : public ::testing::Test {
protected:
  virtual void SetUp() {
    reflective = new Reflective(MYRGBCOLOR);
    reflective->set_kr(MYDOUBLE);
    reflective_test = new Reflective();
  }

  virtual void TearDown() {
    delete reflective;
    delete reflective_test;
  }

  Reflective *reflective;
  Reflective *reflective_test;
};

TEST_F(ReflectiveTest, XmlSerialization) {
  const char* filename = "Reflective.xml";
  save_xml<Reflective>(*reflective, filename);
  load_xml<Reflective>(*reflective_test, filename);
  EXPECT_TRUE(*reflective == *reflective_test);
}

TEST_F(ReflectiveTest, BinarySerialization) {
  const char* filename = "Reflective.bin";
  save_binary<Reflective>(*reflective, filename);
  load_binary<Reflective>(*reflective_test, filename);
  EXPECT_TRUE(*reflective == *reflective_test);
}

class EmissiveTest : public ::testing::Test {
protected:
  virtual void SetUp() {
    emissive = new Emissive(MYRGBCOLOR);
    emissive->set_radiance(MYDOUBLE);
    emissive->set_ce(MYRGBCOLOR);
    emissive_test = new Emissive();
  }

  virtual void TearDown() {
    delete emissive;
    delete emissive_test;
  }

  Emissive *emissive;
  Emissive *emissive_test;
};

TEST_F(EmissiveTest, XmlSerialization) {
  const char* filename = "Emissive.xml";
  save_xml<Emissive>(*emissive, filename);
  load_xml<Emissive>(*emissive_test, filename);
  EXPECT_TRUE(*emissive == *emissive_test);
}

TEST_F(EmissiveTest, BinarySerialization) {
  const char* filename = "Emissive.bin";
  save_binary<Emissive>(*emissive, filename);
  load_binary<Emissive>(*emissive_test, filename);
  EXPECT_TRUE(*emissive == *emissive_test);
}


class PointLightTest : public ::testing::Test {
protected:
  virtual void SetUp() {
    pl = new PointLight(MYVECTOR3D);
    pl->set_radiance(MYDOUBLE);
    pl->set_color(MYRGBCOLOR);
    pl_test = new PointLight();
  }

  virtual void TearDown() {
    delete pl;
    delete pl_test;
  }

  PointLight *pl;
  PointLight *pl_test;
};

TEST_F(PointLightTest, XmlSerialization) {
  const char* filename = "PointLight.xml";
  save_xml<PointLight>(*pl, filename);
  load_xml<PointLight>(*pl_test, filename);
  EXPECT_TRUE(*pl == *pl_test);
}

TEST_F(PointLightTest, BinarySerialization) {
  const char* filename = "PointLight.bin";
  save_binary<PointLight>(*pl, filename);
  load_binary<PointLight>(*pl_test, filename);
  EXPECT_TRUE(*pl == *pl_test);
}


class DirectionalLightTest : public ::testing::Test {
protected:
  virtual void SetUp() {
    dl = new DirectionalLight(MYVECTOR3D);
    dl->set_radiance(MYDOUBLE);
    dl->set_color(MYRGBCOLOR);
    dl_test = new DirectionalLight();
  }

  virtual void TearDown() {
    delete dl;
    delete dl_test;
  }

  DirectionalLight *dl;
  DirectionalLight *dl_test;
};

TEST_F(DirectionalLightTest, XmlSerialization) {
  const char* filename = "DirectionalLight.xml";
  save_xml<DirectionalLight>(*dl, filename);
  load_xml<DirectionalLight>(*dl_test, filename);
  EXPECT_TRUE(*dl == *dl_test);
}

TEST_F(DirectionalLightTest, BinarySerialization) {
  const char* filename = "DirectionalLight.bin";
  save_binary<DirectionalLight>(*dl, filename);
  load_binary<DirectionalLight>(*dl_test, filename);
  EXPECT_TRUE(*dl == *dl_test);
}



class AmbientTest : public ::testing::Test {
protected:
  virtual void SetUp() {
    ambient = new Ambient();
    ambient->set_radiance(MYDOUBLE);
    ambient->set_color(MYRGBCOLOR);
    ambient_test = new Ambient();
  }

  virtual void TearDown() {
    delete ambient;
    delete ambient_test;
  }

  Ambient *ambient;
  Ambient *ambient_test;
};

TEST_F(AmbientTest, XmlSerialization) {
  const char* filename = "Ambient.xml";
  save_xml<Ambient>(*ambient, filename);
  load_xml<Ambient>(*ambient_test, filename);
  EXPECT_TRUE(*ambient == *ambient_test);
}

TEST_F(AmbientTest, BinarySerialization) {
  const char* filename = "Ambient.bin";
  save_binary<Ambient>(*ambient, filename);
  load_binary<Ambient>(*ambient_test, filename);
  EXPECT_TRUE(*ambient == *ambient_test);
}


class AmbientOccluderTest : public ::testing::Test {
protected:
  virtual void SetUp() {
    ambient = new AmbientOccluder();
    ambient->set_minimum_amount(MYDOUBLE);
    ambient_test = new AmbientOccluder();
  }

  virtual void TearDown() {
    delete ambient;
    delete ambient_test;
  }

  AmbientOccluder *ambient;
  AmbientOccluder *ambient_test;
};

TEST_F(AmbientOccluderTest, XmlSerialization) {
  const char* filename = "AmbientOccluder.xml";
  save_xml<AmbientOccluder>(*ambient, filename);
  load_xml<AmbientOccluder>(*ambient_test, filename);
  EXPECT_TRUE(*ambient == *ambient_test);
}

TEST_F(AmbientOccluderTest, BinarySerialization) {
  const char* filename = "AmbientOccluder.bin";
  save_binary<AmbientOccluder>(*ambient, filename);
  load_binary<AmbientOccluder>(*ambient_test, filename);
  EXPECT_TRUE(*ambient == *ambient_test);
}

class CameraTest : public ::testing::Test {
protected:
  virtual void SetUp() {
    camera = new Camera();
    camera->set_eye_carthesian(MYVECTOR3D);
    // FIXME (na parte de girar a camera?) camera->set_lookat(MYVECTOR3D);
    camera->set_zoom(MYDOUBLE);
    camera->set_distance(MYDOUBLE);
    // FIXME (na parte de girar a camera?) camera->set_up_vector(MYVECTOR3D);
    camera_test = new Camera();
  }

  virtual void TearDown() {
    delete camera;
    delete camera_test;
  }

  Camera *camera;
  Camera *camera_test;
};

TEST_F(CameraTest, XmlSerialization) {
  const char* filename = "Camera.xml";
  save_xml<Camera>(*camera, filename);
  load_xml<Camera>(*camera_test, filename);
  EXPECT_TRUE(*camera == *camera_test);
}

TEST_F(CameraTest, BinarySerialization) {
  const char* filename = "Camera.bin";
  save_binary<Camera>(*camera, filename);
  load_binary<Camera>(*camera_test, filename);
  EXPECT_TRUE(*camera == *camera_test);
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
