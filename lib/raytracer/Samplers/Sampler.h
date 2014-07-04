#ifndef _SAMPLER_MINE_
#define _SAMPLER_MINE_

#include "Utilities.h"
#include <Eigen/Dense>
#include <algorithm> // for random_shuffle in Sampler::setup_shuffled_indices
#include <cmath>
#include <vector>
using Eigen::Vector2d;
using Eigen::Vector3d;
using namespace std;

class Sampler {

 public:
  Sampler();
  Sampler(const int num);
  Sampler(const int num, const int num_sets);
  Sampler(const Sampler& s);
  virtual const char* to_string() = 0; /**> Return a string with the class name */
  virtual Sampler* clone() const = 0;
  virtual ~Sampler();
  int get_number_of_samples();

  void shuffle_x_coordinates(); /**> shuffle the x coordinates of the points within each set */
  void shuffle_y_coordinates(); /**> shuffle the y coordinates of the points within set */
  void setup_shuffled_indices(); /**> sets up randomly shuffled indices for the samples array */

  virtual void generate_samples() = 0; /**> Generate sample patterns in a unit square */
  Vector2d sample_unit_square(); /**> Get next sample on unit square */

  void map_samples_to_unit_disk(); /**> Maps the 2D sample points in the square [-1,1] X [-1,1] to a unit disk, using Peter Shirley's concentric map function */
  Vector2d sample_unit_disk();   /**> Get next sample on unit disk */

  void map_samples_to_hemisphere(const double p); /**> Maps the 2D sample points to 3D points on a unit hemisphere with a cosine power density distribution in the polar angle */
  Vector3d sample_hemisphere();  /**> Get next sample on unit hemisphere */

  void map_samples_to_sphere(); /**> Maps the 2D sample points to 3D points on a unit sphere with a uniform density distribution over the surface -- this is used for modelling a spherical light */
  Vector3d sample_sphere();      /**> Get next sample on unit sphere */

  Vector2d sample_one_set(); /**> Only used to set up a vector noise table -- Not actually discussed in the book, but see the file LatticeNoise.cpp in Chapter 31 */

 protected:
  unsigned num_samples = 1; /**> Number of sample points in a set */
  unsigned num_sets = 83; /**> Number of sample sets */
  unsigned long count = 0; /**> Current number of sample points used */
  int jump = 0; /**> Random index jump. */
  vector<Vector2d> samples; /**> Sample points on a unit square */
  vector<int> shuffled_indices; /**> Shuffled samples array indices */
  vector<Vector2d> disk_samples; /**> Sample points on a unit disk */
  vector<Vector3d> hemisphere_samples; /**> Sample points on a unit hemisphere */
  vector<Vector3d> sphere_samples; /**> Sample points on a unit sphere */
};

#endif // _SAMPLER_MINE_
