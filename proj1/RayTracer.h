//
// Created by Josh on 2/1/2017.
//

#ifndef PROJ_RAYTRACER_H
#define PROJ_RAYTRACER_H

/*Standard includes*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <numeric>
#include <math.h>
#include <string>

/*Custom Includes*/
#include "Shape.h"
#include "Sphere.h"
#include "Polygon.h"
#include "../common/slVector.H"

class RayTracer {

public:
    /*Public Variables*/
    std::ifstream file;

    SlVector3 from, up, w, u, v, at, e;
    SlVector3 direction;
    SlVector3 origin;

    std::vector<Polygon> polygons;
    std::vector<Sphere> spheres;
    std::vector<Shape *> shapes;

    //Fill color and shading parameters
    //Red Green Blue Kd Ks Shine T refraction_index
    double Rs, Gs, Bs;
    double L, B, R, T, d, angle, m;
    double u_pos, v_pos;
    double rad_angle;


    //Hither
    int hither;
    //Resolution
    int Nx, Ny;

    /*Constructor*/
    RayTracer();

    /*Destructor*/
    ~RayTracer();

    /**
     * @name - init
     * @constraints:
     * Param must be a .nff file with proper formatting.
     * Checks will not be done to ensure a proper file, unknown results
     * may occur.
     * @desc:
     * Parses NFF file, will compute camera basis and all redundant values
     * that will be used by the RayTracer
     */
    void init(std::string);

    std::vector<Polygon> getTriangles();


    std::vector<Sphere> getSpheres();

    std::vector<Shape *> getGeometry();

private:



};



#endif //PROJ_RAYTRACER_H
