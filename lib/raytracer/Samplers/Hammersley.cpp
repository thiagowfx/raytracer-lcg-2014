#include "Hammersley.h"

Hammersley::Hammersley() :
  Sampler()
{}


Hammersley::Hammersley(const int num) :
  Sampler(num)
{
  generate_samples();
}


Hammersley::Hammersley(const Hammersley& h) :
  Sampler(h)
{
  generate_samples();
}


Hammersley* Hammersley::clone() const {
  return new Hammersley(*this);
}


Hammersley::~Hammersley() {}


double Hammersley::phi(int j) {
  double x = 0.0;
  double f = 0.5;
  while (j) {
    x += f * double(j & 1);
    j /= 2;
    f *= 0.5;
  }
  return x;
}


void Hammersley::generate_samples() {
  for (unsigned p = 0; p < num_sets; p++) {
    for (unsigned j = 0; j < num_samples; j++) {
      Vector2d pv((double) j / (double) num_samples, phi(j));
      samples.push_back(pv);
    }
  }
}
