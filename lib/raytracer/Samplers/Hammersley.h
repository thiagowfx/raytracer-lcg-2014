#ifndef __HAMMERSLEY__
#define __HAMMERSLEY__

#include "Sampler.h"

class Hammersley: public Sampler {

 public:
  Hammersley();
  Hammersley(const int num);
  Hammersley(const Hammersley& r);
  Hammersley& operator= (const Hammersley& rhs);
  virtual Hammersley* clone() const;
  virtual ~Hammersley();
  double phi(int j);

 private:
  virtual void generate_samples();

};

#endif
