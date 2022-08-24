#ifndef MATERIAL_H
#define MATERIAL_H

#include "usefullnums.h"
#include "hittable.h"

class material{
public:
    virtual bool scatter(
        const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered_ray
    ) const = 0;
}; 

class lambertian : public material{
public:
    color albedo;

    lambertian(const color& col) : albedo(col){}

    virtual bool scatter(
        const ray& r_in,const hit_record& rec,color& attenuatuion, ray& scattered
    )const override{
        vec3 scatter_dir = rec.normal + random_unit_vector();
        scattered = ray(rec.p,scatter_dir);
        if(scattered.dir.near_zero()){
            scatter_dir = rec.normal;
        }
        attenuatuion = albedo;
        return 1;
    }

};


class metal : public material{
public:
    color albedo;
    double fuzz;

    metal(const color& col,double f) : albedo(col),fuzz(f < 1 ? f : 1) {}

    virtual bool scatter(
        const ray& r_in,const hit_record& rec,color& attenuatuion, ray& scattered
    )const override{
        vec3 ref = reflect(unit_vector(r_in.direction()),rec.normal);
        scattered = ray(rec.p,ref + fuzz*random_in_sphere());
        attenuatuion = albedo;
        return (dot(scattered.direction(), rec.normal) > 0);
    }

};

//TODO:
//Different colors
class dielectric : public material{
public:
    double ir;

    dielectric(double index_of_refraction) : ir(index_of_refraction){}

    virtual bool scatter(
        const ray& r_in,const hit_record& rec,color& attenuatuion, ray& scattered
    )const override{
        attenuatuion = color(0.9,0.9,0.9);
        double refraction_ratio = rec.front_face ? (1.0/ir) : ir;

        vec3 unit_direction = unit_vector(r_in.direction());

        double cos_theta = fmin(dot(-unit_direction,rec.normal),1.0);
        double sin_theta = sqrt(1.0 - cos_theta*cos_theta);

        vec3 direction;
        bool cannot_refract = refraction_ratio * sin_theta > 1.0;
        
        if(cannot_refract)
            direction = reflect(unit_direction,rec.normal);
        else 
            direction = refract(unit_direction,rec.normal,refraction_ratio);

        scattered = ray(rec.p,direction);
        return true;
    }
};

#endif