#include "Jittered.h"

Jittered::Jittered() :
  Sampler()
{}


Jittered::Jittered(const int num_samples) :
  Sampler(num_samples) {
  generate_samples();
}


Jittered::Jittered(const int num_samples, const int m) :
  Sampler(num_samples, m) {
  generate_samples();
}


Jittered::Jittered(const Jittered& js) :
  Sampler(js) {
  generate_samples();
}


const char* Jittered::to_string() {
  return "Jittered";
}


Jittered* Jittered::clone(void) const {
  return new Jittered(*this);
}


Jittered::~Jittered(void) {}


void Jittered::generate_samples(void) {
  unsigned n = (unsigned) sqrt((double)num_samples);
  for (unsigned p = 0; p < num_sets; p++) {
    for (unsigned j = 0; j < n; j++) {
      for (unsigned k = 0; k < n; k++) {
        Vector2d sp((k + get_random_double()) / n, (j + get_random_double()) / n);
        samples.push_back(sp);
      }
    }
  }
}
