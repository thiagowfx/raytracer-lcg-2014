#include "PrimitivaDaniel.h"


PrimitivaDaniel::PrimitivaDaniel() :
  GeometricObject(),
  primitive()
{}


PrimitivaDaniel::PrimitivaDaniel(Primitive* p) :
  GeometricObject(),
  primitive(p)
{}


PrimitivaDaniel::~PrimitivaDaniel() {
  if (primitive) {
    delete primitive;
    primitive = NULL;
  }
}


bool PrimitivaDaniel::hit(const Ray& ray, double& tmin, ShadeRec& sr) const {
  Vector3d intersectionPoint;
  Vector3d intersectionNormal;

  if ( primitive->rayIntersection(ray.o, ray.d, intersectionPoint, intersectionNormal) ) {
    tmin = (intersectionPoint - ray.o).norm();
    sr.normal = intersectionNormal;
    sr.local_hit_point = intersectionPoint;
    return true;
  }

  return false;
}
