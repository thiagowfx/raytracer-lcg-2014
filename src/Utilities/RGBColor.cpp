#include "RGBColor.h"
#include <math.h>

RGBColor::RGBColor() 
  : r(0.0), g(0.0), b(0.0) 
{}


RGBColor::RGBColor(float c)
  : r(c), g(c), b(c) 							
{}
								

RGBColor::RGBColor(float _r, float _g, float _b)	
  : r(_r), g(_g), b(_b)
{}


RGBColor::RGBColor(const RGBColor& c)
  : r(c.r), g(c.g), b(c.b)
{} 				 
		

RGBColor::~RGBColor() {}


RGBColor& RGBColor::operator= (const RGBColor& rhs) {
  if (this != &rhs) {
    r = rhs.r;
    g = rhs.g;
    b = rhs.b;
  }

  return *this;
}


/* Raise each component to the specified power */
// used for color filtering in Chapter 28
RGBColor RGBColor::powc(float p) const {
  return RGBColor(pow(r, p), pow(g, p), pow(b, p));
}
