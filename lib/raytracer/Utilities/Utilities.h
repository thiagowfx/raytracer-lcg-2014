#ifndef __UTILITIES__
#define __UTILITIES__

#include <cstdlib>
#include "RGBColor.h"

const double kEpsilonShadows = 1.0e-3;
const double kEpsilon        = 1.0e-5;
const double kHugeValue      = 1.0e10;

const double kKa = 0.20; /** ambient constant */
const double kKd = 0.80; /** diffuse constant */
const double kKs = 0.12; /** specular constant */
const double kExp = 10.0; /** exponent for specular */
const double kKr = 0.75; /** reflective constant */

const RGBColor black(0.0, 0.0, 0.0);
const RGBColor brown(0.71, 0.40, 0.16);
const RGBColor light_grey(0.6, 0.6, 0.6);
const RGBColor light_gray(light_grey);
const RGBColor grey(0.3, 0.3, 0.3);
const RGBColor gray(grey);
const RGBColor white(1.0, 1.0, 1.0);
const RGBColor red(1.0, 0.0, 0.0);
const RGBColor green(0.0, 1.0, 0.0);
const RGBColor light_green(0.65, 1.0, 0.30);
const RGBColor dark_green(0.0, 0.41, 0.41);
const RGBColor blue(0.0, 0.0, 1.0);
const RGBColor light_purple(0.65, 0.3, 1.0);
const RGBColor dark_purple(0.5, 0.0, 1);
const RGBColor yellow(1.0, 1.0, 0.0);
const RGBColor dark_yellow(0.61, 0.61, 0.0);
const RGBColor orange(1.0, 0.75, 0.0);

void set_rand_seed(int);
int rand_int();                               /** Return a random integer from 0 to RAND_MAX */
int rand_int(int begin, int end);             /** Return a random integer from begin to end */
double rand_double();                         /** Return a random double from 0.0 to 1.0 */
double rand_double(double begin, double end); /** Return a random double from begin to end */

#endif
