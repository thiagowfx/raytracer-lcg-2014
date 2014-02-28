#include "Regular.h"

Regular::Regular() : Sampler() {}


Regular::Regular(const int num) :
  Sampler(num) 
{
  generate_samples();
}


Regular::Regular(const Regular& u) :
  Sampler(u)
{
  generate_samples();
}


Regular& Regular::operator= (const Regular& rhs) {
  if (this != &rhs) {
    Sampler::operator= (rhs);
  }

  return *this;
}


Regular* Regular::clone() const {
  return new Regular(*this);
}


Regular::~Regular() {}


void Regular::generate_samples() {
  int n = (int) sqrt((float)num_samples);

  for (int j = 0; j < num_sets; j++)
    for (int p = 0; p < n; p++)		
      for (int q = 0; q < n; q++)
        samples.push_back(Vector2d((q + 0.5) / n, (p + 0.5) / n));
}
