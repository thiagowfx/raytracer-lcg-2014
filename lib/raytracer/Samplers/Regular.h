#ifndef _REGULAR_MINE_
#define _REGULAR_MINE_

#include "Sampler.h"

class Regular: public Sampler {

 public:
  Regular();
  Regular(const int);
  Regular(const Regular&);
  virtual const char* to_string();
  virtual Regular* clone() const;
  virtual ~Regular();
 private:
  virtual void generate_samples();
};

#endif // _REGULAR_MINE_
