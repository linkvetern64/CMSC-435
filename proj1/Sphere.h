//
// Created by Josh on 2/2/2017.
//

#ifndef PROJ_SPHERE_H
#define PROJ_SPHERE_H


#include "Shape.h"

class Sphere  : public Shape{
    public:
        double x, y, z, radius;

        Sphere();
        Sphere(double, double, double, double);

        ~Sphere();

};


#endif //PROJ_SPHERE_H
