#include "rtweekend.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"

int main(){

    // WORLD
    hittable_list world;
    world.add(make_shared<sphere>(point3(0,0,2), 1));
    world.add(make_shared<sphere>(point3(1.5,-0.3,2.5), 0.7));
    world.add(make_shared<sphere>(point3(-1.5,-0.3,2.5), 0.7));
    world.add(make_shared<sphere>(point3(-3,-0.5,3), 0.5));
    world.add(make_shared<sphere>(point3(3,-0.5,3), 0.5));
    world.add(make_shared<sphere>(point3(0,-100.5,10), 100));
    //world.add(make_shared<sphere>(point3(0,-1,10), 4));
   
    camera cam;

    cam.aspectRatio = 16.0/9.0;
    cam.imageW = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth = 50;

    cam.render(world);

    std::clog << "\rDone.             \n";

}