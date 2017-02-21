//
// Created by Josh on 2/2/2017.
//

#ifndef PROJ_SPHERE_H
#define PROJ_SPHERE_H


class Sphere {
    public:
        double x, y, z, radius;


        Sphere(double, double, double, double);
        ~Sphere();

        bool checkIntersect(void);
};


#endif //PROJ_SPHERE_H
