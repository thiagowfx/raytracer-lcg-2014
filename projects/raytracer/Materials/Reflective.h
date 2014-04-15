#ifndef __REFLECTIVE__
#define __REFLECTIVE__

#include "Phong.h"
#include "PerfectSpecular.h"

class Reflective: public Phong {
  
 public:
  Reflective(); 
  Reflective(const Reflective& rm); 
  Reflective& operator= (const Reflective& rhs);
  virtual Reflective* clone() const; 
  ~Reflective(); 
  void set_kr(const double k);
  void set_cr(const RGBColor& c);
  virtual RGBColor shade(ShadeRec& s);
		
 private:
  PerfectSpecular* reflective_brdf;
  
};


inline void Reflective::set_kr(const double k) {
  reflective_brdf->set_kr(k);
}


inline void Reflective::set_cr(const RGBColor& c) {
  reflective_brdf->set_cr(c);
	
}

#endif
