#ifndef __WORLD__
#define __WORLD__

// The World class does not have a copy constructor or an assignment operator, for the followign reasons:
// 1 	There's no need to copy construct or assign the World
// 2 	We wouldn't want to do this anyway, because the world can contain an arbitray amount of data
// 3 	These operations wouldn't work because the world is self-referencing:
//	 	the Tracer base class contains a pointer to the world. If we wrote a correct copy constructor for the 
// 	  	Tracer class, the World copy construtor would call itself recursively until we ran out of memory. 

#include "Constants.h"
#include "GeometricObject.h"
#include "MultipleObjects.h"
#include "Plane.h"
#include "RGBColor.h"
#include "Ray.h"
#include "ShadeRec.h"
#include "Sphere.h"
#include "Tracer.h"
#include "ViewPlane.h"
#include "World.h"
#include <Eigen/Dense>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <png++/png.hpp>
#include <vector>
using Eigen::Vector2d;
using Eigen::Vector3d;
using namespace std;

class World {
  
 public:	
  ViewPlane                vp;
  RGBColor                 background_color;
  Tracer*                  tracer_ptr;
  vector<GeometricObject*> objects;		
		
  World(void); 
  ~World();
  void add_object(GeometricObject* object_ptr);
  void build(void);
  void render_scene(FILE *fp) const;
  void render_perspective(FILE *fp) const;
  RGBColor max_to_one(const RGBColor& c) const;
  RGBColor clamp_to_color(const RGBColor& c) const;
  void display_pixel(const int row, const int column, const RGBColor& pixel_color, FILE *fp) const;
  ShadeRec hit_bare_bones_objects(const Ray& ray);
  void file_to_png(FILE *fp, const char *imageFile);
						
 private:
  void delete_objects(void);
  
};


inline void World::add_object(GeometricObject* object_ptr) {  
  objects.push_back(object_ptr);	
}


#endif
