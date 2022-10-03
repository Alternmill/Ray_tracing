#include <iostream>
#include <fstream>
#include <chrono>

#include "usefullnums.h"
#include "color.h"
#include "sphere.h"
#include "hittable_list.h"
#include "camera.h"
#include "material.h"
#include "world_setting.h"
#include "bmp.h"

using namespace std;
int gg = 0;
color ray_color(const ray& r,hittable_list &hit_list,int depth){
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
const int rendering_depth = 25;
int main(int argc, char *argv[]){
    chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
    //MATERIALS
    shared_ptr<metal> mat_right = make_shared<metal>(color(0.4,0.6,1),0);
    shared_ptr<dielectric> mat_left  = make_shared<dielectric>(1.5);
    shared_ptr<lambertian> ground = make_shared<lambertian>(color(0.2,0.2,0.2));
    shared_ptr<lambertian> mat_back = make_shared<lambertian>(color(0.4,0.6,0.1));
    
    hittable_list world;
    get_test_world(world);

    
    //world.add(make_shared<sphere>(point3(-0.5,0,-1.5),0.5,mat_left));
    //world.add(make_shared<sphere>(point3(0,0,-1),0.5,mat_left));
    //world.add(make_shared<sphere>(point3(-0.3,0,-2),0.5,mat_back));
    

    point3 lookfrom(15,3,10);
    point3 lookat(0,0,-1);
    vec3 vup(0,1,0);
    double dist_to_focus = (lookfrom-lookat).length();
    double aperture = 0.0;
    camera cam(lookfrom,lookat,vup,30,aspect_ratio,aperture,dist_to_focus);
    
    //RENDER
    
    BMP image(im_width,im_height,1);
    chrono::high_resolution_clock::time_point last = t1;
    for(int i=im_height-1;i>=0;i--){
        chrono::high_resolution_clock::time_point ti = chrono::high_resolution_clock::now();
        auto tm_duration = chrono::duration_cast<chrono::milliseconds>(ti - last).count();
        auto tm_duration_total = chrono::duration_cast<chrono::milliseconds>(ti - t1).count();
        last = ti;
        tm_duration*=i;
        cerr << "\rProgress: " << im_height - i <<'/'<<im_height
        <<"    Left:"<<tm_duration/1000<<'.'<<tm_duration%1000<<" seconds"
        <<"    Total:"<<tm_duration_total/1000<<'.'<<tm_duration_total%1000<<" seconds"
        <<flush;
        for(int j=0;j<im_width;j++){   
            double v = (double)i/(im_height-1);
            double u = (double)j/(im_width-1);
            color col;
            for(int k=0;k<samples_per_pixel;k++){
                ray r = cam.get_ray(v + random_double()/(im_height-1),u + random_double()/(im_width-1));
                col += ray_color(r,world,rendering_depth);
            }
        
            write_color(image,col,i,j,samples_per_pixel);
        }
    }
    image.write("Test2.bmp"); 
    chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
    auto tm_duration = chrono::duration_cast<chrono::milliseconds>(t2 - t1).count();
    cout<<endl<<tm_duration/1000<<'.'<<tm_duration%1000<<" seconds"<<endl;
    return 0;
}