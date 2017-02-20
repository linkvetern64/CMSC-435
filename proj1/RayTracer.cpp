//
// Created by Josh on 2/1/2017.
//

#include <iostream>
#include "RayTracer.h"
#include <math.h>
#include "../common/SlVector.h"

#define PI 3.14159265


/**
 * Constructor of RayTracer class
 * Preconditions: None
 * Postconditions: RayTracer class will be initialized
 * @return None
 */
RayTracer::RayTracer() {

}

/**
 * Destructor of RayTracer class
 */
RayTracer::~RayTracer() {}

void RayTracer::getBackgroundColor(){
}

void RayTracer::init(){
    /** Begin Computation **/

    /**Eye point vector**/
    e = SlVector3(from.x(), from.y(), from.z());

    /**Magnitude of vectors from - at*/
    d = mag(from - at);

    /**Math works and verified**/
    w = (from - at) / mag(from - at); //This makes a normalized W
    u = cross(up, w); //Need to normalize U
    u = u / mag(u);
    v = cross(w, u);


    /** Angle has to be in rads!!!!! **/
    rad_angle = (angle * PI) / 180.0;
    m = tan(rad_angle / 2) * d;


    /** Assigns the Left, Right, Top, Bottom values **/
    L = B = -m;
    R = T = m;

    /** End Computation **/
}

bool RayTracer::triangleIntersect(SlVector3 Av, SlVector3 Bv, SlVector3 Cv, int i, int j){

    /** calculates pixel location in world space **/
    u_pos = L + (((R - L) * (i + 0.5)) / Nx );
    v_pos = B + (((T - B) * (j + 0.5)) / Ny );

    /* Vector D */
    direction = ((-d * w) + (u_pos * u) + (v_pos * v));

    /* Vector E*/
    origin = e;

    /** Compute Cramer Rule**/

    a0 = Av.x() - Bv.x();
    b0 = Av.y() - Bv.y();
    c0 = Av.z() - Bv.z();
    d0 = Av.x() - Cv.x();
    e0 = Av.y() - Cv.y();
    f0 = Av.z() - Cv.z();
    g0 = direction.x();
    h0 = direction.y();
    i0 = direction.z();
    j0 = Av.x() - origin.x();
    k0 = Av.y() - origin.y();
    l0 = Av.z() - origin.z();

    M = a0*(e0*i0 - h0*f0) + b0*(g0*f0 - d0*i0) + c0*(d0*h0 - e0*g0);

    /** Compute T **/

    t = -(f0*(a0*k0 - j0*b0) + e0*(j0*c0 - a0*l0) + d0*(b0*l0 - k0*c0)) / M;

    if( t < 0 || t > 100){
        return false;
    }

    /** Compute Gamma **/

    gamma = (i0*(a0*k0 - j0*b0) + h0*(j0*c0 - a0*l0) + g0*(b0*l0 - k0*c0)) / M;

    if( gamma < 0 || gamma > 1){
        return false;
    }

    /** Compute Beta **/

    beta =  (j0*(e0*i0 - h0*f0) + k0*(g0*f0 - d0*i0) + l0*(d0*h0 - e0*g0)) / M;

    if(beta < 0 || beta > (1 - gamma)){
        return false;
    }

    return true;
}


void RayTracer::printImage(){

}