#ifndef _MATERIAL_MINE_
#define _MATERIAL_MINE_

#include "Utilities.h"
#include "RGBColor.h"
#include "ShadeRec.h"
#include <Eigen/Dense>
using Eigen::Vector3d;

namespace Raytracer {
  /**
   * @brief A material for a geometric object. Its shade function is
   * responsible for shading the correct color given a ShadeRec object
   * and it is different for each type of material.
   */
  class Material {
  public:
    Material();
    virtual ~Material();
    Material(const Material&);
    virtual Material* clone() const = 0;

    /** Return the main color of this material, necessary for the
	MultipleObjects tracer. Lights shouldn't be present in this
	calculation. */
    virtual RGBColor get_color() const = 0;
    /** How should the color of a point in a geometric object be computed? */
    virtual RGBColor shade(ShadeRec& sr) = 0;

    /** Required for area lights. */
    virtual RGBColor area_light_shade(ShadeRec& sr) = 0;
    /** Effective color (radiance * hue) emitted by this material. */
    virtual RGBColor get_Le(ShadeRec& sr) const;
  };
}

#endif // _MATERIAL_MINE_
