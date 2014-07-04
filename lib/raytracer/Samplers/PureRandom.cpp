#include "PureRandom.h"

PureRandom::PureRandom() :
  Sampler()
{}


PureRandom::PureRandom(const int num) :
  Sampler(num) {
  generate_samples();
}


PureRandom::PureRandom(const PureRandom& r)  :
  Sampler(r) {
  generate_samples();
}


const char* PureRandom::to_string() {
  return "PureRandom";
}


PureRandom* PureRandom::clone() const {
  return new PureRandom(*this);
}


PureRandom::~PureRandom() {}


void PureRandom::generate_samples() {
  for (unsigned p = 0; p < num_sets; p++)
    for (unsigned q = 0; q < num_samples; q++)
      samples.push_back(Vector2d(get_random_double(), get_random_double()));
}
