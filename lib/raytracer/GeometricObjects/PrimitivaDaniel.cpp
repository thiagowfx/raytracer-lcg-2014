#include "PrimitivaDaniel.h"

namespace Raytracer {
  PrimitivaDaniel::PrimitivaDaniel(Primitive* p) :
    GeometricObject(),
    primitive(p)
  {}


  PrimitivaDaniel::PrimitivaDaniel(const PrimitivaDaniel& p) :
    GeometricObject(p),
    primitive(NULL) {
    // if (p)
    //   primitive = p->clone();
    // else
    //   primitive = NULL;
  }


  PrimitivaDaniel::~PrimitivaDaniel() {
    if (primitive != NULL) {
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


  vector<PrimitivaDaniel*> PrimitivaDaniel::generic(const char *filename) {
    vector<PrimitivaDaniel*> pds;
    
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
    
    if (filename == 0) {
      puts("ERROR: No primitives file set.");
      exit(1);
    }
    ifstream data(filename);
    double x, y, z;
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
    littlePCSD.set(points, normals, k, epsilon, tao, pt, alpha, r, maxElements,maxLevel);
    littlePCSD.detect(true);
    primitives = littlePCSD.getPrimitives();
    candidates = littlePCSD.getCandidates();
    cout << "Number of primitives: " << primitives.size() << endl;
    cout << "Number of candidates: " << candidates.size() << endl;
    for (unsigned int i = 0; i < primitives.size(); ++i) {
      pds.push_back(new PrimitivaDaniel(primitives[i]));
    }
    return pds;
  }

  vector<PrimitivaDaniel*> PrimitivaDaniel::loadPly(const char *filename) {
    vector<PrimitivaDaniel*> pds;
    
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
    CMesh mesh; // the active mesh instance

    if (filename == 0) {
      puts("ERROR: No primitives file set.");
      exit(1);
    }
    int err = vcg::tri::io::ImporterPLY<CMesh>::Open(mesh, filename);
    if( err == vcg::ply::E_NOERROR ) {
      vcg::tri::UpdateBounding<CMesh>::Box(mesh);
      vcg::tri::UpdateNormal<CMesh>::PerVertexNormalizedPerFace(mesh);
      vcg::tri::UpdateNormal<CMesh>::PerFaceNormalized(mesh);
      vcg::tri::UpdateColor<CMesh>::PerVertexConstant(mesh, vcg::Color4b::Red);
      vcg::tri::UpdateColor<CMesh>::PerFaceConstant(mesh, vcg::Color4b::Red);
      vcg::tri::UpdateColor<CMesh>::PerVertexPerlinNoise(mesh, vcg::Point3f(0.5,0.75,1.0));
      vcg::tri::UpdateColor<CMesh>::PerFaceFromVertex(mesh);
    }
    double x, y, z;
    double nx, ny, nz;
    vector<Point> points;
    vector<Point> normals;
    for (unsigned int i = 0; i < mesh.vert.size(); ++i) {
      x = mesh.vert[i].P()[0];
      y = mesh.vert[i].P()[1];
      z = mesh.vert[i].P()[2];
      nx = mesh.vert[i].N()[0];
      ny = mesh.vert[i].N()[1];
      nz = mesh.vert[i].N()[2];
      Point newPoint(x,y,z);
      Point newNormal(nx, ny, nz);
      points.push_back(newPoint);
      normals.push_back(newNormal);
    }
    littlePCSD.set(points, normals, k, epsilon, tao, pt, alpha, r, maxElements,maxLevel);
    littlePCSD.detect(true);
    primitives = littlePCSD.getPrimitives();
    candidates = littlePCSD.getCandidates();
    cout << "Number of primitives: " << primitives.size() << endl;
    cout << "Number of candidates: " << candidates.size() << endl;
    for (unsigned int i = 0; i < primitives.size(); ++i) {
      pds.push_back(new PrimitivaDaniel(primitives[i]));
    }
    return pds;
  }
}
