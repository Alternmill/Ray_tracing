#ifndef VEC3_H
#define VEC3_H

#include<cmath>
#include<iostream>

using std::sqrt;

class vec3{
public:
    double e[3];

    vec3() : e{0,0,0} {}
    vec3(double e1,double e2,double e3) :e{e1,e2,e3} {}

    double &x = e[0],&y = e[1],&z = e[2];

    //operators
    vec3 operator-()const {return vec3(-e[0],-e[1],-e[2]);}
    double operator[](int i)const {return e[i];}
    double& operator[](int i) {return e[i];}
    vec3& operator+=(const vec3 &v){
        e[0]+=v.e[0];
        e[1]+=v.e[1];
        e[2]+=v.e[2];
        return *this;
    }

    inline static vec3 random(){
        return vec3(random_double(),random_double(),random_double());
    }

    inline static vec3 random(double min, double max){
        return vec3(random_double(min,max),random_double(min,max),random_double(min,max));
    }

    vec3& operator*=(const double &d){
        e[0]*=d;
        e[1]*=d;
        e[2]*=d;
        return *this;
    }

    vec3& operator/=(const double &d){
        return *this *= (1.0/d);
    }

    vec3& operator=(const vec3& other){
        (*this).e[0] = other.e[0];
        (*this).x = (*this).e[0];
        (*this).e[1] = other.e[1];
        (*this).y = (*this).e[1];
        (*this).e[2] = other.e[2];
        (*this).z = (*this).e[2];
        return *this;
    }

    double length_sq() const{
        return e[0]*e[0]+e[1]*e[1]+e[2]*e[2];
    }

    double length(){
        return sqrt(length_sq());
    }
    
    bool near_zero(){
        double s = 1e-8;
        return (fabs(e[0])<s && fabs(e[1]) < s && fabs(e[2]) < s);
    }
    
}; 

inline std::ostream& operator<<(std::ostream& out,const vec3 &v){
    return out<<v.e[0]<<' '<<v.e[1]<<' '<<v.e[2];
}

inline vec3 operator + (const vec3& v,const vec3& u){
    return vec3(v.e[0]+u.e[0],v.e[1]+u.e[1],v.e[2]+u.e[2]);
}

inline vec3 operator -(const vec3& v,const vec3& u){
    return vec3(v.e[0]-u.e[0],v.e[1]-u.e[1],v.e[2]-u.e[2]);
}

inline vec3 operator *(const vec3& v,const vec3& u){
    return vec3(v.e[0]*u.e[0],v.e[1]*u.e[1],v.e[2]*u.e[2]);
}

inline vec3 operator *(const double& t,const vec3& v){
    return vec3(t*v.e[0],t*v.e[1],t*v.e[2]);
}

inline vec3 operator*(const vec3 &v, double t) {
    return t * v;
}

inline vec3 operator/(vec3 v, double t) {
    return (1.0/t) * v;
}

inline double dot(const vec3 &u, const vec3 &v) {
    return u.e[0] * v.e[0]
         + u.e[1] * v.e[1]
         + u.e[2] * v.e[2];
}

inline vec3 cross(const vec3 &u, const vec3 &v) {
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]
    );
}

vec3 reflect(const vec3& v, const vec3& n) {
    return v - 2*dot(v,n)*n;
}

inline vec3 unit_vector(vec3 v) {
    return v / v.length();
}

vec3 random_in_sphere(){
    while(1){
        vec3 p = vec3::random(-1,1);
        if(p.length_sq()<1)return p;
    }
}

vec3 random_unit_vector(){
    return unit_vector(random_in_sphere());
}

vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat){
    auto cos_theta = fmin(dot(-uv,n),1.0);
    vec3 r_out_perp = etai_over_etat * (uv + cos_theta*n);
    vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_sq())) * n;
    return r_out_perp + r_out_parallel;
}

using color = vec3;
using point3 = vec3;

#endif