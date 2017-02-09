//
// Created by Josh on 2/2/2017.
//

#ifndef PROJ_POLYGON_H
#define PROJ_POLYGON_H

#include <vector>

struct vertices{
    float x, y, z;
};

class Polygon {

public:

    //Total vertices of polygons
    int numVertices;

    //Vector containing structs of vertices
    //Scalable beyond 3 given coordinates
    std::vector<vertices> vertex;

    float x, y, z;

    //Constructor
    Polygon();

    //Destructor
    ~Polygon();

    //Creates vertice struct and inserts into vert vector
    void insertVertices(float, float, float);

    //Prints vertices in struct vector
    void printVertices(void);


private:
    //Nonion rings
};


#endif //PROJ_POLYGON_H
