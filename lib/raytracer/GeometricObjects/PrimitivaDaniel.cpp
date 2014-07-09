#include "PrimitivaDaniel.h"

namespace Raytracer {
  PrimitivaDaniel::PrimitivaDaniel(Primitive* p) :
    GeometricObject(),
    primitive(p)
  {}

  PrimitivaDaniel::PrimitivaDaniel(const PrimitivaDaniel& pd) :
    GeometricObject(pd),
    primitive(NULL) {
    /*
      if(primitive)
      primitive = pd.primitive->clone();
    */
  }


  PrimitivaDaniel::~PrimitivaDaniel() {
    if (primitive) {
      delete primitive;
      primitive = NULL;
    }
  }

  PrimitivaDaniel *PrimitivaDaniel::clone() const {
    return new PrimitivaDaniel(*this);
  }

  bool PrimitivaDaniel::hit(const Ray_t& type, const Ray& ray, double& tmin, ShadeRec& sr) const {
    if (type == SHADOW_RAY && !shadows)
      return false;

    Vector3d intersectionPoint;
    Vector3d intersectionNormal;

    if ( primitive->rayIntersection(ray.origin, ray.direction, intersectionPoint, intersectionNormal) ) {
      tmin = (intersectionPoint - ray.origin).norm();

      if (tmin > kEpsilonShadows) {
        if (type == PRIMARY_RAY) {
          sr.normal = intersectionNormal;
          sr.local_hit_point = intersectionPoint;
        }
        return true;
      }
    }
    return false;
  }


  vector<PrimitivaDaniel*> PrimitivaDaniel::generic(const char *path_to_shape) {
    vector<PrimitivaDaniel*> pds;

    puts("INFO: begin build PrimitivaDaniel::dummy");
    vector<Primitive*> primitives;
    vector<Shape*> candidates;
    double epsilon = 0.05;
    double alpha = 10;
    double tao = 50;
    double pt = 0.99;
    int k = 3;
    int r = 100;
    int maxElements = 30;
    int maxLevel = 10;
    int option = -1;
    int option2 = -1;
    PCShapeDetection littlePCSD;
    if (path_to_shape == 0) {
      puts("ERROR: No primitives file set.");
      exit(1);
    }
    ifstream data(path_to_shape);
    double x,y,z;
    double nx, ny, nz;
    vector<Point> points;
    vector<Point> normals;
    while (data >> x >> y >> z) {
      Point newPoint(x,y,z);
      data >> nx >> ny >> nz;
      Point newNormal(nx, ny, nz);
      points.push_back(newPoint);
      normals.push_back(newNormal);
      Element newElement;
      newElement.location = newPoint;
      newElement.normal = newNormal;
    }
    littlePCSD.set(points, normals, k, epsilon, tao, pt, alpha,r, maxElements,maxLevel);
    littlePCSD.detect(true); // let this be TRUE
    primitives = littlePCSD.getPrimitives();
    candidates = littlePCSD.getCandidates();
    cout << "Number of primitives: " << primitives.size() << endl;
    cout << "Number of candidates: " << candidates.size() << endl;
    for (unsigned int i = 0; i < primitives.size(); ++i)
      pds.push_back(new PrimitivaDaniel(primitives[i]));
    puts("INFO: end build PrimitivaDaniel::dummy");

    return pds;
  }
}
