//
// Created by Josh on 2/2/2017.
//

#ifndef PROJ_POLYGON_H
#define PROJ_POLYGON_H

#define PI 3.14159265

#include <vector>
#include "../common/slVector.H"
#include "Shape.h"

class Polygon : public Shape{

public:

    //Total vertices of polygons
    int numVertices;

    //Vector containing structs of vertices
    //Scalable beyond 3 given coordinates
    std::vector<SlVector3> vertex;


    //Constructor
    Polygon() : Shape(){};

    //Destructor
    ~Polygon(){};

    //Creates vertice struct and inserts into vert vector
    void insertVertices(double, double, double);


    std::vector<SlVector3> getVectors(void);

private:
    //Nonion rings
};


#endif //PROJ_POLYGON_H
