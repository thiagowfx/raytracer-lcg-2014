#ifndef _HAMMERSLEY_MINE_
#define _HAMMERSLEY_MINE_

#include "Sampler.h"

namespace Raytracer {
  class Hammersley: public Sampler {
  public:
    Hammersley();
    Hammersley(const int);
    Hammersley(const Hammersley&);
    virtual const char* to_string();
    virtual Hammersley* clone() const;
    virtual ~Hammersley();
  private:
    virtual void generate_samples();
    double phi(int);
  };
}

#endif // _HAMMERSLEY_MINE_
