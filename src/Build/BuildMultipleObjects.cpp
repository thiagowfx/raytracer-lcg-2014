#include "build.h"
#include "MultipleObjects.h"
#include "Plane.h"

void World::build(void) {
  vp.set_hres(200);
  vp.set_vres(200);
  vp.set_pixel_size(1.0);
  vp.set_num_samples(25);
	
  tracer_ptr = new MultipleObjects(this); 
	
  background_color = RGBColor(black);
	
  // use access functions to set centre and radius
	
  Sphere* sphere_ptr = new Sphere;
  sphere_ptr->set_center(0, -25, 0);
  sphere_ptr->set_radius(80);
  sphere_ptr->set_color(1, 0, 0);  // red
  add_object(sphere_ptr);

  // use constructor to set centre and radius 
	
  sphere_ptr = new Sphere(Vector3d(0, 30, 0), 60);
  sphere_ptr->set_color(1, 1, 0);	// yellow
  add_object(sphere_ptr);
	
  Plane* plane_ptr = new Plane(Vector3d(0,0,0), Vector3d(0, 1, 1));
  plane_ptr->set_color(0.0, 0.3, 0.0);	// dark green
  add_object(plane_ptr);

  sphere_ptr = new Sphere(Vector3d(15, -15, 80), 50);
  sphere_ptr->set_color(white);
  add_object(sphere_ptr);
}
