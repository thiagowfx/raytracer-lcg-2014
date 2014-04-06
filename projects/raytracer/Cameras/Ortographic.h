#ifndef __ORTOGRAPHIC__
#define __ORTOGRAPHIC__

/* This uses ortographic viewning along the zw axis */

#include "Camera.h"
#include "World.h"

class Ortographic : public Camera {
  
 public:
  Ortographic();
  Ortographic(const Ortographic&);
  Ortographic& operator= (const Ortographic& rhs);
  virtual ~Ortographic();
  virtual Ortographic* clone() const;
  void set_view_distance(const float);
  virtual void render_scene(const World& w, const char* image_file);

 private:
  float zw;
};


inline void Ortographic::set_view_distance(const float d) {
  this->zw = d;
}

#endif
