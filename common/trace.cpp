#include "trace.H"
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <getopt.h>
#ifdef __APPLE__
#define MAX std::numeric_limits<double>::max()
#else
#include <values.h>
#define MAX DBL_MAX
#endif

// return the determinant of the matrix with columns a, b, c.
double det(const SlVector3 &a, const SlVector3 &b, const SlVector3 &c) {
  return a[0]* (b[1] * c[2] - c[1] * b[2]) +
	b[0] * (c[1] * a[2] - a[1] * c[2]) +
	c[0] * (a[1] * b[2] - b[1] * a[2]);
}

inline double sqr(double x) {return x*x;} 

bool Triangle::intersect(const Ray &r, double t0, double t1, HitRecord &hr) const {
  SlVector3 ba = a-b;
  SlVector3 ca = a-c;
  SlVector3 ea = a-r.e;
  double detA = det(ba, ca, r.d);
  double t = det(ba, ca, ea)/detA;
  if (t < t0 || t > t1) return false;
  double beta = det(ea, ca, r.d)/detA;
  if (beta < 0 || beta > 1) return false;
  double gamma = det(ba, ea, r.d)/detA;
  if (gamma < 0.0 || gamma > 1.0-beta) return false;
  hr.t = t;
  hr.p = r.e + t * r.d;
  return true;
}

bool Sphere::intersect(const Ray &r, double t0, double t1, HitRecord &hr) const {
  double ddotemc = dot(r.d, r.e-c);
  double d2 = sqrMag(r.d);

  double disc = sqr(ddotemc) - d2 * (sqrMag(r.e-c) - rad*rad);

  if (disc < 0) return false;
  double root1 = (-ddotemc + sqrt(disc)) / d2;
  double root2 = (-ddotemc - sqrt(disc)) / d2;

  double t = root1;
  if (root1 < 0 || (root2 > 0 && root2 < root1)) t = root2;
  if (t < t0 || t > t1) return false;
  
  hr.t = t;
  hr.p = r.e + t * r.d;
  return true;
}

SlVector2 project(const SlVector3 &x, int projectDir) {
  switch (projectDir) {
  case 0:
	return SlVector2(x[1],x[2]);
  case 1:
	return SlVector2(x[0],x[2]);
  case 2:
	return SlVector2(x[0],x[1]);
  }
  return SlVector2(1.0, 1.0);
}

bool Poly::intersect(const Ray &r, double t0, double t1, HitRecord &hr) const {
  int projectDir;
  SlVector3 n = cross(verts[1]-verts[0], verts[2]-verts[0]);
  normalize(n);

  double t = -(dot(r.e, n) - dot(verts[0], n)) / dot(r.d,n);
  if (t < t0 || t > t1) return false;

  SlVector3 p = r.e + t*r.d;

  if (fabs(n[0]) > fabs(n[1]) && fabs(n[0]) > fabs(n[2])) {
	projectDir = 0;
  } else if (fabs(n[1]) > fabs(n[2])) {
	projectDir = 1;
  } else {
	projectDir = 2;
  }
  
  SlVector2 p2 = project(p, projectDir);

  SlVector2 bbMin = project(verts[0], projectDir);
  SlVector2 bbMax = bbMin;
  for (unsigned int i=1; i<verts.size(); i++) {
	SlVector2 v = project(verts[i], projectDir);
	if (v[0] < bbMin[0]) bbMin[0] = v[0];
	if (v[0] > bbMax[0]) bbMax[0] = v[0];
	if (v[1] < bbMin[1]) bbMin[1] = v[1];
	if (v[1] > bbMax[1]) bbMax[1] = v[1];
  }
  
  if (p2[0] < bbMin[0]) return false;
  if (p2[1] < bbMin[1]) return false;
  if (p2[0] > bbMax[0]) return false;
  if (p2[1] > bbMax[1]) return false;

  SlVector2 dir(sqrt(2), sqrt(2));
  int count = 0;
  for (unsigned int i=0; i<verts.size(); i++) {
	SlVector2 a = project(verts[i], projectDir);
	SlVector2 b = project(verts[(i+1) % verts.size()], projectDir);
	SlVector2 ab = b-a;
	double t2 = cross(a-p2, ab / cross(dir, ab));
	if (t2 < 0.0) continue;
	double alpha = cross(a-p2, dir / cross(dir, ab));
	if (alpha > 0.0 && alpha < 1.0) count++;
  }

  if (count % 2 == 0) {
	return false;
  }

  hr.t = t;
  hr.p = p;
  return true;
}

Tracer::Tracer(const std::string &fname) {
  std::ifstream in(fname.c_str(), std::ios_base::in);
  std::string line;
  char ch;
  Fill fill;
  while (in) {
	getline(in, line);
	switch (line[0]) {
	case 'b': {
	  std::stringstream ss(line);
	  ss>>ch>>bcolor[0]>>bcolor[1]>>bcolor[2];
	  break;
	}

	case 'v': {
	  getline(in, line);
	  std::string junk;
	  std::stringstream fromss(line);
	  fromss>>junk>>eye[0]>>eye[1]>>eye[2];

	  getline(in, line);
	  std::stringstream atss(line);
	  atss>>junk>>at[0]>>at[1]>>at[2];

	  getline(in, line);
	  std::stringstream upss(line);
	  upss>>junk>>up[0]>>up[1]>>up[2];

	  getline(in, line);
	  std::stringstream angless(line);
	  angless>>junk>>angle;

	  getline(in, line);
	  std::stringstream hitherss(line);
	  hitherss>>junk>>hither;

	  getline(in, line);
	  std::stringstream resolutionss(line);
	  resolutionss>>junk>>res[0]>>res[1];
	  break;
	}

	case 'p': {
	  bool patch = false;
	  std::stringstream ssn(line);
	  unsigned int nverts;
	  if (line[1] == 'p') {
		patch = true;
		ssn>>ch;
	  }
	  ssn>>ch>>nverts;
	  std::vector<SlVector3> vertices;
	  std::vector<SlVector3> normals;
	  for (unsigned int i=0; i<nverts; i++) {
		getline(in, line);
		std::stringstream ss(line);
		SlVector3 v,n;
		if (patch) ss>>v[0]>>v[1]>>v[2]>>n[0]>>n[1]>>n[2];
		else ss>>v[0]>>v[1]>>v[2];
		vertices.push_back(v);
		normals.push_back(n);
	  }
	  bool makeTriangles = false;
	  if (vertices.size() == 3) {
		makeTriangles = true;
		if (patch) {
		  surfaces.push_back(std::pair<Surface *, Fill>(new TrianglePatch(vertices[0], vertices[1], vertices[2], 
					  normals[0], normals[1], normals[2]), fill));
		} else {
		  surfaces.push_back(std::pair<Surface *, Fill>(new Triangle(vertices[0], vertices[1], vertices[2]), fill));
		}
	  } else if (vertices.size() == 4) {
		SlVector3 n0 = cross(vertices[1] - vertices[0], vertices[2] - vertices[0]);
		SlVector3 n1 = cross(vertices[2] - vertices[1], vertices[3] - vertices[1]);
		SlVector3 n2 = cross(vertices[3] - vertices[2], vertices[0] - vertices[2]);
		SlVector3 n3 = cross(vertices[0] - vertices[3], vertices[1] - vertices[3]);
		if (dot(n0,n1) > 0 && dot(n0,n2) > 0 && dot(n0,n3) > 0) {
		  makeTriangles = true;
		  if (patch) {
			surfaces.push_back(std::pair<Surface *, Fill>(new TrianglePatch(vertices[0], vertices[1], vertices[2], 
						normals[0], normals[1], normals[2]), fill));
			surfaces.push_back(std::pair<Surface *, Fill>(new TrianglePatch(vertices[0], vertices[2], vertices[3], 
						normals[0], normals[2], normals[3]), fill));
		  } else {
			surfaces.push_back(std::pair<Surface *, Fill>(new Triangle(vertices[0], vertices[1], vertices[2]), fill));
			surfaces.push_back(std::pair<Surface *, Fill>(new Triangle(vertices[0], vertices[2], vertices[3]), fill));
		  }
		}
	  }
	  if (!makeTriangles) {
		if (patch) {
		  surfaces.push_back(std::pair<Surface *, Fill>(new PolyPatch(vertices, normals), fill));
		} else {
		  surfaces.push_back(std::pair<Surface *, Fill>(new Poly(vertices), fill));
		}
	  }
	  break;
	}

	case 's' : {
	  std::stringstream ss(line);
	  SlVector3 c;
	  double r;
	  ss>>ch>>c[0]>>c[1]>>c[2]>>r;
	  surfaces.push_back(std::pair<Surface *, Fill>(new Sphere(c,r), fill));
	  break;
	}
	  
	case 'f' : {
	  std::stringstream ss(line);
	  ss>>ch>>fill.color[0]>>fill.color[1]>>fill.color[2]>>fill.kd>>fill.ks>>fill.shine>>fill.t>>fill.ior;
	  break;
	}

	default:
	  break;
	}
  }
  im = new SlVector3[res[0]*res[1]];
}

Tracer::~Tracer() {
  if (im) delete [] im;
  for (unsigned int i=0; i<surfaces.size(); i++) delete surfaces[i].first;
}

SlVector3 Tracer::shade(const HitRecord &hr) const {
  return hr.f.color;
}

SlVector3 Tracer::traceRay(const Ray &r, double t0, double t1) const {
  HitRecord hr;
  SlVector3 color(bcolor);
  
  bool hit = false;
  for (unsigned int k=0; k<surfaces.size(); k++) {
	const std::pair<Surface *, Fill> &s  = surfaces[k];
	if (s.first->intersect(r, t0, t1, hr)) {
	  t1 = hr.t;
	  hr.f = s.second;
	  hit = true;
	}
  }

  if (hit) color = shade(hr);
  return color;
}

void Tracer::traceImage() {
  // set up coordinate system
  SlVector3 w = eye - at;
  w /= mag(w);
  std::cout<<w<<std::endl;
  SlVector3 u = cross(up,w);
  normalize(u);
  SlVector3 v = cross(w,u);
  
  double d = mag(eye - at);
  double h = tan((M_PI/180.0) * (angle/2.0)) * d;
  double l = -h;
  double r = h;
  // ppm starts at the top of the image, so these are flipped
  double b = h;
  double t = -h;

  SlVector3 *pixel = im;

  for (unsigned int j=0; j<res[1]; j++) {
	for (unsigned int i=0; i<res[0]; i++, pixel++) {
	  double x = l + (r-l)*(i+0.5)/res[0];
	  double y = b + (t-b)*(j+0.5)/res[1];
	  SlVector3 dir = -d * w + x * u + y * v;
	  normalize(dir);
	  Ray r(eye, dir);
	  (*pixel) = traceRay(r, 0.0, MAX);
	}
  }
}

void Tracer::writeImage(const std::string &fname) {
#ifdef __APPLE__
  std::ofstream out(fname, std::ios::out | std::ios::binary);
#else
  std::ofstream out(fname.c_str(), std::ios_base::binary);
#endif
  out<<"P6"<<"\n"<<res[0]<<" "<<res[1]<<"\n"<<255<<"\n";
  SlVector3 *pixel = im;
  char val;
  for (unsigned int i=0; i<res[0]*res[1]; i++, pixel++) {
	val = (unsigned char)(std::min(1.0, std::max(0.0, (*pixel)[0])) * 255.0);
	out.write (&val, sizeof(unsigned char));
	val = (unsigned char)(std::min(1.0, std::max(0.0, (*pixel)[1])) * 255.0);
	out.write (&val, sizeof(unsigned char));
	val = (unsigned char)(std::min(1.0, std::max(0.0, (*pixel)[2])) * 255.0);
	out.write (&val, sizeof(unsigned char));
  }
  out.close();
}


int main(int argc, char *argv[]) {
  if (argc != 3) {
	std::cout<<"usage: trace input.nff output.ppm"<<std::endl;
	exit(0);
  }	

  Tracer tracer(argv[1]);
  tracer.traceImage();
  tracer.writeImage(argv[2]);
};
