#ifndef _JITTERED_MINE_
#define _JITTERED_MINE_

#include "Sampler.h"

class Jittered: public Sampler {
 public:
  Jittered();
  Jittered(const int);
  Jittered(const int num_samples, const int m);
  Jittered(const Jittered&);
  virtual Jittered* clone() const;
  virtual ~Jittered();

 private:
  virtual void generate_samples();
};

#endif // _JITTERED_MINE_
