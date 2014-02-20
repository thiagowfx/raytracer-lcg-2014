#ifndef __SHADE_REC__
#define __SHADE_REC__

class World; // only need a forward class declaration as the World data member is a reference

#include "Constants.h"
#include "RGBColor.h"
#include <Eigen/Dense>
using Eigen::Vector3d;

class ShadeRec {
  
 public:
  bool		hit_an_object;	 // did the ray hit an object?
  Vector3d	local_hit_point; // world coordinates of hit point 
  Vector3d	normal;		 // normal at hit point
  World&	w;		 // world reference for shading
  ShadeRec(World& wr);		 // constructor
  ShadeRec(const ShadeRec& sr);	 // copy constructor
  ~ShadeRec();
  
};

#endif
