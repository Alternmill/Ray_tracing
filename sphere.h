#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "usefullnums.h"

class sphere : public hittable{
public: 
    point3 center;
    double radius;
    shared_ptr<material> mat_ptr;

public:
    sphere();
    sphere(point3 center,double radius, shared_ptr<material> mat) : center(center),radius(radius),mat_ptr(mat){};

    virtual bool hit(
        const ray& r,double t_min,double t_max,hit_record& hit) const override;
};

bool sphere::hit(const ray& r,double t_min,double t_max,hit_record& hit) const {
    vec3 oc = r.origin() - center;
    double a = r.direction().length_sq();
    
    double half_b = dot(oc, r.direction());
    double c = oc.length_sq() - radius*radius;
    double discriminant = half_b*half_b - a*c;

    if(discriminant < 0) return false;
    double sqrt_d = sqrt(discriminant);

    double root = (-sqrt_d - half_b)/(a); 
    
    if(root < t_min || root > t_max){
        root = (sqrt_d - half_b)/(a);
        if(root < t_min || root > t_max){
            return false;
        }
    }

    hit.t = root;
    hit.p = r.at(root);
    vec3 outward_normal = (hit.p - center)/radius;
    hit.set_front_face(r,outward_normal);
    hit.mat_ptr = mat_ptr;
    return true;
}

#endif