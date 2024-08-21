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
    bool hit(const ray& r, interval ray_t, hit_record& rec) const override{

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
        if (!ray_t.surrounds(root)) {
            root = (h + sqrtd) / a;
            if (!ray_t.surrounds(root))
                return false;
        }

        rec.t = root;
        rec.p = r.at(rec.t);
        rec.normal = (rec.p - orig) / rad;

        return true;
        
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