#include "World.h"

namespace Raytracer {
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
  

  void World::display_pixel(const int row, const int column,
                            const RGBColor& raw_color /**< Pixel color computed by the raytracer */,
                            png::image<png::rgb_pixel>& image) const {
    RGBColor mapped_color;
    if (vp.out_of_gamut) {
      mapped_color = raw_color.clamp_to_red();
    }
    else {
      mapped_color = raw_color.normalize();
    }
    if (vp.gamma != 1.0) {
      mapped_color = mapped_color.powc(1.0 / vp.gamma);
    }
    int x = column;
    int y = vp.vres - row - 1;
    image[y][x] = png::rgb_pixel(int(mapped_color.r * 255),
                                 int(mapped_color.g * 255),
                                 int(mapped_color.b * 255));
  }


  ShadeRec World::hit_objects(const Ray& ray) {
    ShadeRec sr(*this);
    double t;
    Vector3d normal;
    Vector3d local_hit_point;
    double tmin = kHugeValue;
    const unsigned num_objects = objects.size();
    for (unsigned j = 0; j < num_objects; ++j) {
      if (objects[j]->hit(PRIMARY_RAY, ray, t, sr) && (t < tmin)) {
        sr.hit_an_object = true;
        tmin             = t;
        sr.material_ptr  = objects[j]->get_material();
        sr.hit_point     = ray.o + (t * ray.d);
        normal           = sr.normal;
        local_hit_point  = sr.local_hit_point;
      }
    }
    /** Needed because the hit function may overwrite these */
    if(sr.hit_an_object) {
      sr.t = tmin;
      sr.normal = normal;
      sr.local_hit_point = local_hit_point;
    }
    return sr;
  }


  void World::delete_objects() {
    const unsigned num_objects = objects.size();
    for (unsigned j = 0; j < num_objects; ++j) {
      delete objects[j];
      objects[j] = NULL;
    }
    objects.erase(objects.begin(), objects.end());
  }


  void World::delete_lights() {
    const unsigned num_lights = lights.size();
    for (unsigned j = 0; j < num_lights; ++j) {
      delete lights[j];
      lights[j] = NULL;
    }
    lights.erase(lights.begin(), lights.end());
  }
}
