#ifndef _PURERANDOM_MINE_
#define _PURERANDOM_MINE_

#include "Sampler.h"

namespace Raytracer {
  /**
   * @brief A PureRandom sampler generates all samples randomly.
   */
  class PureRandom: public Sampler {
  public:
    PureRandom();
    PureRandom(const int);
    PureRandom(const PureRandom&);
    virtual const char* to_string();
    virtual PureRandom* clone() const;
    virtual ~PureRandom();
  private:
    virtual void generate_samples();
  };
}

#endif // _PURERANDOM_MINE_
