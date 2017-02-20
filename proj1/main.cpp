/**
 * Author: Joshua Standiford
 * Email: jstand1@umbc.edu
 * Desc: driver file for ray tracing program
 */

/*Standard includes*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <numeric>
#include <math.h>


/*Custom includes*/
#include "RayTracer.h"
#include "Polygon.h"
#include "../common/slVector.H"
#include "../common/slTransform.H"
#include "../common/slIO.H"
//#include "../common/CImg.h"

#define PI 3.14159265

void printImage(void);

using namespace std;
int main() {

    int tokenSize = 8;
    ifstream file;
    RayTracer ray;
    string line;
    string filepath = "tetra-3.nff";
    string tokens[tokenSize];
    vector<Polygon> polygons;

    double L, B, R, T, d, angle, m;
    SlVector3 from, up, w, u, v, at, e;
     /*
     * Calling inline functions
     * cross()
     * dot()
     */


    file.open(filepath);

    if(!file){
        cout << "File: " << filepath << " Failed to open." << endl;
    }

    if(file.is_open()) {
        while (getline(file, line)) {
            stringstream tokenizer(line);
            int i = 0;
            //break apart string into tokens
            while(tokenizer.good() && i < tokenSize){
                tokenizer >> tokens[i];
                i++;
            }

            //Place tokens into RayTracer object
            for(int j = 0; j < i; j++){
                string cmp = tokens[0];
                if(!cmp.compare("b")){

                    break;
                }
                else if(!cmp.compare("from")){
                    ray.Fx = stof(tokens[1]);
                    ray.Fy = stof(tokens[2]);
                    ray.Fz = stof(tokens[3]);
                    from = SlVector3(ray.Fx, ray.Fy, ray.Fz);
                    break;
                }
                else if(!cmp.compare("at")){
                    ray.Ax = stof(tokens[1]);
                    ray.Ay = stof(tokens[2]);
                    ray.Az = stof(tokens[3]);
                    at = SlVector3(ray.Ax, ray.Ay, ray.Az);
                    break;
                }
                else if(!cmp.compare("up")){
                    ray.Ux = stof(tokens[1]);
                    ray.Uy = stof(tokens[2]);
                    ray.Uz = stof(tokens[3]);
                    up = SlVector3(ray.Ux, ray.Uy, ray.Uz);
                    break;
                }
                else if(!cmp.compare("angle")){
                    ray.angle = stoi(tokens[1]);
                    angle = ray.angle;
                    break;
                }
                else if(!cmp.compare("hither")){
                    ray.hither = stoi(tokens[1]);
                    break;
                }
                else if(!cmp.compare("resolution")){
                    ray.xres = stoi(tokens[1]);
                    ray.yres = stoi(tokens[2]);
                    break;
                }
                else if(!cmp.compare("f")){
                    ray.Rs = stof(tokens[1]);
                    ray.Gs = stof(tokens[2]);
                    ray.Bs = stof(tokens[3]);
                    break;
                }
                //For populating Polygons
                else if(!cmp.compare("p")){
                    int polyCount = stoi(tokens[1]);
                    Polygon polygon;
                    for(int m = 0; m < polyCount; m++){

                        getline(file, line);
                        stringstream tokenizer(line);
                        int i = 0;
                        //break apart string into tokens
                        while(tokenizer.good() && i < tokenSize){
                            tokenizer >> tokens[i];
                            i++;
                        }
                        polygon.insertVertices(stof(tokens[0]), stof(tokens[1]), stof(tokens[2]));
                    }
                    polygons.push_back(polygon);
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
    u = cross(up, w);
    v = cross(w, u);


    /** Angle has to be in rads!!!!! **/
    double rad_angle = (angle * PI) / 180.0;
    m = tan(rad_angle / 2) * d;


    /** Assigns the Left, Right, Top, Bottom values **/
    L = B = -m;
    R = T = m;

    /** Debug Statements **/
    /*
    cout << "X: " << w.x() << " Y: " << w.y() << " Z: " << w.z() << endl;
    cout << "X: " << u.x() << " Y: " << u.y() << " Z: " << u.z() << endl;
    cout << "X: " << v.x() << " Y: " << v.y() << " Z: " << v.z() << endl;
    cout << "M - value: " << m << endl;
    cout << "Left: " << l << endl;
    cout << "Right: " << r << endl;
    cout << "Bottom: " << b << endl;
    cout << "Top: " << t << endl;
    */
    /** End Computation **/

    double u_pos, v_pos;
    int Nx, Ny;
    Nx = ray.xres;
    Ny = ray.yres;

    for(int i = 0; i < Nx; i++){
        for(int j = 0; j < Ny; j++){
            /** Compute pixels here**/
            /* Calculate pixel location in world space
             * Calculate ray from eye point through pixel into scene
             * calculate ray-object intersections, choose closest T
             * set pixel to that color
             */

            /** calculates pixel location in world space **/
            u_pos = L + (((R - L) * (i + 0.5)) / Nx );
            v_pos = B + (((T - B) * (j + 0.5)) / Ny );


        }
    }

    /** Write pixels out to file **/
    //ray.printImage();

    return 0;
}

