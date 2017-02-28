//
// Created by Josh on 2/22/2017.
//

#include "Shape.h"

std::string Shape::getType(){
    return type;
}

void Shape::setRBG(double red, double green, double blue) {
    this->red = red;
    this->green = green;
    this->blue = blue;
}

bool Shape::intersect(SlVector3, SlVector3) {
    return false;
}
