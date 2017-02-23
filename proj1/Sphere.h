//
// Created by Josh on 2/2/2017.
//

#ifndef PROJ_SPHERE_H
#define PROJ_SPHERE_H


#include "Shape.h"
#include "../common/slVector.H"

class Sphere  : public Shape{
    public:
        SlVector3 C;
        double radius;

        Sphere();
        Sphere(SlVector3, double);

        ~Sphere();

        bool intersect(SlVector3, SlVector3);
};


#endif //PROJ_SPHERE_H
