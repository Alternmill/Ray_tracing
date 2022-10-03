#ifndef COLOR_H
#define COLOR_H

#include "usefullnums.h"
#include "bmp.h"

#include <iostream>

void write_color(BMP &image,color col,int ypos,int xpos,int samples_per_pixel = 1){
    uint32_t channels = image.bmp_info_header.bit_count / 8;

    image.data[channels * (ypos * image.bmp_info_header.width + xpos) + 0]=(int)(clump(255 * sqrt(col.e[2] / samples_per_pixel),0,255));
    image.data[channels * (ypos * image.bmp_info_header.width + xpos) + 1]=(int)(clump(255 * sqrt(col.e[1] / samples_per_pixel),0,255));
    image.data[channels * (ypos * image.bmp_info_header.width + xpos) + 2]=(int)(clump(255 * sqrt(col.e[0] / samples_per_pixel),0,255));
    
    if (channels == 4) {
        image.data[channels * (ypos * image.bmp_info_header.width + xpos) + 3] = 255;
    }
}

#endif