//
// Created by Josh on 2/1/2017.
//

#include <iostream>
#include <math.h>


#include "RayTracer.h"

#define PI 3.14159265


/**
 * Constructor of RayTracer class
 * Preconditions: None
 * Postconditions: RayTracer class will be initialized
 * @return None
 */
RayTracer::RayTracer() {

}

/**
 * Destructor of RayTracer class
 */
RayTracer::~RayTracer() {}


void RayTracer::init(std::string filepath){

    std::string line;
    int tokenSize = 8;
    std::string tokens[8];

    /** Parse NFF File*/
    file.open(filepath.c_str());

    if(!file){
        std::cout << "File: " << filepath << " Failed to open." << std::endl;
    }

    if(file.is_open()) {
        while (getline(file, line)) {
            std::stringstream tokenizer(line);
            int i = 0;
            //break apart string into tokens
            while(tokenizer.good() && i < tokenSize){
                tokenizer >> tokens[i];
                i++;
            }

            //Place tokens into RayTracer object
            for(int j = 0; j < i; j++){
                std::string cmp = tokens[0];
                if(!cmp.compare("b")){

                    break;
                }
                else if(!cmp.compare("from")){
                    from = SlVector3(atof(tokens[1].data()), atof(tokens[2].data()), atof(tokens[3].data()));
                    break;
                }
                else if(!cmp.compare("at")){
                    at = SlVector3(atof(tokens[1].data()), atof(tokens[2].data()), atof(tokens[3].data()));
                    break;
                }
                else if(!cmp.compare("up")){
                    up = SlVector3(atof(tokens[1].data()), atof(tokens[2].data()), atof(tokens[3].data()));
                    break;
                }
                else if(!cmp.compare("angle")){
                    angle = atoi(tokens[1].data());
                    break;
                }
                else if(!cmp.compare("hither")){
                    hither = atoi(tokens[1].data());
                    break;
                }
                    //Ex: 512x512 pixesl
                else if(!cmp.compare("resolution")){
                    Nx = atoi(tokens[1].data());
                    Ny = atoi(tokens[2].data());
                    break;
                }
                    //Stores the last fill color
                else if(!cmp.compare("f")){
                    Rs = atof(tokens[1].data());
                    Gs = atof(tokens[2].data());
                    Bs = atof(tokens[3].data());
                    break;
                }
                    //For populating Polygons
                else if(!cmp.compare("p")){
                    int polyCount = atoi(tokens[1].data());
                    std::vector<SlVector3> vertices;

                    for(int m = 0; m < polyCount; m++){

                        getline(file, line);
                        std::stringstream tokenizer(line);
                        int i = 0;
                        //break apart string into tokens
                        while(tokenizer.good() && i < tokenSize){
                            tokenizer >> tokens[i];
                            i++;
                        }
                        vertices.push_back(SlVector3(atof(tokens[0].data()), atof(tokens[1].data()), atof(tokens[2].data())));
                    }
                    //polygons.push_back(polygon);
                    shapes.push_back(new Polygon(vertices));
                    break;
                }

                    //For computing Spheres
                else if(!cmp.compare("s")){
                    shapes.push_back(new Sphere(SlVector3(atof(tokens[1].data()), atof(tokens[2].data()), atof(tokens[3].data())), atof(tokens[4].data())));
                    break;
                }
            }
        }
    }
    file.close();

    /** Begin Computation **/

    /**Eye point vector**/
    e = SlVector3(from.x(), from.y(), from.z());

    /**Magnitude of vectors from - at*/
    d = mag(from - at);

    /**Math works and verified**/
    w = (from - at) / mag(from - at); //This makes a normalized W
    u = cross(up, w); //Need to normalize U
    u = u / mag(u);
    v = cross(w, -u);


    /** Angle has to be in rads!!!!! **/
    rad_angle = (angle * PI) / 180.0;
    m = tan(rad_angle / 2) * d;


    /** Assigns the Left, Right, Top, Bottom values **/
    L = B = -m;
    R = T = m;

    /** End Computation **/
}

std::vector<Polygon> RayTracer::getTriangles(){
    return polygons;
}

std::vector<Sphere> RayTracer::getSpheres(){
    return spheres;
}

std::vector<Shape *> RayTracer::getGeometry(){
    return shapes;
}
