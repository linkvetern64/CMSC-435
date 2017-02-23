//
// Created by Josh on 2/2/2017.
//
#include "Polygon.h"


Polygon::Polygon(std::vector<SlVector3> vertices) {
    this->vertex = vertices;
}


bool Polygon::intersect(SlVector3 direction, SlVector3 origin){

    /** Compute Cramer Rule**/
    SlVector3 Av = vertex.at(0);
    SlVector3 Bv = vertex.at(1);
    SlVector3 Cv = vertex.at(2);

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

    if(gamma < 0 || gamma > 1){
        return false;
    }

    /** Compute Beta **/

    beta =  (j0*(e0*i0 - h0*f0) + k0*(g0*f0 - d0*i0) + l0*(d0*h0 - e0*g0)) / M;

    if(beta < 0 || beta > (1 - gamma)){
        return false;
    }

    return true;
}
