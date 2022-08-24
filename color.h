#ifndef COLOR_H
#define COLOR_H

#include "usefullnums.h"

#include <iostream>

void write_color(std::ostream &out,color col,int samples_per_pixel = 1){

    out <<(int)(clump(255 * sqrt(col.e[0] / samples_per_pixel),0,255))<<' '
        <<(int)(clump(255 * sqrt(col.e[1] / samples_per_pixel),0,255))<<' '
        <<(int)(clump(255 * sqrt(col.e[2] / samples_per_pixel),0,255))<<'\n';
}

#endif