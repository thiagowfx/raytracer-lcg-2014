#include "Regular.h"

Regular::Regular() :
  Sampler()
{}


Regular::Regular(const int number_of_samples) :
  Sampler(number_of_samples) {
  generate_samples();
}


Regular::Regular(const Regular& u) :
  Sampler(u) {
  generate_samples();
}


const char* Regular::to_string() {
  return "Regular";
}


Regular* Regular::clone() const {
  return new Regular(*this);
}


Regular::~Regular() {}


void Regular::generate_samples() {
  unsigned n = sqrt(number_of_samples);
  for (unsigned j = 0; j < number_of_sets; j++)
    for (unsigned p = 0; p < n; p++)
      for (unsigned q = 0; q < n; q++)
        samples.push_back(Vector2d((q + 0.5) / n, (p + 0.5) / n));
}
