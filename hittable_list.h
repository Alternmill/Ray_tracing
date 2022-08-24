#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

#include <vector>
#include <memory>

using std::shared_ptr;
using std::make_shared;

class hittable_list : public hittable{
public:
    std::vector<shared_ptr<hittable> > objects;

    hittable_list(){};
    hittable_list(shared_ptr<hittable> object){objects.push_back(object);}

    void clear(){objects.clear();}
    void add(shared_ptr<hittable> object){objects.push_back(object);}

    virtual bool hit(
        const ray& r,double t_min,double t_max,hit_record& hit)const override;
};

bool hittable_list::hit(const ray& r,double t_min,double t_max,hit_record& hit)const{
    hit_record temp_rec;
    bool hit_anyting = false;
    double closest = t_max;

    for(const auto& p:objects){
        if(p->hit(r,t_min,closest,temp_rec)){
            hit_anyting = true;
            closest = temp_rec.t;
            hit = temp_rec;
        }
    }

    return hit_anyting;
}

#endif