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

namespace Raytracer {
  class Sampler {
  public:
    Sampler();
    /** Create a sampler with the given number of samples. */
    Sampler(const int number_of_samples);
    /** Create a sampler with the given number of samples and sets. */
    Sampler(const int number_of_samples, const int number_of_sets);
    Sampler(const Sampler&);
    virtual Sampler* clone() const = 0;
    virtual ~Sampler();

    /** Return a string with the class name */
    virtual const char* to_string() = 0;

    /** Return the number of samples. */
    int get_number_of_samples();

    /** Shuffle the x coordinates of the points within each set. */
    void shuffle_x_coordinates();

    /** Shuffle the y coordinates of the points within set. */
    void shuffle_y_coordinates();

    /** Sets up randomly shuffled indices for the samples array. */
    void setup_shuffled_indices();

    /** Generate sample patterns in a unit square. */
    virtual void generate_samples() = 0;

    /** Get next sample on unit square. */
    Vector2d sample_unit_square();

    /** Maps the 2D sample points in the square [-1,1] X [-1,1] to a unit disk, using Peter Shirley's concentric map function. */
    void map_samples_to_unit_disk();

    /** Get next sample on unit disk. */
    Vector2d sample_unit_disk();

    /** Maps the 2D sample points to 3D points on a unit hemisphere with a cosine power density distribution in the polar angle. */
    void map_samples_to_hemisphere(const double p);

    /** Get next sample on unit hemisphere. */
    Vector3d sample_hemisphere();

    /** Maps the 2D sample points to 3D points on a unit sphere with a uniform density distribution over the surface -- this is used for modelling a spherical light. */
    void map_samples_to_sphere();

    /** Get next sample on unit sphere. */
    Vector3d sample_sphere();

    /** Only used to set up a vector noise table -- not actually discussed in the book, but see the file LatticeNoise.cpp in Chapter 31. */
    Vector2d sample_one_set();

  protected:
    /** Number of sample points in a set */
    unsigned number_of_samples = 1;

    /** Number of sample sets */
    unsigned number_of_sets = 100;

    /** Current number of sample points used */
    unsigned long count = 0;

    /** Random index jump. */
    int jump = 0;

    /** Sample points on a unit square */
    vector<Vector2d> samples;

    /** Shuffled samples array indices */
    vector<int> shuffled_indices;

    /** Sample points on a unit disk */
    vector<Vector2d> disk_samples;

    /** Sample points on a unit hemisphere */
    vector<Vector3d> hemisphere_samples;

    /** Sample points on a unit sphere */
    vector<Vector3d> sphere_samples;
  };
}

#endif // _SAMPLER_MINE_
