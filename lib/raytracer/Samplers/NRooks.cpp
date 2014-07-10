#include "NRooks.h"

NRooks::NRooks()
  : Sampler()
{}


NRooks::NRooks(const int number_of_samples) :
  Sampler(number_of_samples) {
  generate_samples();
}


const char* NRooks::to_string() {
  return "NRooks";
}


NRooks::NRooks(const NRooks& nr) :
  Sampler(nr) {
  generate_samples();
}


NRooks* NRooks::clone() const {
  return new NRooks(*this);
}


NRooks::~NRooks() {}


void NRooks::generate_samples() {
  for (unsigned p = 0; p < number_of_sets; p++)
    for (unsigned j = 0; j < number_of_samples; j++) {
      Vector2d sp((j + get_random_double()) / number_of_samples, (j + get_random_double()) / number_of_samples);
      samples.push_back(sp);
    }
  shuffle_x_coordinates();
  shuffle_y_coordinates();
}
