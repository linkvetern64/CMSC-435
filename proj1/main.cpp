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

/*Custom includes*/
#include "RayTracer.h"
#include "Polygon.h"
#include "../common/slVector.H"
#include "../common/slTransform.H"
#include "../common/slIO.H"
//#include "../common/CImg.h"


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
                    break;
                }
                else if(!cmp.compare("at")){
                    ray.Ax = stof(tokens[1]);
                    ray.Ay = stof(tokens[2]);
                    ray.Az = stof(tokens[3]);
                    break;
                }
                else if(!cmp.compare("up")){
                    ray.Ux = stof(tokens[1]);
                    ray.Uy = stof(tokens[2]);
                    ray.Uz = stof(tokens[3]);
                    break;
                }
                else if(!cmp.compare("angle")){
                    ray.angle = stoi(tokens[1]);
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


    ray.printImage();

    return 0;
}

