/**
 * Author: Joshua Standiford
 * Email: jstand1@umbc.edu
 * Desc: driver file for ray tracing program
 */
#include "RayTracer.h"
#include "Shape.h"

     /**
     * Todo:  Set up generic fill color for each object
     * Todo:  Set up T intersection value
     * Todo:  Texture class
     * Todo:  Keep on optimizing fam
     *
     * BUG: Calculate closest T value to prevent graphical glitches
     */
using namespace std;
int main(int argc, char *argv[]) {

    RayTracer ray;
    string filepath;
    vector<Shape *> polys;

    /** Assign filepath to argument, if no argument assign default tetra-3.nff*/
     argc > 1 ? filepath = argv[1] : filepath = "tetra-3.nff";

    filepath = "tetra-3.nff";

    /** Creates redundant calculates and initializes camera basis*/
    ray.init(filepath);

    /** Pushes all active geometry into a vector<Shape>*/
    polys  = ray.getGeometry();
    unsigned char pixels[ray.Nx][ray.Ny][3];

    /** Compute pixels here**/
    /* Calculate pixel location in world space
    * Calculate ray from eye point through pixel into scene
    * calculate ray-object intersections, choose closest T
    * set pixel to that color
    */
    for(int i = 0; i < ray.Nx; i++) {
        for (int j = 0; j < ray.Ny; j++) {
            /** calculates pixel location in world space **/
            ray.u_pos = ray.L + (((ray.R - ray.L) * (i + 0.5)) / ray.Nx);
            ray.v_pos = ray.B + (((ray.T - ray.B) * (j + 0.5)) / ray.Ny);

            /* Vector D */
            ray.direction = ((-ray.d * ray.w) + (ray.u_pos * ray.u) + (ray.v_pos * ray.v));

            /* Vector E*/
            ray.origin = ray.e;

            /* Temp Variables for intersection*/
            int t_ind = -1;
            double tmp_t = 100;

            /** Check each Shape object in the vector */
            for (int k = 0; k < polys.size(); k++) {
                if(polys.at(k)->intersect(ray.direction, ray.origin)) {
                    /** the lowest T value, determines closest object to camera */
                    if(tmp_t > polys.at(k)->t){
                        tmp_t = polys.at(k)->t;
                        t_ind = k;
                    }
                }
            }
            //If an intersection occurred, set pixel to that color.  Otherwise set to BG color
            if(t_ind >= 0){
                pixels[j][i][0] = polys.at(t_ind)->red * 255;
                pixels[j][i][1] = polys.at(t_ind)->green * 255;
                pixels[j][i][2] = polys.at(t_ind)->blue * 255;
            }
            else{
                pixels[j][i][0] = ray.BG_r * 255;
                pixels[j][i][1] = ray.BG_g * 255;
                pixels[j][i][2] = ray.BG_b * 255;
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

