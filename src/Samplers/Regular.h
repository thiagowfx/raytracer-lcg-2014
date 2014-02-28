#ifndef __REGULAR__
#define __REGULAR__

#include "Sampler.h"

class Regular: public Sampler {
  
 public:		
  Regular();							
  Regular(const int num);					
  Regular(const Regular& u);				
  Regular& operator= (const Regular& rhs);			
  virtual Regular* clone() const;			
  virtual ~Regular();
  virtual void generate_samples();
  
};

#endif

