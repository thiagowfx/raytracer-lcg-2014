#include "MultiJittered.h"

namespace Raytracer {
  MultiJittered::MultiJittered() :
    Sampler()
  {}


  MultiJittered::MultiJittered(const int number_of_samples) :
    Sampler(number_of_samples) {
    generate_samples();
  }


  MultiJittered::MultiJittered(const MultiJittered& m) :
    Sampler(m) {
    generate_samples();
  }


  const char* MultiJittered::to_string() {
    return "MultiJittered";
  }


  MultiJittered* MultiJittered::clone() const {
    return new MultiJittered(*this);
  }


  MultiJittered::~MultiJittered() {}


  // This is based on code in Chui et al. (1994), cited in the references
  // The overloaded functions get_random_int and get_random_double (called from get_random_int), which take arguments,
  // are defined in Maths.h
  // They should be defined here, as this is the only place they are usedm but I couldn't get them to compile

  void MultiJittered::generate_samples() {
    // number_of_samples needs to be a perfect square

    const unsigned n = (int)sqrt((double)number_of_samples);
    double subcell_width = 1.0 / ((double) number_of_samples);

    // fill the samples array with dummy points to allow us to use the [ ] notation when we set the
    // initial patterns

    Vector2d fill_point;
    for (int j = 0; j < number_of_samples * number_of_sets; j++) {
      samples.push_back(fill_point);
    }

    // distribute points in the initial patterns
    for (int p = 0; p < number_of_sets; p++) {
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          samples[i * n + j + p * number_of_samples](0) = (i * n + j) * subcell_width + get_random_double(0, subcell_width);
          samples[i * n + j + p * number_of_samples](1) = (j * n + i) * subcell_width + get_random_double(0, subcell_width);
        }
      }
    }

    // shuffle x coordinates
    for (int p = 0; p < number_of_sets; p++) {
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          int k = get_random_int(j, n - 1);
          double t = samples[i * n + j + p * number_of_samples](0);
          samples[i * n + j + p * number_of_samples](0) = samples[i * n + k + p * number_of_samples](0);
          samples[i * n + k + p * number_of_samples](0) = t;
        }
      }
    }

    // shuffle y coordinates
    for (int p = 0; p < number_of_sets; p++) {
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          int k = get_random_int(j, n - 1);
          double t = samples[j * n + i + p * number_of_samples](1);
          samples[j * n + i + p * number_of_samples](1) = samples[k * n + i + p * number_of_samples](1);
          samples[k * n + i + p * number_of_samples](1) = t;
        }
      }
    }
  }
}
