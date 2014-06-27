#include "PureRandom.h"

PureRandom::PureRandom() :
  Sampler()
{}


PureRandom::PureRandom(const int num) :
  Sampler(num)
{
  generate_samples();
}


PureRandom::PureRandom(const PureRandom& r)  :
  Sampler(r)
{
  generate_samples();
}


PureRandom& PureRandom::operator= (const PureRandom& rhs) {
  if (this != &rhs) {
    Sampler::operator=(rhs);
  }

  return *this;
}


PureRandom* PureRandom::clone() const {
  return new PureRandom(*this);
}


PureRandom::~PureRandom() {}


void PureRandom::generate_samples() {
  for (int p = 0; p < num_sets; p++)
    for (int q = 0; q < num_samples; q++)
      samples.push_back(Vector2d(rand_double(), rand_double()));
}
