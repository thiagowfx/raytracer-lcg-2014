#ifndef __MAIN__
#define __MAIN__

#include <Eigen/Dense>
using Eigen::Vector3d;

/* RAYTRACER */
#include "Ambient.h"
#include "Camera.h"
#include "Constants.h"
#include "Directional.h"
#include "FishEye.h"
#include "GeometricObject.h"
#include "Light.h"
#include "Material.h"
#include "Matte.h"
#include "MultipleObjects.h"
#include "Orthographic.h"
#include "Phong.h"
#include "Pinhole.h"
#include "PointLight.h"
#include "PrimitivaDaniel.h"
#include "RGBColor.h"
#include "Randomness.h"
#include "Ray.h"
#include "RayCast.h"
#include "Raytracer.h"
#include "RaytracerPlane.h"
#include "RaytracerSphere.h"
#include "Reflective.h"
#include "Regular.h"
#include "ShadeRec.h"
#include "Spherical.h"
#include "Tracer.h"
#include "Triangle.h"
#include "ViewPlane.h"
#include "World.h"

/* PCS_DETECTION */
#include "pc-shape-detection.h"

#endif
