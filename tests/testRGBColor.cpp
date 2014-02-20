#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE testRGBColor
#include <boost/test/unit_test.hpp>

#include "Constants.h"
#include "RGBColor.h"
#include <cmath>

bool areNear(double a, double b) {
  return fabs(a - b) < kEpsilon;
}

BOOST_AUTO_TEST_CASE(testOperatorPlus) {
  RGBColor color1(0.1, 0.1, 0.1), color2(0.5, 0.5, 0.5);
  RGBColor color3 = color1 + color2;
  
  BOOST_CHECK( areNear(color3.r, 0.6) );
  BOOST_CHECK( areNear(color3.g, 0.6) );
  BOOST_CHECK( areNear(color3.b, 0.6) );
}

BOOST_AUTO_TEST_CASE(testOperatorPlusEqual) {
  RGBColor color1(0.1, 0.1, 0.1), color2(0.5, 0.5, 0.5);
  color1 += color2;
  
  BOOST_CHECK( areNear(color1.r, 0.6) );
  BOOST_CHECK( areNear(color1.g, 0.6) );
  BOOST_CHECK( areNear(color1.b, 0.6) );
}

BOOST_AUTO_TEST_CASE(testOneArgumentConstructor) {
  RGBColor color(0.5);
  
  BOOST_CHECK( areNear(color.r, 0.5) );
  BOOST_CHECK( areNear(color.g, 0.5) );
  BOOST_CHECK( areNear(color.b, 0.5) );
}

BOOST_AUTO_TEST_CASE(testAverage) {
  RGBColor color(0.1, 0.2, 0.3);
  BOOST_CHECK( areNear(color.average(), 0.2) );
}

BOOST_AUTO_TEST_CASE(testOperatorCompare) {
  RGBColor color1(0.1, 0.1, 0.1), color2(0.1, 0.1, 0.1);
  BOOST_CHECK( areNear(color1.r, color2.r) );
  BOOST_CHECK( areNear(color1.g, color2.g) );
  BOOST_CHECK( areNear(color1.b, color2.b) );
}

BOOST_AUTO_TEST_CASE(testPowc) {
  RGBColor color1(0.2, 0.2, 0.2);
  RGBColor color2 = color1.powc(2);

  BOOST_CHECK( areNear(color2.r, 0.04) );
  BOOST_CHECK( areNear(color2.g, 0.04) );
  BOOST_CHECK( areNear(color2.b, 0.04) );
}
