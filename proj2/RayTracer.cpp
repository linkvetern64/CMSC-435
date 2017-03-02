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

/**
 * @name init
 * @param filepath - type string
 * @desc
 * Parses the NFF file passed in by the command line or default file.
 * Creates Shape derived classes of types passed in by the NFF file
 */
void RayTracer::init(std::string filepath){

    std::string line;
    int tokenSize = 10;
    std::string tokens[10];
    std::vector<double> fill;

    //local variables used for setting f parameters
    double local_r, local_g, local_b, l_Kd, l_Ks, l_e, l_Kt, l_ir;

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
                    setBackground(atof(tokens[1].data()), atof(tokens[2].data()), atof(tokens[3].data()));
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
                else if(!cmp.compare("l")){
                    lights.push_back(SlVector3(atof(tokens[1].data()), atof(tokens[2].data()), atof(tokens[3].data())));
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
                    /**Todo: Make a new Surface class, then pass that pointer to
                     * the new shape being pushed.
                     */
                    fill.clear();
                    //Red - 0
                    fill.push_back(atof(tokens[1].data()));
                    //Green - 1
                    fill.push_back(atof(tokens[2].data()));
                    //Blue - 2
                    fill.push_back(atof(tokens[3].data()));
                    //Kd - 3
                    fill.push_back(atof(tokens[4].data()));
                    //Ks - 4
                    fill.push_back(atof(tokens[5].data()));
                    //e - 5
                    fill.push_back(atof(tokens[6].data()));
                    //Kt - 6
                    fill.push_back(atof(tokens[7].data()));
                    //ir - 7
                    fill.push_back(atof(tokens[8].data()));
                    break;
                }

                /** Adding Geometry goes below */
                    //For populating Polygons
                else if(!cmp.compare("p") || !cmp.compare("pp")){
                    int polyCount = atoi(tokens[1].data());
                    std::vector<SlVector3> vertices;

                    //pushes P N, N number of vertices into the vector for dynamic complex geometry
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
                    std::vector<SlVector3> tmp_vert;

                    for(int ind = 1; ind < vertices.size() - 1; ind++){
                        tmp_vert.push_back(vertices.at(0));
                        tmp_vert.push_back(vertices.at(ind));
                        tmp_vert.push_back(vertices.at(ind + 1));
                        pushGeometry(new Polygon(tmp_vert), fill);
                        tmp_vert.clear();
                    }
                    break;
                }
                    //For computing Spheres
                else if(!cmp.compare("s")){
                    pushGeometry(new Sphere(SlVector3(atof(tokens[1].data()), atof(tokens[2].data()), atof(tokens[3].data())), atof(tokens[4].data())), fill);
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

std::vector<Sphere *> RayTracer::getSpheres(){
    return spheres;
}

std::vector<Shape *> RayTracer::getGeometry(){
    return shapes;
}

void RayTracer::pushGeometry(Shape * shape, std::vector<double> fills){
    shape->red = fills.at(0);
    shape->green = fills.at(1);
    shape->blue = fills.at(2);
    shape->Kd = fills.at(3);
    shape->Ks = fills.at(4);
    shape->gloss = fills.at(5);
    shape->Kt = fills.at(6);
    shape->Ir = fills.at(7);

    shapes.push_back(shape);
}

void RayTracer::setBackground(double red, double green, double blue){
    this->BG_r = red;
    this->BG_g = green;
    this->BG_b = blue;
}