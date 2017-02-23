//
// Created by Josh on 2/2/2017.
//

#include "Sphere.h"

Sphere::Sphere(SlVector3 C, double radius){
    this->C = C;
    this->radius = radius;
}

Sphere::~Sphere(){

}

bool Sphere::intersect(SlVector3 direction, SlVector3 origin){
    SlVector3 omc = (origin - C);
    double disc = pow(dot(direction, omc),2) - (dot(direction, direction)) * (dot(omc,omc) - pow(radius, 2));
    return disc > 0;
}
