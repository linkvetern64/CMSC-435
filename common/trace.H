#ifndef TRACE_H
#define TRACE_H

#include "slVector.H"
#include <vector>

class Ray {
public:
  SlVector3 e;
  SlVector3 d;
  Ray(const SlVector3 &_e, const SlVector3 &_d, int _depth = 0) : e(_e), d(_d) {};
};

class Fill {
public: 
  SlVector3 color;
  double kd, ks, shine, t, ior;
};

class HitRecord {
public:
  double t;
  SlVector3 p;
  Fill f;
};

class Surface {
public:
  virtual bool intersect(const Ray &r, double t0, double t1, HitRecord &hr) const = 0;
  virtual ~Surface() {};
};

class Triangle : public Surface {
  SlVector3 a,b,c;
public:
  Triangle(const SlVector3 &_a, const SlVector3 &_b, const SlVector3 &_c) : a(_a), b(_b), c(_c) {};
  virtual bool intersect(const Ray &r, double t0, double t1, HitRecord &hr) const;
};

class TrianglePatch : public Triangle {
  SlVector3 n1, n2, n3;
public:
  TrianglePatch(const SlVector3 &_a, const SlVector3 &_b, const SlVector3 &_c,
	  const SlVector3 &_n1, const SlVector3 &_n2, const SlVector3 &_n3) 
	: Triangle(_a,_b,_c), n1(_n1), n2(_n2), n3(_n3) {};
  SlVector3 normal(double alpha, double beta, double gamma) {
	return alpha*n1 + beta*n2 + gamma*n3;
  };
};

class Poly : public Surface {
  std::vector<SlVector3> verts;
public:
  Poly(const std::vector<SlVector3> &_verts) : verts(_verts) {}; 
  virtual bool intersect(const Ray &r, double t0, double t1, HitRecord &hr) const;
};

class PolyPatch : public Poly {
  std::vector<SlVector3> normals;
public:
  PolyPatch(const std::vector<SlVector3> &_verts, const std::vector<SlVector3> &_normals) : Poly(_verts), normals(_normals) {}; 
};

class Sphere : public Surface {
  SlVector3 c;
  double rad;
public:
  Sphere(const SlVector3 &_c, double _r) : c(_c), rad(_r) {};
  bool intersect(const Ray &r, double t0, double t1, HitRecord &hr) const;
};

class Tracer {
  SlVector3 bcolor, eye, at, up;
  double angle, hither;
  unsigned int res[2];
  std::vector<std::pair<Surface *, Fill> > surfaces;

  SlVector3 *im;
public:
  Tracer(const std::string &fname);
  ~Tracer();
  void traceImage();  
  SlVector3 traceRay(const Ray &ray, double t0, double t1) const;
  SlVector3 shade(const HitRecord &hr) const;
  void writeImage(const std::string &fname);
};
	
#endif
