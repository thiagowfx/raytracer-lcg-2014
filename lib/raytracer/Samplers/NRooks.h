#ifndef _NROOKS_MINE_
#define _NROOKS_MINE_

#include "Sampler.h"

class NRooks: public Sampler {
 public:
  NRooks();
  NRooks(const int num_samples);
  NRooks(const int num_samples, const int m);
  NRooks(const NRooks& nr);
  virtual NRooks* clone() const;
  virtual ~NRooks();

 private:
  virtual void generate_samples();
};

#endif // _NROOKS_MINE_
