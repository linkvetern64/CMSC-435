//
// Created by Josh on 2/2/2017.
//

#include "Sphere.h"

Sphere::Sphere(){
    //default constructor
}

Sphere::Sphere(SlVector3 C, double radius){
    this->C = C;
    this->radius = radius;
}

Sphere::~Sphere(){}

bool Sphere::intersect(SlVector3 direction, SlVector3 origin){
    double disc = pow(dot(direction,(origin - C)),2) - (dot(direction, direction)) * (dot((origin - C),(origin - C)) - pow(radius, 2));
    return disc > 0;
}
