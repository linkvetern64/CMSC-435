//
// Created by Josh on 2/1/2017.
//

#ifndef PROJ_RAYTRACER_H
#define PROJ_RAYTRACER_H

class RayTracer {
public:
    /*Public Variables*/

    //Background color
    //Red, Green, Blue
    float R,G,B;
    //The eye location in XYZ
    float Fx, Fy, Fz;
    //Position to be at the center of the image, in XYZ coordinates
    float Ax, Ay, Az;
    //Vector defining up direction, XYZ vector
    float Ux, Uy, Uz;
    //Angle in degrees
    int angle;
    //Hither
    int hither;
    //Resolution
    int xres, yres;
    //Fill color and shading parameters
    //Red Green Blue Kd Ks Shine T refraction_index
    float Rs, Gs, Bs;

    /*Constructor*/
    RayTracer();

    /*Destructor*/
    ~RayTracer();

    void getBackgroundColor(void);

    //Prints image to ppm file
    void printImage(void);

    void init(void);

    void triangleIntersect(void);

private:



};



#endif //PROJ_RAYTRACER_H
