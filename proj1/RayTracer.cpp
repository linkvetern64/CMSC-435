//
// Created by Josh on 2/1/2017.
//

#include <iostream>
#include "RayTracer.h"

/**
 * Constructor of RayTracer class
 * Preconditions: None
 * Postconditions: RayTracer class will be initialized
 * @return None
 */
RayTracer::RayTracer() {
    R = G = B = 0;

}

/**
 * Destructor of RayTracer class
 */
RayTracer::~RayTracer() {}

void RayTracer::getBackgroundColor(){
    printf("RGB = (%d, %d, %d)\n", R, G, B);
}

void RayTracer::printImage(){
    unsigned char pixels[yres][xres][3];

    for(int i = 0; i < yres; i++){
        for(int j = 0; j < xres; j++){
            pixels[i][j][1] = 1 * 255;
        }
    }

    FILE *f = fopen("hide.ppm","wb");
    fprintf(f, "P6\n%d %d\n%d\n", yres, xres, 255);
    fwrite(pixels, 1, yres*xres*3, f);
    fclose(f);
}