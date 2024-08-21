#ifndef HITTABLE_H
#define HITTABLE_H

#include "rtweekend.h"

class hit_record {

    public:
        point3 p;
        vec3 normal;
        double t;
        bool front_face;

        void set_face_normal(const ray& r, const vec3& outwardNormal){
            // sets the hit record normal vector

            front_face = dot(r.direction(), outwardNormal) < 0;
            normal = front_face ? outwardNormal : -outwardNormal;
        }
};

class hittable {
    public:
        virtual ~hittable() = default;

        virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const=0;
};

#endif