#include "Matte.h"

Matte::Matte () :
  Material(),
  ambient_brdf(new Lambertian),
  diffuse_brdf(new Lambertian)
{}


Matte::Matte(const Matte& m) :
  Material(m),
  ambient_brdf(NULL),
  diffuse_brdf(NULL)
{
  if(m.ambient_brdf)
    ambient_brdf = m.ambient_brdf->clone(); 
  
  if(m.diffuse_brdf)
    diffuse_brdf = m.diffuse_brdf->clone(); 
}


Material* Matte::clone() const {
  return new Matte(*this);
}	


Matte& Matte::operator= (const Matte& rhs) {
  if (this != &rhs) {		
    Material::operator=(rhs);
	
    if (ambient_brdf) {
      delete ambient_brdf;
      ambient_brdf = NULL;
    }

    if (rhs.ambient_brdf)
      ambient_brdf = rhs.ambient_brdf->clone();
		
    if (diffuse_brdf) {
      delete diffuse_brdf;
      diffuse_brdf = NULL;
    }

    if (rhs.diffuse_brdf)
      diffuse_brdf = rhs.diffuse_brdf->clone();

  }

  return *this;
}


Matte::~Matte() {
  if (ambient_brdf) {
    delete ambient_brdf;
    ambient_brdf = NULL;
  }
	
  if (diffuse_brdf) {
    delete diffuse_brdf;
    diffuse_brdf = NULL;
  }
}


RGBColor Matte::shade(ShadeRec& sr) {
  Vector3d wo = -sr.ray.d;
  RGBColor L = ambient_brdf->rho(sr, wo) * sr.w.ambient_ptr->L(sr);
  int num_lights = sr.w.lights.size();

  for (int j = 0; j < num_lights; j++) {
    Vector3d wi = sr.w.lights[j]->get_direction(sr);    
    double ndotwi = sr.normal.dot(wi);
	
    if (ndotwi > 0.0) 
      L += diffuse_brdf->f(sr, wo, wi) * sr.w.lights[j]->L(sr) * ndotwi;
  }
	
  return L;
}
