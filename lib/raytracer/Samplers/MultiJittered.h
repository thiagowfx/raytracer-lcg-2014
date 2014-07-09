#ifndef _MULTIJITTERED_MINE_
#define _MULTIJITTERED_MINE_

#include "Sampler.h"

class MultiJittered: public Sampler {
 public:
  MultiJittered();
  MultiJittered(const int);
  MultiJittered(const MultiJittered&);
  virtual const char* to_string();
  virtual MultiJittered* clone() const;
  virtual ~MultiJittered();
 private:
  virtual void generate_samples();
};

#endif // _MULTIJITTERED_MINE_
