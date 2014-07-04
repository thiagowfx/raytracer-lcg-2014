#ifndef _CAMERA_MINE_
#define _CAMERA_MINE_

/* There is no view plane distance because the fisheye and panoramic cameras don't use it */
#include <Eigen/Dense>
using Eigen::Vector2d;
using Eigen::Vector3d;
class World;

namespace Raytracer {
  class Camera {
  public:
    Camera();
    Camera(const Camera& camera);
    virtual Camera* clone() const = 0;
    virtual ~Camera();
    virtual void render_scene(const World* w, const char* image_file) = 0;
    void set_eye(const Vector3d&);
    void set_eye(double, double, double);
    void set_lookat(const Vector3d&);
    void set_lookat(double,double,double);
    void set_up_vector(const Vector3d&);
    void set_up_vector(double,double,double);
    void set_exposure_time(double exposure);
    void set_zoom(double zoom);
    void set_view_distance(double d);
    void compute_uvw();
    Vector3d get_eye() const;
    double get_view_distance() const;

  protected:
    Vector3d eye; /**< Camera position. */
    Vector3d lookat = Vector3d::Zero(); /**< Point where the camera is looking at. */
    Vector3d u, v, w; // orthonormal basis vectors
    Vector3d up; // up vector
    double exposure_time = 1.0; /**< Exposure time. */
    double zoom = 1.0; /**< Zoom factor. More is nearer. */
    double d = 250.0; /**< View plane distance. */
  };


  inline void Camera::set_eye(const Vector3d& p) {
    eye = p;
  }


  inline void Camera::set_eye(double x, double y, double z) {
    eye = Vector3d(x,y,z);
  }


  inline void Camera::set_lookat(const Vector3d& p) {
    lookat = p;
  }


  inline void Camera::set_lookat(double x, double y, double z) {
    lookat = Vector3d(x,y,z);
  }


  inline void Camera::set_up_vector(const Vector3d& u) {
    up = u;
  }


  inline void Camera::set_up_vector(double x, double y, double z) {
    up = Vector3d(x,y,z);
  }


  inline void Camera::set_exposure_time(double exposure_time) {
    this->exposure_time = exposure_time;
  }


  inline Vector3d Camera::get_eye() const {
    return eye;
  }


  inline double Camera::get_view_distance() const {
    return d;
  }


  inline void Camera::set_zoom(double zoom) {
    this->zoom = zoom;
  }


  inline void Camera::set_view_distance(double d) {
    this->d = d;
  }
}

#endif // _CAMERA_MINE_
