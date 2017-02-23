//
// Created by Josh on 2/2/2017.
//
#include "Polygon.h"
#include <vector>
#include <iostream>

/**
 * Constructor for Polygon class
 * @return None
 */
//Polygon::Polygon(){}

/**
 * Destructors for Polygon class
 * @return None
 */
//Polygon::~Polygon(){}

/**
 * Creates a new vertice struct and insert it into that polygons vertice vector
 * @param x - float of position X
 * @param y - float of position Y
 * @param z - float of position Z
 */
void Polygon::insertVertices(double x, double y, double z){
    vertex.push_back(SlVector3(x, y, z));
}

std::vector<SlVector3> Polygon::getVectors(){
    return vertex;
}