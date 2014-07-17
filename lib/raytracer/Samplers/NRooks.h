#ifndef _NROOKS_MINE_
#define _NROOKS_MINE_

#include "Sampler.h"

namespace Raytracer {
  /**
   * @brief A NRooks sampler generates only one sampler per line and column, in a scheme compared to placing rooks in a chess board.
   */
  class NRooks: public Sampler {
  public:
    NRooks();
    NRooks(const int);
    NRooks(const NRooks&);
    virtual const char* to_string();
    virtual NRooks* clone() const;
    virtual ~NRooks();
  private:
    virtual void generate_samples();
  };
}

#endif // _NROOKS_MINE_
