#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"


class camera{
public:
    point3 origin,lower_left_corner;
    vec3 horizontal,vertical;

    camera(){
        
        const double aspect_ratio = 16.0/9.0;
        double viewport_height = 2.0;
        double viewport_width = viewport_height * aspect_ratio;
        double focal_length = 1.0;

        origin = point3(0,0,0);
        horizontal = vec3(viewport_width, 0, 0);
        vertical = vec3(0,viewport_height,0);
        lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0,0,focal_length);
        //std::cout<<"Corner: "<<lower_left_corner<<std::endl;
    }
    int a = 0;
    ray get_ray(double v,double u) {
        ray r = ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
       
        //std::cout<<"Q1:"<< lower_left_corner + u * horizontal + v * vertical - origin << std::endl;
        //std::cout<<"Q2:"<<r.dir <<' '<<u*horizontal<<' '<<v*vertical<<std::endl;
        
        return r;
    } 
};

#endif