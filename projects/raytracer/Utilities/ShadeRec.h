#ifndef __SHADE_REC__
#define __SHADE_REC__

#include "Ray.h"
#include "RGBColor.h"
#include <Eigen/Dense>
using Eigen::Vector3d;

class Material;
class World;

class ShadeRec {
  
 public:
  bool	    hit_an_object;      // did the ray hit an object?
  Material* material_ptr;       // pointer to the nearest object's material
  Vector3d  hit_point;          // world coordinates of intersection
  Vector3d  local_hit_point;    // world coordinates of hit point on generic object (used for texture transformations)
  Vector3d  normal;             // normal at hit point
  Ray 	    ray;                // required for specular hightlights and area lights
  int	    depth;              // recursion depth
  RGBColor color;
  double	    t;                  // ray parameter
  World&    w;                  // world reference
  ShadeRec(World& wr);
  ShadeRec(const ShadeRec& sr);
  ~ShadeRec();
};

#endif
