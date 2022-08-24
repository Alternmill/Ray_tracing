#include <iostream>
#include <fstream>

#include "usefullnums.h"

#include "color.h"
#include "sphere.h"
#include "hittable_list.h"
#include "camera.h"
#include "material.h"
using namespace std;
int gg = 0;
color ray_color(const ray& r,hittable_list hit_list,int depth){
    hit_record rec;
    
    if(depth <= 0){
        return color(0,0,0);
    }
    //cout<<"Q4:"<<r.dir<<endl;
    
    bool hit = hit_list.hit(r,0.001,infinity,rec);
    if(hit)
    {
        ray scattered;
        color attenuation;
        if(rec.mat_ptr -> scatter(r,rec,attenuation,scattered)){
            return attenuation * ray_color(scattered,hit_list,depth - 1);
        }
        return color(0,0,0);
        // point3 targ = rec.p + rec.normal + random_unit_vector();
        // return 0.5 * ray_color(ray(rec.p,targ - rec.p), hit_list,depth-1);
    }   
    vec3 unit_dir = unit_vector(r.direction());
    double t = (unit_dir.y+1)/2.0;
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}
const double aspect_ratio = 16.0/9.0;
const int im_width = 400, im_height = (double) im_width / aspect_ratio; 

const int samples_per_pixel = 100;
const int rendering_depth = 50;
int main(int argc, char *argv[]){
    
    //MATERIALS
    shared_ptr<metal> mat1 = make_shared<metal>(color(1,1,1));
    shared_ptr<lambertian> mat2 = make_shared<lambertian>(color(0.5,0,0.7));
    shared_ptr<lambertian> mat3 = make_shared<lambertian>(color(0.6,0.5,0));
    
    hittable_list world;
    world.add(make_shared<sphere>(point3(0.6,0,-1),0.5,mat1));
    world.add(make_shared<sphere>(point3(-0.6,0,-1),0.5,mat2));
    world.add(make_shared<sphere>(point3(0,-100.5,-1),100,mat3));

    camera cam;
    
    //RENDER
    ofstream outp;
    outp.open("image.ppm");
    outp<<"P3\n"<<im_width<<' '<<im_height<<"\n255\n";
    for(int i=im_height-1;i>=0;i--){
        cerr << "\rProgress: " << im_height - i <<'/'<<im_height << flush;
        for(int j=0;j<im_width;j++){   
            double v = (double)i/(im_height-1);
            double u = (double)j/(im_width-1);
            color col;
            for(int k=0;k<samples_per_pixel;k++){
                ray r = cam.get_ray(v + random_double()/(im_height-1),u + random_double()/(im_width-1));
                //ray r = ray(point3(v + random_double(),u + random_double(), 0), vec3(0,0,1));
                col += ray_color(r,world,rendering_depth);
            }
           
            //if(i == im_height - 1 && j ==0)
            //cout<<"Q3:"<<r.dir<<endl;

           //= ray_color(r,world);
            write_color(outp,col,samples_per_pixel);
        }
    }
    outp.close();
    return 0;
}