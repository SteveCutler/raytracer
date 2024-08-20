#ifndef SPHERE_H
#define SPHERE_H

#include <cmath>
#include <iostream>
#include "rtweekend.h"
#include "ray.h"
#include "hittable.h"


class sphere: public hittable {
    public: 
        sphere() {}
        sphere( const point3& origin, const double radius) : orig(origin), rad(radius) {}


    //HIT FUNCTION
    bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const override{

        vec3 oc = orig - r.origin();
        auto a = r.direction().length_squared();
        auto h = dot(r.direction(), oc);
        auto c = oc.length_squared() - rad*rad;

        auto discriminant = h*h - a*c;
            if (discriminant < 0)
            return false;

        auto sqrtd = std::sqrt(discriminant);

        // Find the nearest root that lies in the acceptable range.
        auto root = (h - sqrtd) / a;
        if (root <= ray_tmin || ray_tmax <= root) {
            root = (h + sqrtd) / a;
            if (root <= ray_tmin || ray_tmax <= root)
                return false;
        }

        rec.t = root;
        rec.p = r.at(rec.t);
        rec.normal = (rec.p - orig) / rad;

        return true;
        // double rayOrigX = ray.origin().x();
        // double rayOrigY = ray.origin().y();
        // double rayOrigZ = ray.origin().z();

        // double rayDirX = ray.direction().x();
        // double rayDirY = ray.direction().y();
        // double rayDirZ = ray.direction().z();

        // vec3 oc = ray.origin()-orig;
        
        // double a = dot(ray.direction(), ray.direction());
        // double b = -2*(dot(ray.direction(),(oc)));
        // double c = dot((oc),(oc)) - pow(rad,2);
        // //double c = (pow(rayOrigX,2)+pow(rayOrigY,2)+pow(rayOrigZ,2)) + ((2*rayOrigX*orig.x())+(2*rayOrigY*orig.y())+(2*rayOrigZ*orig.z())) + (pow(orig.x(),2) + pow(orig.y(),2)+pow(orig.z(),2)) - pow(rad,2);
        
        // double discrim = sqrt(pow(b,2) - (4*a*c));

        // if(discrim > 0){
        //     //hits=2;
        //     double t1 = ((-b + discrim)/(2*a));
        //     double t2 = ((-b - discrim)/(2*a));

        //     point3 hit1 = ray.at(t1); 
        //     point3 hit2 = ray.at(t2); 
        //     //std::cout << "Your ray hits the sphere 2 times - at: " << hit1 << " and " << hit2 << std::endl;
        //     double hit1Length = (hit1-ray.origin()).length();
        //     double hit2Length = (hit2-ray.origin()).length();
        //     if(hit1Length>=hit2Length){
        //         rec.t=t2;
        //         rec.p=hit2;
        //         vec3 outwardNormal=(rec.p-orig)/rad;
        //         rec.set_face_normal(ray, outwardNormal);
        //         return true;
        //     }else{
        //         rec.t=t1;
        //         rec.p=hit1;
        //         vec3 outwardNormal=(rec.p-orig)/rad;
        //         rec.set_face_normal(ray, outwardNormal);
        //         return true;
        //     }
        // }
        // else if(discrim == 0)
        //     {
        //     double t = ((-b)/(2*a));
        //     point3 hit = ray.at(t); 
        //     rec.t=t;
        //     rec.p=hit;
            
        //     vec3 outwardNormal=(rec.p-orig)/rad;
        //     rec.set_face_normal(ray, outwardNormal);
        //     return true;
        //     }
        // else{
        //     return false;
        //     }
    }
   

    // Getter for origin
    const point3& getOrig() const {
        return orig;
    }
    

    private:
            point3 orig;
            double rad;
};



#endif