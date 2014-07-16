#ifndef _COMPOUND_MINE_
#define _COMPOUND_MINE_

#include <vector>
#include "GeometricObject.h"

namespace Raytracer {
  /** A compound object represents a collection of objects. */
  class Compound: public GeometricObject {
  public:
    /** Construct a empty compound object. Objects should be added later. */
    Compound();
    Compound(const Compound&);
    ~Compound();
    virtual Compound* clone() const;

    /* Setters. */
    /** Set the same material on all objects. */
    virtual void set_material(Material*);

    /** Set the same shadows property on all objects. */
    virtual void set_shadows(const bool);
    
    /** Add a new object to this compound object. */
    virtual void add_object(GeometricObject*);

    /* Getters. */
    unsigned get_number_of_objects();

    virtual bool hit(const Ray_t& type, const Ray& ray, double& tmin, ShadeRec& sr) const;
  protected:
    /** Primitive objects or other compound ones. */
    vector<GeometricObject*> objects;
  private:
    /** Delete all objects from the array then empty it. */
    void delete_objects();
    /** Copy all objects from the given array to this compound object. */
    void copy_objects(const vector<GeometricObject*>&);
  };


  inline unsigned Compound::get_number_of_objects() {
    return objects.size();
  }
}

#endif // _COMPOUND_MINE_
