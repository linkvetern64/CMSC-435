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
    SlVector3 direction;
    SlVector3 origin;
    double beta, gamma, t, M;
    double a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0;

    SlVector3 Av, Bv, Cv;
    Av = SlVector3(0,1,1);
    Bv = SlVector3(1,0,-1);
    Cv = SlVector3(-1,-1,-1);

    unsigned char pixels[Nx][Ny][3];

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

            /* Vector D */
            direction = ((-d * w) + (u_pos * u) + (v_pos * v));

            /* Vector E*/
            origin = e;

            /** Compute Cramer Rule**/

            a0 = Av.x() - Bv.x();
            b0 = Av.y() - Bv.y();
            c0 = Av.z() - Bv.z();
            d0 = Av.x() - Cv.x();
            e0 = Av.y() - Cv.y();
            f0 = Av.z() - Cv.z();
            g0 = direction.x();
            h0 = direction.y();
            i0 = direction.z();
            j0 = Av.x() - origin.x();
            k0 = Av.y() - origin.y();
            l0 = Av.z() - origin.z();

            bool err = false;

            M = a0*(e0*i0 - h0*f0) + b0*(g0*f0 - d0*i0) + c0*(d0*h0 - e0*g0);

            /** Compute T **/

            t = -(f0*(a0*k0 - j0*b0) + e0*(j0*c0 - a0*l0) + d0*(b0*l0 - k0*c0)) / M;

            if( t < 0 || t > 100){
                err = true;
            }

            /** Compute Gamma **/

            gamma = (i0*(a0*k0 - j0*b0) + h0*(j0*c0 - a0*l0) + g0*(b0*l0 - k0*c0)) / M;

            if( gamma < 0 || gamma > 1){
                err = true;
            }

            /** Compute Beta **/

            beta =  (j0*(e0*i0 - h0*f0) + k0*(g0*f0 - d0*i0) + l0*(d0*h0 - e0*g0)) / M;

            if(beta < 0 || beta > (1 - gamma)){
                err = true;
            }

            if(!err){
                //set pixel color to triangle color
                pixels[j][i][1]= 1*255;

            }
            else{
                pixels[j][i][1]= 0*255;
                //set to background color
            }
        }
    }

    /** Write pixels out to file **/
    //ray.printImage();

    FILE *f = fopen("hide.ppm","wb");
    fprintf(f, "P6\n%d %d\n%d\n", Nx, Ny, 255);
    fwrite(pixels, 1, Nx*Ny*3, f);
    fclose(f);

    return 0;
}

