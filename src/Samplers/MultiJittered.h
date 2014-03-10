#ifndef __MULTI_JITTERED__
#define __MULTI_JITTERED__

#include "Sampler.h"

class MultiJittered: public Sampler {

 public:
  MultiJittered();
  MultiJittered(const int num_samples);
  MultiJittered(const int num_samples, const int m);
  MultiJittered(const MultiJittered& mjs);
  MultiJittered& operator= (const MultiJittered& rhs);
  virtual MultiJittered* clone() const;
  virtual ~MultiJittered();

 private:
  virtual void generate_samples();
  
};

#endif
