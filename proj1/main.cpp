/**
 * Author: Joshua Standiford
 * Email: jstand1@umbc.edu
 * Desc: driver file for ray tracing program
 */
#include "RayTracer.h"
#include "Shape.h"

using namespace std;
int main(int argc, char *argv[]) {

    /**
     * Todo:  Set up generic fill color for each object
     *        Keep on optimizing fam
     */

    RayTracer ray;
    string filepath;
    vector<Shape *> polys;

    /** Assign filepath to argument, if no argument assign default tetra-3.nff*/
    if(argc > 1){
        filepath = argv[1];
    }
    else{
        filepath = "tetra-3.nff";
        //filepath = "balls.nff";
    }

    /** Creates redundant calculates and initializes camera basis*/
    ray.init(filepath);

    /** Pushes all active geometry into a vector<Shape>*/
    polys  = ray.getGeometry();
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

            bool inter = false;
            /** Check each Shape object in the vector */
            for (int k = 0; k < polys.size(); k++) {
                if(polys.at(k)->intersect(ray.direction, ray.origin)) {
                    pixels[j][i][0] = ray.Rs * 255;
                    pixels[j][i][1] = ray.Bs * 255;
                    pixels[j][i][2] = ray.Gs * 255;
                    inter = true;
                    break;
                }
            }
            if(!inter){
                pixels[j][i][0] = 0.078 * 255;
                pixels[j][i][1] = 0.361 * 255;
                pixels[j][i][2] = 0.753 * 255;
            }
        }
        cout << "Time : " << i << endl;
    }

    /** Write pixels out to file **/
    FILE *f = fopen("hide.ppm","wb");
    fprintf(f, "P6\n%d %d\n%d\n", ray.Nx, ray.Ny, 255);
    fwrite(pixels, 1, ray.Nx*ray.Ny*3, f);
    fclose(f);

    return 0;
}

