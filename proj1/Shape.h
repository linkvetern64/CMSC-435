//
// Created by Josh on 2/22/2017.
//

#ifndef PROJ_SHAPE_H
#define PROJ_SHAPE_H

#include "../common/slVector.H"


class Shape{

public:

    std::string type;
    double RED, GREEN, BLUE;

    //Constructor for Super Class Shape
    Shape(){};

    //Destructor for Super Class Shape
    ~Shape(){};

    std::string getType(void);

    virtual bool intersect(SlVector3, SlVector3);

};

#endif //PROJ_SHAPE_H
