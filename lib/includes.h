#ifndef __MAIN__
#define __MAIN__

#include <Eigen/Dense>
using Eigen::Vector3d;

/* RAYTRACER */
#include "Ambient.h"
#include "AmbientOccluder.h"
#include "AreaLight.h"
#include "AreaLighting.h"
#include "Camera.h"
#include "Directional.h"
#include "Emissive.h"
#include "GeometricObject.h"
#include "Jittered.h"
#include "Light.h"
#include "Material.h"
#include "Matte.h"
#include "MultiJittered.h"
#include "MultipleObjects.h"
#include "Orthographic.h"
#include "Phong.h"
#include "Pinhole.h"
#include "PointLight.h"
#include "RGBColor.h"
#include "Ray.h"
#include "Raytracer.h"
#include "RaytracerPlane.h"
#include "RaytracerSphere.h"
#include "Rectangle.h"
#include "Reflective.h"
#include "Regular.h"
#include "ShadeRec.h"
#include "Tracer.h"
#include "Triangle.h"
#include "ViewPlane.h"
#include "Whitted.h"
#include "World.h"

#include <cstdio>
#include <cmath>
#include <QColor>
#include <QString>

#include "PrimitivaDaniel.h"
#include "pc-shape-detection.h"

#endif