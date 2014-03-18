#ifndef __PHONG__
#define __PHONG__

#include "Material.h"
#include "GlossySpecular.h"
#include "Lambertian.h"
#include "World.h"

class Phong :public Material
{
 public:
  Phong();
  virtual Material* clone() const;
  virtual ~Phong();
  virtual RGBColor shade (ShadeRec& s);
  void set_ka ( float ka);
  void set_kd ( float kd);
  void set_ks ( float ks);
  void set_cd (const RGBColor& color);
  void set_exp ( float exp);
  void set_cs (const RGBColor& color);

 private:
  Lambertian *ambient_brdf;
  Lambertian *diffuse_brdf;
  GlossySpecular *specular_brdf;
};

inline void Phong::set_ka (float ka) {
  ambient_brdf->set_ka (ka);
}

inline void Phong::set_kd (float kd) {
  diffuse_brdf->set_kd (kd);
}

inline void Phong::set_ks (float ks) {
  specular_brdf->set_ks (ks);
}

inline void Phong::set_cd (const RGBColor& color) {
  diffuse_brdf->set_cd (color);
  ambient_brdf->set_cd (color);
}

inline void Phong::set_exp (float exp) {
  specular_brdf->set_exp (exp);
}

inline void Phong::set_cs (const RGBColor& color) {
  specular_brdf->set_cs (color);
}


#endif
