#include "Compound.h"

namespace Raytracer {
  Compound::Compound () :
    GeometricObject()
  {}


  Compound* Compound::clone() const {
    return new Compound(*this);
  }


  Compound::Compound (const Compound& c) :
    GeometricObject(c) {
    copy_objects(c.objects);
  }


  Compound::~Compound() {
    delete_objects();
  }


  void Compound::add_object(GeometricObject* object_ptr) {
    objects.push_back(object_ptr);
  }


  void Compound::set_material(Material* material_ptr) {
    const unsigned num_objects = objects.size();
    for (unsigned j = 0; j < num_objects; ++j)
      objects[j]->set_material(material_ptr);
  }


  void Compound::set_shadows(const bool shadow){
    const unsigned num_objects = objects.size();
    for (unsigned j = 0; j < num_objects; ++j)
      objects[j]->set_shadows(shadow);
  }


  void Compound::delete_objects() {
    const unsigned num_objects = objects.size();
    for (unsigned j = 0; j < num_objects; ++j) {
      delete objects[j];
      objects[j] = NULL;
    }
    objects.erase(objects.begin(), objects.end());
  }


  void Compound::copy_objects(const vector<GeometricObject*>& rhs_ojects) {
    delete_objects();
    const unsigned num_objects = rhs_ojects.size();
    for (unsigned j = 0; j < num_objects; ++j)
      objects.push_back(rhs_ojects[j]->clone());
  }


  bool Compound::hit(const Ray_t& type, const Ray& ray, double& tmin, ShadeRec& sr) const {
    double t;
    Vector3d normal;
    Vector3d local_hit_point;
    bool hit = false;
    tmin = kHugeValue;
    const unsigned num_objects = objects.size();

    for (unsigned j = 0; j < num_objects; ++j)
      if (objects[j]->hit(type, ray, t, sr) && (t < tmin)) {
        hit = true;
        tmin = t;
        material_ptr = objects[j]->get_material();
        if (type == PRIMARY_RAY) {
          normal = sr.normal;
          local_hit_point = sr.local_hit_point;
        }
      }
    if (hit && type == PRIMARY_RAY) {
      sr.t = tmin;
      sr.normal = normal;
      sr.local_hit_point  = local_hit_point;
    }
    return hit;
  }
}
