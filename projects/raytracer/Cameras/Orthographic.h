#ifndef __ORTHOGRAPHIC__
#define __ORTHOGRAPHIC__

/* This uses ortographic viewning along the zw axis */

#include "Camera.h"
#include "World.h"

class Orthographic : public Camera {
  
 public:
  Orthographic();
  Orthographic(const Orthographic&);
  Orthographic& operator= (const Orthographic& rhs);
  virtual ~Orthographic();
  virtual Orthographic* clone() const;
  void set_view_distance(const double);
  virtual void render_scene(const World* w, const char* image_file);

 private:
  double zw;
};


inline void Orthographic::set_view_distance(const double d) {
  this->zw = d;
}

#endif
