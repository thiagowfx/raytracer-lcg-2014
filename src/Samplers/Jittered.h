#ifndef __JITTERED__
#define __JITTERED__

#include "Sampler.h"

class Jittered: public Sampler {
  
 public:		
  Jittered(); 
  Jittered(const int num_samples); 
  Jittered(const int num_samples, const int m); 
  Jittered(const Jittered& u); 
  Jittered& operator= (const Jittered& rhs); 
  virtual Jittered* clone() const; 
  virtual ~Jittered();
		
 private:
  virtual void generate_samples();
  
};

#endif

