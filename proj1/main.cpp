/**
 * Author: Joshua Standiford
 * Email: jstand1@umbc.edu
 * Desc: driver file for ray tracing program
 */
#include "RayTracer.h"
#include "Shape.h"
using namespace std;
int main() {


    RayTracer ray;
    string filepath = "tetra-3.nff";
    //string filepath = "balls.nff";

    vector<Shape> shapes = ray.init(filepath);

    cout << shapes.size() << endl;


    unsigned char pixels[ray.Nx][ray.Ny][3];

    for(int i = 0; i < ray.Nx; i++) {
        for (int j = 0; j < ray.Ny; j++) {
            /** Compute pixels here**/
            /* Calculate pixel location in world space
            * Calculate ray from eye point through pixel into scene
            * calculate ray-object intersections, choose closest T
            * set pixel to that color
            */

            /** calculates pixel location in world space **/
            ray.u_pos = ray.L + (((ray.R - ray.L) * (i + 0.5)) / ray.Nx);
            ray.v_pos = ray.B + (((ray.T - ray.B) * (j + 0.5)) / ray.Ny);

            /* Vector D */
            ray.direction = ((-ray.d * ray.w) + (ray.u_pos * ray.u) + (ray.v_pos * ray.v));

            /* Vector E*/
            ray.origin = ray.e;

            /** Check each Shape object in the vector */
            for (int k = 0; k < shapes.size(); k++) {
                if(shapes[k].getType().compare("polygon")){
                    /*if(shapes.at(k).intersects(ray)){
                        pixels[j][i][0] = ray.Rs * 255;
                        pixels[j][i][1] = ray.Bs * 255;
                        pixels[j][i][2] = ray.Gs * 255;
                        break;
                    }
                    else{
                        pixels[j][i][0] = 0.078 * 255;
                        pixels[j][i][1] = 0.361 * 255;
                        pixels[j][i][2] = 0.753 * 255;
                    }*/
                }
            }
        }
    }


    /** Write pixels out to file **/

    FILE *f = fopen("hide.ppm","wb");
    fprintf(f, "P6\n%d %d\n%d\n", ray.Nx, ray.Ny, 255);
    fwrite(pixels, 1, ray.Nx*ray.Ny*3, f);
    fclose(f);


    return 0;
}

