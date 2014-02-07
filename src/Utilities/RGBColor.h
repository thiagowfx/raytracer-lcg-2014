#ifndef __RGB_COLOR__
#define __RGB_COLOR__

class RGBColor {
	
 public:
  float	r, g, b;									
				
 public:
  RGBColor(void);			  // default constructor
  RGBColor(float c);			  // constructor
  RGBColor(float _r, float _g, float _b); // constructor
  RGBColor(const RGBColor& c);		  // copy constructor
  ~RGBColor(void);			  // destructor
  RGBColor& operator= (const RGBColor& rhs); 
  RGBColor operator+ (const RGBColor& c) const;	
  RGBColor& operator+= (const RGBColor& c);
  RGBColor operator* (const float a) const;
  RGBColor& operator*= (const float a);					
  RGBColor operator/ (const float a) const;
  RGBColor& operator/= (const float a); 
  RGBColor operator* (const RGBColor& c) const;
  bool operator== (const RGBColor& c) const;
  RGBColor powc(float p) const;
  float average(void) const;
};


// addition of two colors
inline RGBColor 
RGBColor::operator+ (const RGBColor& c) const {
  return (RGBColor(r + c.r, g + c.g, b + c.b));
}


// compound addition of two colors
inline RGBColor& RGBColor::operator+= (const RGBColor& c) {
  r += c.r; g += c.g; b += c.b;
  return (*this);
}


// multiplication by a float on the right
inline RGBColor RGBColor::operator* (const float a) const {
  return (RGBColor (r * a, g * a, b * a));	
}


// compound multiplication by a float on the right
inline RGBColor& RGBColor::operator*= (const float a) {
  r *= a; g *= a; b *= a;
  return (*this);
}


// division by float
inline RGBColor RGBColor::operator/ (const float a) const {
  return (RGBColor (r / a, g / a, b / a));
}


// compound division by float
inline RGBColor& RGBColor::operator/= (const float a) {	
  r /= a; g /= a; b /= a;
  return (*this);
}



// component-wise multiplication of two colors
inline RGBColor RGBColor::operator* (const RGBColor& c) const {
  return (RGBColor (r * c.r, g * c.g, b * c.b));
} 


// are two RGBColors the same?
inline bool RGBColor::operator== (const RGBColor& c) const {
  return (r == c.r && g == c.g && b == c.b);
}

// the average of the three components
inline float											
RGBColor::average(void) const {
  return (0.333333333333 * (r + g + b));
}


// multiplication by a float on the left
RGBColor operator* (const float a, const RGBColor& c);

inline RGBColor operator* (const float a, const RGBColor& c) {
  return (RGBColor (a * c.r, a * c.g, a * c.b));	
}

#endif
