#ifndef USEFULL_NUMS_H
#define USEFULL_NUMS_H

#include <cmath>
#include <memory>
#include <limits>
#include <cstdlib>

using std::make_shared;
using std::shared_ptr;
using std::sqrt;

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double deg_to_rad(double degrees){
    return degrees * pi / 180.0;
}

inline double random_double(){
    return rand()/(RAND_MAX + 1.0);
}

inline double random_double(double min,double max){
    return min + (max-min)*random_double();
}

inline double clump(double x,double min,double max){
    if(x<min)return min;
    if(x>max)return max;
    return x;
}

#include "ray.h"
#include "vec3.h"

#endif