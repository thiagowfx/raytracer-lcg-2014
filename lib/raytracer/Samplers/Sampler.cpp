#include "Sampler.h"

namespace Raytracer {
  Sampler::Sampler() {
    samples.reserve(number_of_samples * number_of_sets);
    setup_shuffled_indices();
  }


  Sampler::Sampler(const int number_of_samples) :
    number_of_samples(number_of_samples) {
    samples.reserve(number_of_samples * number_of_sets);
    setup_shuffled_indices();
  }


  Sampler::Sampler(const int number_of_samples, const int number_of_sets) :
    number_of_samples(number_of_samples),
    number_of_sets(number_of_sets) {
    samples.reserve(number_of_samples * number_of_sets);
    setup_shuffled_indices();
  }


  Sampler::Sampler(const Sampler& s) :
    number_of_samples(s.number_of_samples),
    number_of_sets(s.number_of_sets),
    samples(s.samples),
    shuffled_indices(s.shuffled_indices),
    disk_samples(s.disk_samples),
    hemisphere_samples(s.hemisphere_samples),
    sphere_samples(s.sphere_samples),
    count(s.count),
    jump(s.jump)
  {}


  Sampler::~Sampler() {}


  int Sampler::get_number_of_samples() {
    return number_of_samples;
  }


  void Sampler::shuffle_x_coordinates() {
    for (unsigned p = 0; p < number_of_sets; p++)
      for (unsigned i = 0; i < number_of_samples - 1; i++) {
        int target = get_random_int() % number_of_samples + p * number_of_samples;
        double temp = samples[i + p * number_of_samples + 1](0);
        samples[i + p * number_of_samples + 1](0) = samples[target](0);
        samples[target](0) = temp;
      }
  }


  void Sampler::shuffle_y_coordinates() {
    for (unsigned p = 0; p < number_of_sets; p++)
      for (unsigned i = 0; i <  number_of_samples - 1; i++) {
        int target = get_random_int() % number_of_samples + p * number_of_samples;
        double temp = samples[i + p * number_of_samples + 1](1);
        samples[i + p * number_of_samples + 1](1) = samples[target](1);
        samples[target](1) = temp;
      }
  }


  void Sampler::setup_shuffled_indices() {
    shuffled_indices.reserve(number_of_samples * number_of_sets);
    std::vector<int> indices;
    for (unsigned j = 0; j < number_of_samples; j++)
      indices.push_back(j);
    for (unsigned p = 0; p < number_of_sets; p++) {
      random_shuffle(indices.begin(), indices.end());
      for (unsigned j = 0; j < number_of_samples; j++)
        shuffled_indices.push_back(indices[j]);
    }
  }


  void Sampler::map_samples_to_unit_disk() {
    unsigned size = samples.size();
    double r, phi;                 // polar coordinates
    Vector2d sp; ///< sample point on unit disk
    disk_samples.reserve(size);
    for (unsigned j = 0; j < size; j++) {
      /* map sample point to [-1, 1] X [-1,1] */
      sp(0) = 2.0 * samples[j](0) - 1.0;
      sp(1) = 2.0 * samples[j](1) - 1.0;
      if (sp(0) > -sp(1)) {         // sectors 1 and 2
        if (sp(0) > sp(1)) {        // sector 1
          r = sp(0);
          phi = sp(1) / sp(0);
        }
        else {                    // sector 2
          r = sp(1);
          phi = 2.0 - sp(0) / sp(1);
        }
      }
      else {                      // sectors 3 and 4
        if (sp(0) < sp(1)) {        // sector 3
          r = -sp(0);
          phi = 4.0 + sp(1) / sp(0);
        }
        else {                    // sector 4
          r = -sp(1);
          if (sp(1) != 0.0)       // avoid division by zero at origin
            phi = 6.0 - sp(0) / sp(1);
          else
            phi  = 0.0;
        }
      }
      phi *= M_PI / 4.0;
      disk_samples[j](0) = r * cos(phi);
      disk_samples[j](1) = r * sin(phi);
    }
    samples.erase(samples.begin(), samples.end());
  }


  void Sampler::map_samples_to_hemisphere(const double exp) {
    unsigned size = samples.size();
    hemisphere_samples.reserve(number_of_samples * number_of_sets);
    for (int j = 0; j < size; j++) {
      double cos_phi = cos(TWO_PI * samples[j](0));
      double sin_phi = sin(TWO_PI * samples[j](0));
      double cos_theta = pow((1.0 - samples[j](1)), 1.0 / (exp + 1.0));
      double sin_theta = sqrt (1.0 - cos_theta * cos_theta);
      double pu = sin_theta * cos_phi;
      double pv = sin_theta * sin_phi;
      double pw = cos_theta;
      hemisphere_samples.push_back(Vector3d(pu, pv, pw));
    }
  }


  void Sampler::map_samples_to_sphere() {
    double r1, r2;
    double x, y, z;
    double r, phi;
    sphere_samples.reserve(number_of_samples * number_of_sets);
    for (int j = 0; j < number_of_samples * number_of_sets; j++) {
      r1  = samples[j](0);
      r2  = samples[j](1);
      z   = 1.0 - 2.0 * r1;
      r   = sqrt(1.0 - z * z);
      phi = TWO_PI * r2;
      x   = r * cos(phi);
      y   = r * sin(phi);
      sphere_samples.push_back(Vector3d(x, y, z));
    }
  }


  Vector2d Sampler::sample_unit_square() {
    if (count % number_of_samples == 0) // start of a new pixel
      jump = (get_random_int() % number_of_sets) * number_of_samples; // random index jump initialised to zero in constructor
    return (samples[jump + shuffled_indices[jump + count++ % number_of_samples]]);
  }


  Vector2d Sampler::sample_unit_disk() {
    if (count % number_of_samples == 0) // start of a new pixel
      jump = (get_random_int() % number_of_sets) * number_of_samples;
    return (disk_samples[jump + shuffled_indices[jump + count++ % number_of_samples]]);
  }


  Vector3d Sampler::sample_hemisphere() {
    if (count % number_of_samples == 0) // start of a new pixel
      jump = (get_random_int() % number_of_sets) * number_of_samples;
    return (hemisphere_samples[jump + shuffled_indices[jump + count++ % number_of_samples]]);
  }


  Vector3d Sampler::sample_sphere() {
    if (count % number_of_samples == 0) // start of a new pixel
      jump = (get_random_int() % number_of_sets) * number_of_samples;
    return (sphere_samples[jump + shuffled_indices[jump + count++ % number_of_samples]]);
  }


  Vector2d Sampler::sample_one_set() {
    return(samples[count++ % number_of_samples]);
  }
}
