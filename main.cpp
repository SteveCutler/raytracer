#include "rtweekend.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"

color ray_color(const ray& r, const hittable& world) {
    hit_record rec;
    if (world.hit(r, 0, infinity, rec)) {
        return 0.5 * (rec.normal + color(1,1,1));
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}


int main(){


    // IMAGE
    double aspectRatio = ((double)16.0/9.0);
    int pWidth = 400;
    int pHeight = static_cast<int>(pWidth /aspectRatio);
    pHeight = (pHeight < 1) ? 1 : pHeight;

    // WORLD
    hittable_list world;
    world.add(make_shared<sphere>(point3(0,0,-2), 1));
    world.add(make_shared<sphere>(point3(0,-100.5,-10), 100));
    //world.add(make_shared<sphere>(point3(0,-1,10), 4));
   
 
    //Camera attribs
    point3 cOrigin = vec3(0,0,0);
    vec3 cForward = vec3(0,0,-1);
    vec3 cUp = vec3(0,1,0);
    int vpHeight = 2;
    double focalLength = 1;

    //Camera object creation
    camera cam(cOrigin, cForward, cUp, vpHeight, pWidth, focalLength, aspectRatio);
    
    //Grab pixels via reference to save memory
    const std::vector<point3>& pixels = cam.getPixels();


   // RENDER
    double pixelsLength = pixels.size();
    //std::clog << "pixel array length: " << pixelsLength << std::endl;
    std::cout << "P3\n" << pWidth << ' ' << pHeight << "\n255\n";
    

    for (int i = 0; i < pHeight; i++) {
        
        // std::clog << "\rScanlines remaining: " << (pHeight - j) << '\n' << std::flush;

        for (int j = 0; j < pWidth; j++) {
            int index = j+(pWidth*i);   
            if (index >= pixels.size()) {
                std::clog << "skipping..." << '\n';
                continue; // Skip if index is out of bounds
            }
            //std::clog << "vp pixel coord: " << pixels[index] << '\n';
            auto newRay = ray(cOrigin,pixels[index]);
            color pixelColor = ray_color(newRay, world);
             write_color(std::cout, pixelColor);
        }
        //     if(hit){
        //     point3 hitPoint = rec.p;
           
        //     vec3 N = rec.normal;
        //     vec3 pixelColor = 0.5*color(N.x()+1, N.y()+1, N.z()+1);
        //    // auto pixelColor = color(normal);
        //     write_color(std::cout, pixelColor);
        //    } 

        //     else{
        //    // std::clog << "no hit" << std::endl;
        //     double a = ((double)index/pWidth)/pHeight;
        //     //std::clog << "a = " << a << std::endl;
        //     double bVal = (1-a);
        //     auto pixelColor = bVal*color(0.5, 0.7, 1.0) + color(1,1,1)*a;
        //    //auto pixel_color = color(double(i)/(image_width-1), double(j)/(image_height-1),0);
        //     write_color(std::cout, pixelColor);
        //    }
        

    }

    std::clog << "\rDone.             \n";

    
}