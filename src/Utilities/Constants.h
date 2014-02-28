#ifndef __CONSTANTS__
#define __CONSTANTS__

#include <stdlib.h>
#include "RGBColor.h"

const double PI          = 3.1415926535897932384;
const double TWO_PI	 = 6.2831853071795864769;
const double PI_ON_180   = 0.0174532925199432957;
const double invPI	 = 0.3183098861837906715;
const double invTWO_PI   = 0.1591549430918953358;
const double kEpsilon    = 0.0001; 
const double kHugeValue  = 1.0e10;
const double invRAND_MAX = 1.0 / double(RAND_MAX);

const RGBColor black(0.0, 0.0, 0.0);
const RGBColor blue(0.0, 0.0, 1.0);
const RGBColor brown(0.71, 0.40, 0.16);
const RGBColor dark_green(0.0, 0.41, 0.41);
const RGBColor dark_purple(0.5, 0.0, 1);
const RGBColor dark_yellow(0.61, 0.61, 0.0);
const RGBColor green(0.0, 1.0, 0.0);
const RGBColor grey(0.25, 0.25, 0.25);
const RGBColor light_green(0.65, 1.0, 0.30);
const RGBColor light_purple(0.65, 0.3, 1.0);
const RGBColor orange(1.0, 0.75, 0.0);
const RGBColor red(1.0, 0.0, 0.0);
const RGBColor white(1.0, 1.0, 1.0);
const RGBColor yellow(1.0, 1.0, 0.0);

#endif
