#include "Sampler.h"

Sampler::Sampler() :
  num_sets(83)
{
  samples.reserve(num_samples * num_sets);
  setup_shuffled_indices();
}


Sampler::Sampler(const int ns) :
  num_samples(ns),
  num_sets(83),
  count(0),
  jump(0)
{
  samples.reserve(num_samples * num_sets);
  setup_shuffled_indices();
}


Sampler::Sampler(const int ns, const int n_sets) :
  num_samples(ns),
  num_sets(n_sets),
  count(0),
  jump(0)
{
  samples.reserve(num_samples * num_sets);
  setup_shuffled_indices();
}


Sampler::Sampler(const Sampler& s) :
  num_samples(s.num_samples),
  num_sets(s.num_sets),
  samples(s.samples),
  shuffled_indices(s.shuffled_indices),
  disk_samples(s.disk_samples),
  hemisphere_samples(s.hemisphere_samples),
  sphere_samples(s.sphere_samples),
  count(s.count),
  jump(s.jump)
{}


Sampler::~Sampler() {}


void Sampler::set_num_sets(const int np) {
  num_sets = np;
}


int Sampler::get_num_samples() {
  return num_samples;
}


void Sampler::shuffle_x_coordinates() {
  for (int p = 0; p < num_sets; p++)
    for (int i = 0; i <  num_samples - 1; i++) {
      int target = get_random_int() % num_samples + p * num_samples;
      double temp = samples[i + p * num_samples + 1](0);
      samples[i + p * num_samples + 1](0) = samples[target](0);
      samples[target](0) = temp;
    }
}


void Sampler::shuffle_y_coordinates() {
  for (int p = 0; p < num_sets; p++)
    for (int i = 0; i <  num_samples - 1; i++) {
      int target = get_random_int() % num_samples + p * num_samples;
      double temp = samples[i + p * num_samples + 1](1);
      samples[i + p * num_samples + 1](1) = samples[target](1);
      samples[target](1) = temp;
    }
}


void Sampler::setup_shuffled_indices() {
  shuffled_indices.reserve(num_samples * num_sets);
  vector<int> indices;

  for (int j = 0; j < num_samples; j++)
    indices.push_back(j);

  for (int p = 0; p < num_sets; p++) {
    random_shuffle(indices.begin(), indices.end());

    for (int j = 0; j < num_samples; j++)
      shuffled_indices.push_back(indices[j]);
  }
}


void Sampler::map_samples_to_unit_disk() {
  int size = samples.size();
  double r, phi;                 // polar coordinates
  Vector2d sp;                   // sample point on unit disk

  disk_samples.reserve(size);

  for (int j = 0; j < size; j++) {
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
        if (sp(1) != 0.0)	// avoid division by zero at origin
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
  int size = samples.size();
  hemisphere_samples.reserve(num_samples * num_sets);

  for (int j = 0; j < size; j++) {
    double cos_phi = cos(2.0 * M_PI * samples[j](0));
    double sin_phi = sin(2.0 * M_PI * samples[j](0));
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

  sphere_samples.reserve(num_samples * num_sets);

  for (int j = 0; j < num_samples * num_sets; j++) {
    r1 	= samples[j](0);
    r2 	= samples[j](1);
    z 	= 1.0 - 2.0 * r1;
    r 	= sqrt(1.0 - z * z);
    phi = (2 * M_PI) * r2;
    x 	= r * cos(phi);
    y 	= r * sin(phi);
    sphere_samples.push_back(Vector3d(x, y, z));
  }
}


Vector2d Sampler::sample_unit_square() {
  if (count % num_samples == 0) // start of a new pixel
    jump = (get_random_int() % num_sets) * num_samples; // random index jump initialised to zero in constructor

  return (samples[jump + shuffled_indices[jump + count++ % num_samples]]);
}


Vector2d Sampler::sample_unit_disk() {
  if (count % num_samples == 0) // start of a new pixel
    jump = (get_random_int() % num_sets) * num_samples;

  return (disk_samples[jump + shuffled_indices[jump + count++ % num_samples]]);
}


Vector3d Sampler::sample_hemisphere() {
  if (count % num_samples == 0) // start of a new pixel
    jump = (get_random_int() % num_sets) * num_samples;

  return (hemisphere_samples[jump + shuffled_indices[jump + count++ % num_samples]]);
}


Vector3d Sampler::sample_sphere() {
  if (count % num_samples == 0) // start of a new pixel
    jump = (get_random_int() % num_sets) * num_samples;

  return (sphere_samples[jump + shuffled_indices[jump + count++ % num_samples]]);
}


Vector2d Sampler::sample_one_set() {
  return(samples[count++ % num_samples]);
}
