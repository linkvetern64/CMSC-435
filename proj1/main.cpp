/**
 * Author: Joshua Standiford
 * Email: jstand1@umbc.edu
 * Desc: driver file for ray tracing program
 */

/*Standard includes*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <numeric>
#include <math.h>


/*Custom includes*/
#include "RayTracer.h"
#include "Polygon.h"
#include "Sphere.h"
#include "../common/slVector.H"


void printImage(void);

using namespace std;
int main() {

    int tokenSize = 8;
    ifstream file;
    RayTracer ray;
    string line;
    //string filepath = "tetra-3.nff";
    string filepath = "balls.nff";
    string tokens[8];
    vector<Polygon> polygons;
    vector<Sphere> spheres;

     /*
     * Calling inline functions
     * cross()
     * dot()
     */


    file.open(filepath.c_str());

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
                    ray.from = SlVector3(atof(tokens[1].data()), atof(tokens[2].data()), atof(tokens[3].data()));
                    break;
                }
                else if(!cmp.compare("at")){
                    ray.at = SlVector3(atof(tokens[1].data()), atof(tokens[2].data()), atof(tokens[3].data()));
                    break;
                }
                else if(!cmp.compare("up")){
                    ray.up = SlVector3(atof(tokens[1].data()), atof(tokens[2].data()), atof(tokens[3].data()));
                    break;
                }
                else if(!cmp.compare("angle")){
                    ray.angle = atoi(tokens[1].data());
                    break;
                }
                else if(!cmp.compare("hither")){
                    ray.hither = atoi(tokens[1].data());
                    break;
                }
                else if(!cmp.compare("resolution")){
                    ray.Nx = atoi(tokens[1].data());
                    ray.Ny = atoi(tokens[2].data());
                    break;
                }
                else if(!cmp.compare("f")){
                    ray.Rs = atof(tokens[1].data());
                    ray.Gs = atof(tokens[2].data());
                    ray.Bs = atof(tokens[3].data());
                    break;
                }
                //For populating Polygons
                else if(!cmp.compare("p")){
                    int polyCount = atoi(tokens[1].data());
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
                        polygon.insertVertices(atof(tokens[0].data()), atof(tokens[1].data()), atof(tokens[2].data()));
                    }
                    polygons.push_back(polygon);
                    break;
                }
                else if(!cmp.compare("s")){
                    spheres.push_back(Sphere(atof(tokens[1].data()), atof(tokens[2].data()), atof(tokens[3].data()), atof(tokens[4].data())));
                    break;
                }
            }
        }
    }
    file.close();
    ray.init();


    unsigned char pixels[ray.Nx][ray.Ny][3];

    for(int i = 0; i < ray.Nx; i++) {
        for (int j = 0; j < ray.Ny; j++) {
            /** Compute pixels here**/
            /* Calculate pixel location in world space
             * Calculate ray from eye point through pixel into scene
             * calculate ray-object intersections, choose closest T
             * set pixel to that color
             */

            for (int k = 0; k < polygons.size(); k++) {
                if (ray.triangleIntersect(polygons.at(k).getVectors().at(0), polygons.at(k).getVectors().at(1), polygons.at(k).getVectors().at(2), i, j)) {
                    pixels[j][i][0] = ray.Rs * 255;
                    pixels[j][i][1] = ray.Bs * 255;
                    pixels[j][i][2] = ray.Gs * 255;
                    break;
                }
                else{
                    //Background color
                    pixels[j][i][0] = 0.078 * 255;
                    pixels[j][i][1] = 0.361 * 255;
                    pixels[j][i][2] = 0.753 * 255;
                }
            }
        }
    }
    //;

    /** Write pixels out to file **/

    FILE *f = fopen("hide.ppm","wb");
    fprintf(f, "P6\n%d %d\n%d\n", ray.Nx, ray.Ny, 255);
    fwrite(pixels, 1, ray.Nx*ray.Ny*3, f);
    fclose(f);


    return 0;
}

