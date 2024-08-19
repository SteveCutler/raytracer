#ifndef SPHERE_H
#define SPHERE_H

#include <cmath>
#include <iostream>
#include "vec3.h"
#include "ray.h"


class sphere {
    public: 
        sphere() {}
        sphere( const point3& origin, const double radius) : orig(origin), rad(radius) {}

    // EQUATION TO PLOT A SPHERE

    std::optional<point3> collision(ray ray){
        double rayOrigX = ray.origin().x();
        double rayOrigY = ray.origin().y();
        double rayOrigZ = ray.origin().z();

        double rayDirX = ray.direction().x();
        double rayDirY = ray.direction().y();
        double rayDirZ = ray.direction().z();

        double a = dot(ray.direction(), ray.direction());
        double b = 2*(dot(ray.direction(),(ray.origin()-orig)));
        double c = dot((ray.origin()-orig),(ray.origin()-orig)) - pow(rad,2);
        //double c = (pow(rayOrigX,2)+pow(rayOrigY,2)+pow(rayOrigZ,2)) + ((2*rayOrigX*orig.x())+(2*rayOrigY*orig.y())+(2*rayOrigZ*orig.z())) + (pow(orig.x(),2) + pow(orig.y(),2)+pow(orig.z(),2)) - pow(rad,2);
        
        double discrim = sqrt(pow(b,2) - (4*a*c));
        int hits;
        if(discrim > 0){
            //hits=2;
            point3 hit1 = ray.at(((-b + discrim)/(2*a))); 
            point3 hit2 = ray.at(((-b - discrim)/(2*a))); 
            //std::cout << "Your ray hits the sphere 2 times - at: " << hit1 << " and " << hit2 << std::endl;
            double hit1Length = (hit1-ray.origin()).length();
            double hit2Length = (hit2-ray.origin()).length();
            if(hit1Length>=hit2Length){
                return hit2;
            }else{
                return hit1;
            }
        } else if(discrim == 0){
            //hits=1;
            point3 hit = ray.at(((-b)/(2*a))); 
            
             //std::cout << "Your ray hits the sphere 1 time - at: " << hit1 << std::endl;
            return hit;
        } else {
           // hits=0;
            //std::cout << "Your ray doesn't hit the sphere :(" << std::endl;
            return std::nullopt;
        }
    };

     // Getter for origin
        const point3& getOrig() const {
            return orig;
        }

 
    

    private:
            point3 orig;
            double rad;
};



#endif