#ifndef __CONSTANTS__
#define __CONSTANTS__

#include <cmath>
#include <stdlib.h>
#include "RGBColor.h"

const double PI          = M_PI;
const double TWO_PI      = 2 * M_PI;
const double invPI       = 1 / M_PI;
const double invTWO_PI   = invPI / 2.0;
const double kEpsilon    = 1.0e-4;
const double kHugeValue  = 1.0e10;
const double invRAND_MAX = 1.0 / double(RAND_MAX);

const RGBColor black(0.0, 0.0, 0.0);
const RGBColor white(1.0, 1.0, 1.0);
const RGBColor blue(0.0, 0.0, 1.0);
const RGBColor red(1.0, 0.0, 0.0);
const RGBColor brown(0.71, 0.40, 0.16);
const RGBColor light_green(0.65, 1.0, 0.30);
const RGBColor green(0.0, 1.0, 0.0);
const RGBColor dark_green(0.0, 0.41, 0.41);
const RGBColor dark_purple(0.5, 0.0, 1);
const RGBColor dark_yellow(0.61, 0.61, 0.0);
const RGBColor light_grey(0.6, 0.6, 0.6);
const RGBColor light_gray(light_grey);
const RGBColor grey(0.3, 0.3, 0.3);
const RGBColor gray(grey);
const RGBColor light_purple(0.65, 0.3, 1.0);
const RGBColor orange(1.0, 0.75, 0.0);
const RGBColor yellow(1.0, 1.0, 0.0);

#endif
