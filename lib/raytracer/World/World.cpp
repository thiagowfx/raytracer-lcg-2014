#include "World.h"

/* tracer_ptr is set to NULL because the build functions will always construct the appropriate tracer
   ambient_ptr is set to a default ambient light because this will do for most scenes
   camera_ptr is set to NULL because the build functions will always have to construct a camera
   and set its parameters */

World::World() {}


World::~World() {
  if(tracer_ptr) {
    delete tracer_ptr;
    tracer_ptr = NULL;
  }
  if (ambient_ptr) {
    delete ambient_ptr;
    ambient_ptr = NULL;
  }
  if (camera_ptr) {
    delete camera_ptr;
    camera_ptr = NULL;
  }
  delete_objects();
  delete_lights();
}

/* raw_color is the pixel color computed by the ray tracer
   its RGB doubleing point components can be arbitrarily large
   mapped_color has all components in the range [0, 1], but still doubleing point
   display color has integer components for computer display
   the Mac's components are in the range [0, 65535]
   a PC's components will probably be in the range [0, 255]
   the system-dependent code is in the function convert_to_display_color
   the function SetCPixel is a Mac OS function */
void World::display_pixel(const int row, const int column, const RGBColor& raw_color, png::image<png::rgb_pixel>& image) const {
  RGBColor mapped_color;

  if (vp.show_out_of_gamut)
    mapped_color = raw_color.clamp_to_red();
  else
    mapped_color = raw_color.max_to_one();

  if (vp.gamma != 1.0)
    mapped_color = mapped_color.powc(1.0 / vp.gamma);

  //have to start from max y coordinate to convert to screen coordinates
  int x = column;
  int y = vp.vres - row - 1;

  image[y][x] = png::rgb_pixel(int(mapped_color.r * 255),
                               int(mapped_color.g * 255),
                               int(mapped_color.b * 255));
}


ShadeRec World::hit_objects(const Ray& ray) {
  ShadeRec sr(*this);
  double   t;
  Vector3d normal;
  Vector3d local_hit_point;
  double   tmin         = kHugeValue;
  const int num_objects = objects.size();

  for (int j = 0; j < num_objects; ++j) {
    if (objects[j]->hit(PRIMARY_RAY, ray, t, sr) && (t < tmin)) {
      sr.hit_an_object = true;
      tmin             = t;
      sr.material_ptr  = objects[j]->get_material();
      sr.hit_point     = ray.o + (t * ray.d);
      normal           = sr.normal;
      local_hit_point  = sr.local_hit_point;
    }
  }
  /** needed because the hit function may overwrite these */
  if(sr.hit_an_object) {
    sr.t = tmin;
    sr.normal = normal;
    sr.local_hit_point = local_hit_point;
  }
  return sr;
}


/* Deletes the objects in the objects array, and erases the array.
   The objects array still exists, because it's an automatic variable, but it's empty */
void World::delete_objects() {
  int num_objects = objects.size();

  for (int j = 0; j < num_objects; ++j) {
    delete objects[j];
    objects[j] = NULL;
  }

  objects.erase(objects.begin(), objects.end());
}


void World::delete_lights() {
  int num_lights = lights.size();

  for (int j = 0; j < num_lights; ++j) {
    delete lights[j];
    lights[j] = NULL;
  }

  lights.erase(lights.begin(), lights.end());
}
