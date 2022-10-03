#ifndef WORLD_SETTING_H
#define WORLD_SETTING_H

#include "usefullnums.h"
#include "color.h"
#include "sphere.h"
#include "hittable_list.h"
#include "camera.h"
#include "material.h"

void get_test_world(hittable_list &world){
    
    shared_ptr<lambertian> ground = make_shared<lambertian>(color(0.2,0.2,0.2));
    shared_ptr<metal> mat_right = make_shared<metal>(color(0.4,0.6,1),0);
    world.add(make_shared<sphere>(point3(0,-1000.5,-1),1000,ground));

    for(int i = -8; i <= 8; i+=2){
        for(int j = -8; j <= 8; j+=2){
            double a = random_double();
            if(abs(i)<=3 && abs(j)<=3)continue;
            if(a<0.4){
                world.add(make_shared<sphere>(point3(i + random_double(),0,j + random_double()),0.5,make_shared<lambertian>(color(
                    random_double(),random_double(),random_double()))));
            }else{
                if(a<0.90){
                    world.add(make_shared<sphere>(point3(i + random_double(),0,j + random_double()),0.5,make_shared<metal>(color(
                        random_double(),random_double(),random_double()),random_double()/5)));
                }else{
                    world.add(make_shared<sphere>(point3(i + random_double(),0,j + random_double()),0.5,make_shared<dielectric>(1.5)));
                }
            }
        }
    }

    world.add(make_shared<sphere>(point3(0,3.5,0),4,mat_right));
}


#endif