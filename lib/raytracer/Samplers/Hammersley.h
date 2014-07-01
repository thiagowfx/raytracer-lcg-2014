#ifndef _HAMMERSLEY_MINE_
#define _HAMMERSLEY_MINE_

#include "Sampler.h"

class Hammersley: public Sampler {
 public:
  Hammersley();
  Hammersley(const int);
  Hammersley(const Hammersley&);
  virtual Hammersley* clone() const;
  virtual ~Hammersley();
  double phi(int);

 private:
  virtual void generate_samples();
};

#endif // _HAMMERSLEY_MINE_
