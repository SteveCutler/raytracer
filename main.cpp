#include "color.h"
#include "vec3.h"
#include <iostream>
#include "ray.h"
#include "sphere.h"
#include "camera.h"

int main(){

    // Image
    int image_width = 256;
    int image_height = 256;

    // Ray
    //auto Ray = ray({0,0,0},{1.5,1,1});

    //Sphere
    auto Sphere = sphere({0,0,2}, 1);
 
    //Camera attribs
    point3 cOrigin = vec3(0,0,0);
    vec3 cForward = vec3(0,0,1);
    vec3 cUp = vec3(0,1,0);
    int vpHeight = 2;
    int pWidth = 400;
    double focalLength = 1;
    double aspectRatio = ((double)16.0/9.0);

    //Camera object creation
    camera cam(cOrigin, cForward, cUp, vpHeight, pWidth, focalLength, aspectRatio);
    //Grab pixels via reference to save memory
    const std::vector<point3>& pixels = cam.getPixels();


   // Render
   int pHeight = static_cast<int>(pWidth /aspectRatio);
//    std::clog << "Pheight = " << pHeight;
//    std::clog << "Pwidth = " << pWidth;

    double pixelsLength = pixels.size();
    std::clog << "pixel array length: " << pixelsLength << std::endl;
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
            std::optional<point3> hitLoc = Sphere.collision(newRay);

            if(hitLoc.has_value()){
            point3 hitPoint = hitLoc.value();
            std::clog << "hitLoc: " << hitPoint << std::endl;
            vec3 N = hitPoint - Sphere.getOrig().normalize();
            std::clog << "normal: " << N << std::endl;
            //std::clog << "hit at ray = " << newRay << std::endl;
            vec3 pixelColor = 0.5*color(N.x()+1, N.y()+1, N.z()+1);
           // auto pixelColor = color(normal);
            write_color(std::cout, pixelColor);
           } 

            else{
           // std::clog << "no hit" << std::endl;
            double a = ((double)index/pWidth)/pHeight;
            //std::clog << "a = " << a << std::endl;
            double bVal = (1-a);
            auto pixelColor = bVal*color(0.5, 0.7, 1.0) + color(1,1,1)*a;
           //auto pixel_color = color(double(i)/(image_width-1), double(j)/(image_height-1),0);
            write_color(std::cout, pixelColor);
           }
        }

    }

    std::clog << "\rDone.             \n";

    
}