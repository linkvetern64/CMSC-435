//
// Created by Josh on 2/2/2017.
//

#ifndef PROJ_POLYGON_H
#define PROJ_POLYGON_H

#define PI 3.14159265

#include "Shape.h"
#include "../common/slVector.H"

#include <vector>


class Polygon : public Shape {

public:

    //Total vertices of polygons
    int numVertices;

    double beta, gamma, t, M;
    double a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0;

    //Vector containing structs of vertices
    //Scalable beyond 3 given coordinates
    std::vector<SlVector3> vertex;


    //Constructor
    Polygon() : Shape(){};

    //Destructor
    ~Polygon(){};

    //Creates vertice struct and inserts into vert vector
    void insertVertices(double, double, double);

    bool intersect(SlVector3, SlVector3);

private:

};


#endif //PROJ_POLYGON_H
