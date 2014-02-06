// this file contains the definition of the World class

#include "World.h"
#include "Constants.h"

// geometric objects

#include "Plane.h"
#include "Sphere.h"

// tracers

#include "SingleSphere.h"
#include "MultipleObjects.h"

// utilities

#include <Eigen/Dense>
#include "Normal.h"
#include "ShadeRec.h"
#include "Maths.h"
#include <cmath>

using Eigen::Vector2d;
using Eigen::Vector3d;

// -------------------------------------------------------------------- default constructor

World::World(void)
  :  	background_color(black),
	tracer_ptr(NULL)
{}



//------------------------------------------------------------------ destructor

World::~World(void) {	
	
  if(tracer_ptr) {
    delete tracer_ptr;
    tracer_ptr = NULL;
  }	
	
  delete_objects();	
}


//------------------------------------------------------------------ render_scene

// This uses orthographic viewing along the zw axis

void World::render_scene(FILE *fp) const {
  RGBColor	pixel_color;	 	
  Ray			ray;					
  float		zw		= 100.0;			// hardwired in
  int n = (int) sqrt( (float)vp.num_samples );
  Vector2d pp;

  ray.d = Vector3D(0, 0, -1);
  fprintf(fp, "%d %d\n", vp.hres, vp.vres);
    
  for (int r = 0; r < vp.vres; r++) {			// up
    for (int c = 0; c <= vp.hres; c++) {	// across
      pixel_color = black;

      for (int p = 0; p < n; ++p) {   //up pixel
	for (int q = 0; q < n; ++q) { // accross pixel
	  pp(0) = vp.s * (c - 0.5 * vp.hres + (q + 0.5) / n );
	  pp(1) = vp.s * (r - 0.5 * vp.vres + (p + 0.5) / n );
	  ray.o = Vector3d(pp(0), pp(1), zw);
	  pixel_color += tracer_ptr->trace_ray(ray);
	}
      }
      
      pixel_color /= vp.num_samples; // average the colors
      display_pixel(r, c, pixel_color, fp);
    }
  }
}  
	  
	  
// ------------------------------------------------------------------ clamp

RGBColor
World::max_to_one(const RGBColor& c) const  {
  float max_value = max(c.r, max(c.g, c.b));
	
  if (max_value > 1.0)
    return (c / max_value);
  else
    return (c);
}


// ------------------------------------------------------------------ clamp_to_color
// Set color to red if any component is greater than one

RGBColor
World::clamp_to_color(const RGBColor& raw_color) const {
  RGBColor c(raw_color);
	
  if (raw_color.r > 1.0 || raw_color.g > 1.0 || raw_color.b > 1.0) {
    c.r = 1.0; c.g = 0.0; c.b = 0.0;
  }
		
  return (c);
}


// ---------------------------------------------------------------------------display_pixel

// raw_color is the pixel color computed by the ray tracer
// its RGB floating point components can be arbitrarily large
// mapped_color has all components in the range [0, 1], but still floating point
// display color has integer components for computer display
// the Mac's components are in the range [0, 65535]
// a PC's components will probably be in the range [0, 255]
// the system-dependent code is in the function convert_to_display_color
// the function SetCPixel is a Mac OS function


void World::display_pixel(const int row, const int column, const RGBColor& raw_color, FILE *fp) const {
  RGBColor mapped_color;

  if (vp.show_out_of_gamut)
    mapped_color = clamp_to_color(raw_color);
  else
    mapped_color = max_to_one(raw_color);
	
  if (vp.gamma != 1.0)
    mapped_color = mapped_color.powc(vp.inv_gamma);
	
  //have to start from max y coordinate to convert to screen coordinates
  int x = column;
  int y = vp.vres - row - 1;

  fprintf(fp, "%d %d %d %d %d\n", x, y, (int)(mapped_color.r * 255), (int)(mapped_color.g * 255), (int)(mapped_color.b * 255));
}



// ----------------------------------------------------------------------------- hit_bare_bones_objects

ShadeRec									
World::hit_bare_bones_objects(const Ray& ray) {
  ShadeRec	sr(*this); 
  double		t; 			
  float		tmin 			= kHugeValue;
  int 		num_objects 	= objects.size();
	
  for (int j = 0; j < num_objects; j++)
    if (objects[j]->hit(ray, t, sr) && (t < tmin)) {
      sr.hit_an_object	= true;
      tmin 				= t; 
      sr.color			= objects[j]->get_color(); 
    }
		
  return (sr);   
}


//------------------------------------------------------------------ delete_objects

// Deletes the objects in the objects array, and erases the array.
// The objects array still exists, because it's an automatic variable, but it's empty 

void
World::delete_objects(void) {
  int num_objects = objects.size();
	
  for (int j = 0; j < num_objects; j++) {
    delete objects[j];
    objects[j] = NULL;
  }	
	
  objects.erase (objects.begin(), objects.end());
}
