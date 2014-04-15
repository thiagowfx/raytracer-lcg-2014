#ifndef __SAMPLER__
#define __SAMPLER__

#include "Constants.h"
#include "Randomness.h"
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
  Sampler& operator= (const Sampler& rhs); 
  virtual Sampler* clone() const = 0; 
  virtual ~Sampler(); 
  void set_num_sets(const int np); 
  virtual void generate_samples() = 0; // generate sample patterns in a unit square 
  int get_num_samples(); 
  void shuffle_x_coordinates(); // shuffle the x coordinates of the points within each set 
  void shuffle_y_coordinates(); // shuffle the y coordinates of the points within set
  void setup_shuffled_indices(); // sets up randomly shuffled indices for the samples array
  void map_samples_to_unit_disk(); // maps the 2D sample points in the square [-1,1] X [-1,1] to a unit disk, using Peter Shirley's concentric map function
  void map_samples_to_hemisphere(const double p); // Maps the 2D sample points to 3D points on a unit hemisphere with a cosine power density distribution in the polar angle
  void map_samples_to_sphere(); // Maps the 2D sample points to 3D points on a unit sphere with a uniform density distribution over the surface -- this is used for modelling a spherical light
		
  /* the following functions are not const because they change count and jump */
  Vector2d sample_unit_square(); // get next sample on unit square
  Vector2d sample_unit_disk();   // get next sample on unit disk
  Vector3d sample_hemisphere();  // get next sample on unit hemisphere
  Vector3d sample_sphere();      // get next sample on unit sphere
  Vector2d sample_one_set(); // only used to set up a vector noise table -- this is not discussed in the book, but see the file LatticeNoise.cpp in Chapter 31
  
 protected:
  int              num_samples; // the number of sample points in a set
  int              num_sets;    // the number of sample sets
  vector<Vector2d> samples;     // sample points on a unit square
  vector<int>      shuffled_indices; // shuffled samples array indices
  vector<Vector2d> disk_samples; // sample points on a unit disk
  vector<Vector3d> hemisphere_samples; // sample points on a unit hemisphere
  vector<Vector3d> sphere_samples; // sample points on a unit sphere
  unsigned long    count;       // the current number of sample points used
  int              jump;        // random index jump
};


#endif
