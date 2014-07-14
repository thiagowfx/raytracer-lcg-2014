#ifndef _MATERIAL_MINE_
#define _MATERIAL_MINE_

#include "Utilities.h"
#include "RGBColor.h"
#include "ShadeRec.h"
#include <Eigen/Dense>
using Eigen::Vector3d;

namespace Raytracer {
  /**
   * @brief A material for a geometric object. Its shade function is different for each type of material.
   */
  class Material {
  public:
    Material();
    virtual ~Material();
    Material(const Material&);
    virtual Material* clone() const = 0;
    virtual RGBColor get_color() const = 0;
    virtual RGBColor shade(ShadeRec& sr) = 0;

    virtual RGBColor path_shade(ShadeRec& sr);
    virtual RGBColor area_light_shade(ShadeRec& sr);
    virtual RGBColor get_Le(ShadeRec& sr) const; /* for emissive materials */
  };
}

#endif // _MATERIAL_MINE_
