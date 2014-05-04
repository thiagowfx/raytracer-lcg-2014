#include "PrimitivaDaniel.h"


PrimitivaDaniel::PrimitivaDaniel() :
  GeometricObject(),
  primitive()
{}


PrimitivaDaniel::PrimitivaDaniel(Primitive* p) :
  GeometricObject(),
  primitive(p)
{}

PrimitivaDaniel::PrimitivaDaniel(const PrimitivaDaniel& pd) :
  GeometricObject(pd),
  primitive(NULL)
{
  /*
  if(primitive)
      primitive = pd.primitive->clone();
  */
}




PrimitivaDaniel::~PrimitivaDaniel() {
  if (primitive) {
    delete primitive;
    primitive = NULL;
  }
}

PrimitivaDaniel *PrimitivaDaniel::clone() const {
  return new PrimitivaDaniel(*this);
}


bool PrimitivaDaniel::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
  Vector3d intersectionPoint;
  Vector3d intersectionNormal;

  if ( primitive->rayIntersection(ray.o, ray.d, intersectionPoint, intersectionNormal) ) {
    tmin = (intersectionPoint - ray.o).norm();

    if (tmin >  kEpsilonShadows) {
      sr.normal = intersectionNormal;
      sr.local_hit_point = intersectionPoint;
      return true;
    }
  }
  return false;
}

bool PrimitivaDaniel::shadow_hit(const Ray &ray, double &tmin) const {
  Vector3d intersectionPoint;
  Vector3d intersectionNormal;

  if ( primitive->rayIntersection(ray.o, ray.d, intersectionPoint, intersectionNormal) ) {
    tmin = (intersectionPoint - ray.o).norm();

    if (tmin >  kEpsilonShadows)
      return true;
  }
  return false;
}
