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

    metal(const color& col) : albedo(col){}

    virtual bool scatter(
        const ray& r_in,const hit_record& rec,color& attenuatuion, ray& scattered
    )const override{
        vec3 ref = reflect(unit_vector(r_in.direction()),rec.normal);
        scattered = ray(rec.p,ref);
        attenuatuion = albedo;
        return (dot(scattered.direction(), rec.normal) > 0);
    }

};

#endif