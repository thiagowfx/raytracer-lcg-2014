#include "NRooks.h"

NRooks::NRooks()
  : Sampler()
{}


NRooks::NRooks(const int num_samples) :
  Sampler(num_samples)
{
  generate_samples();
}


NRooks::NRooks(const int num_samples, const int m) :
  Sampler(num_samples, m)
{
  generate_samples();
}


NRooks::NRooks(const NRooks& nr) :
  Sampler(nr)
{
  generate_samples();
}


NRooks& NRooks::operator= (const NRooks& rhs) {
  if (this != &rhs) {
    Sampler::operator=(rhs);
  }

  return *this;
}


NRooks* NRooks::clone() const {
  return new NRooks(*this);
}


NRooks::~NRooks() {}


void NRooks::generate_samples() {
  for (int p = 0; p < num_sets; p++)
    for (int j = 0; j < num_samples; j++) {
      Vector2d sp((j + rand_double()) / num_samples, (j + rand_double()) / num_samples);
      samples.push_back(sp);
    }

  shuffle_x_coordinates();
  shuffle_y_coordinates();
}
