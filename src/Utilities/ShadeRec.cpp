/* there is no default constructor as the World reference always has to be initialised
   there is also no assignment operator as we don't want to assign the world
   the copy constructor only copies the world reference
   the ray tracer is written so that new ShadeRec objects are always constructed
   using the first constructor or the copy constructor */

#include "ShadeRec.h"

ShadeRec::ShadeRec(World& wr) :
  hit_an_object(false),
  material_ptr(NULL),
  hit_point(Vector3d::Zero()),
  local_hit_point(Vector3d::Zero()),
  normal(Vector3d::Zero()),
  ray(),
  depth(0),
  t(0.0),
  w(wr),
  color()
{}


ShadeRec::ShadeRec(const ShadeRec& sr) :
  hit_an_object(sr.hit_an_object),
  material_ptr(sr.material_ptr),
  hit_point(sr.hit_point),
  local_hit_point(sr.local_hit_point),
  normal(sr.normal),
  ray(sr.ray),
  depth(sr.depth),
  t(sr.t),
  w(sr.w),
  color(sr.color)
{}


ShadeRec::~ShadeRec() {}
