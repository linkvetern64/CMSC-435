//
// Created by Josh on 2/1/2017.
//

#ifndef PROJ_RAYTRACER_H
#define PROJ_RAYTRACER_H

#include "../common/SlVector.h"

class RayTracer {
public:
    /*Public Variables*/

    double L, B, R, T, d, angle, m;

    SlVector3 from, up, w, u, v, at, e;


    double u_pos, v_pos;
    double rad_angle;
    SlVector3 direction;
    SlVector3 origin;
    double beta, gamma, t, M;
    double a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0;



    //Hither
    int hither;
    //Resolution
    int Nx, Ny;


    //Fill color and shading parameters
    //Red Green Blue Kd Ks Shine T refraction_index
    double Rs, Gs, Bs;

    /*Constructor*/
    RayTracer();

    /*Destructor*/
    ~RayTracer();

    void getBackgroundColor(void);

    //Prints image to ppm file
    void printImage(void);


    void init(void);

    bool triangleIntersect(SlVector3, SlVector3, SlVector3, int, int);

private:



};



#endif //PROJ_RAYTRACER_H
