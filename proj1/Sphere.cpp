//
// Created by Josh on 2/2/2017.
//

#include "Sphere.h"

Sphere::Sphere(){
    //default constructor
}

Sphere::Sphere(double x, double y, double z, double radius){
    this->x = x;
    this->y = y;
    this->z = z;
    this->radius = radius;
}

Sphere::~Sphere(){}
