//
// Created by Josh on 2/2/2017.
//

#include "Polygon.h"
#include <iostream>

/**
 * Constructor for Polygon class
 * @return None
 */
Polygon::Polygon(){}

/**
 * Destructors for Polygon class
 * @return None
 */
Polygon::~Polygon(){}

/**
 * Creates a new vertice struct and insert it into that polygons vertice vector
 * @param x - float of position X
 * @param y - float of position Y
 * @param z - float of position Z
 */
void Polygon::insertVertices(float x, float y, float z){
    vertices newVert;
    newVert.x = x;
    newVert.y = y;
    newVert.z = z;
    vertex.push_back(newVert);
}

/**
 * Prints all vertices within vertice vector
 */
void Polygon::printVertices(){
    for(int i = 0; i < vertex.size(); i++){
        printf(" Poly Vertices: %f, %f, %f\n", vertex.at(i).x, vertex.at(i).y, vertex.at(i).z );
    }
    std::cout << std::endl;
}