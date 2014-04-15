#include "MultiJittered.h"


MultiJittered::MultiJittered() :
  Sampler()
{}


MultiJittered::MultiJittered(const int num_samples) :
  Sampler(num_samples)
{
  //    count = 0;
  //    jump = 0;
  generate_samples();
}


MultiJittered::MultiJittered(const int num_samples, const int m) :
  Sampler(num_samples, m)
{
  generate_samples();
}


MultiJittered::MultiJittered(const MultiJittered& mjs) :
  Sampler(mjs)
{
  generate_samples();
}


MultiJittered& MultiJittered::operator= (const MultiJittered& rhs) {
  if (this != &rhs) {
    Sampler::operator=(rhs);
  }

  return *this;
}


MultiJittered* MultiJittered::clone() const {
  return new MultiJittered(*this);
}


MultiJittered::~MultiJittered() {}


/*

  void
  MultiJittered::shuffle_x_coordinates() {
  for (int p = 0; p < num_sets; p++) {
  for (int i = 0; i < n; i++)
  for (int j = 0; j < n; j++) {
  int k = rand_int(j, n - 1);
  double t = samples[i * n + j + p * num_samples](0);
  samples[i * n + j + p * num_samples](0) = samples[i * n + k + p * num_samples](0);
  samples[i * n + k + p * num_samples](0) = t;
  }
  }
  }

*/


// ---------------------------------------------------------------- generate_samples

// This is based on code in Chui et al. (1994), cited in the references
// The overloaded functions rand_int and rand_double (called from rand_int), which take arguments,
// are defined in Maths.h
// They should be defined here, as this is the only place they are usedm but I couldn't get them to compile

void MultiJittered::generate_samples() {
  // num_samples needs to be a perfect square

  int n = (int)sqrt((double)num_samples);
  double subcell_width = 1.0 / ((double) num_samples);

  // fill the samples array with dummy points to allow us to use the [ ] notation when we set the
  // initial patterns

  Vector2d fill_point;
  for (int j = 0; j < num_samples * num_sets; j++)
    samples.push_back(fill_point);

  // distribute points in the initial patterns

  for (int p = 0; p < num_sets; p++)
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++) {
        samples[i * n + j + p * num_samples](0) = (i * n + j) * subcell_width + rand_double(0, subcell_width);
        samples[i * n + j + p * num_samples](1) = (j * n + i) * subcell_width + rand_double(0, subcell_width);
      }

  // shuffle x coordinates

  for (int p = 0; p < num_sets; p++)
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++) {
        int k = rand_int(j, n - 1);
        double t = samples[i * n + j + p * num_samples](0);
        samples[i * n + j + p * num_samples](0) = samples[i * n + k + p * num_samples](0);
        samples[i * n + k + p * num_samples](0) = t;
      }

  // shuffle y coordinates

  for (int p = 0; p < num_sets; p++)
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++) {
        int k = rand_int(j, n - 1);
        double t = samples[j * n + i + p * num_samples](1);
        samples[j * n + i + p * num_samples](1) = samples[k * n + i + p * num_samples](1);
        samples[k * n + i + p * num_samples](1) = t;
      }
}
