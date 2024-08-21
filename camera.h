#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"

class camera{

    public:
        camera(){}

            // IMAGE
            int imageW = 100;
            double aspectRatio = 1;
            int samples_per_pixel = 10; // Count of random samples for each pixel
            int max_depth = 10; //MAX RAY BOUNCES

            // RENDER
            void render (const hittable& world){
                initialize();
                populatePixels();
                //double pixelsLength = pixels.size();
                //std::clog << "pixel array length: " << pixelsLength << std::endl;
                std::cout << "P3\n" << imageW << ' ' << pHeight << "\n255\n";
                    for (int i = 0; i < pHeight; i++) {
                         std::clog << "\rScanlines remaining: " << (pHeight - i) << '\n' << std::flush;
                        for (int j = 0; j < imageW; j++) {
                            int index = j+(imageW*i);
                           // std::clog << "pixel: " << pixels[index] << std::endl;
                            color pixel_color(0,0,0);
                            for (int sample = 0; sample < samples_per_pixel; sample++){
                                ray r = get_ray(j, i);
                                pixel_color += ray_color(r, max_depth, world);
                            }
                           // std::clog << "pixel color: " << pixel_color << std::endl;
                            write_color(std::cout, pixel_samples_scale * pixel_color);
                           
                        }
                    }
            }

            int populatePixels(){

                std::clog  << "imageH: " << imageH << " imageW: " << imageW << std::endl;
                for(int i = 0; i<imageH; i++){
                    for(int j = 0; j<imageW; j++){
                        point3 newPoint = topLeft + ((0.5*uDist)*vpRight) - ((0.5*vDist)*up) + (vpRight * (uLength*((double)j/imageW))) - (up*(vLength*((double)i/imageH)));
                        pixels[i*imageW + j] = newPoint;

                        //std::clog << "point loc: " << newPoint << std::endl;
                    
                    }
                }       
                return 0;
            };

            // Getter for pixels
            const std::vector<vec3>& getPixels() const {
                return pixels;
            }


    private:
        point3 center;
        vec3 forward;
        vec3 up;
        double focalLength;
        double pixel_samples_scale;
        
        double vpHeight;
        double vpWidth;
        int pHeight;
        
        double imageH;
        point3 topLeft;
        double uDist;
        double vDist;
        vec3 vpRight;
        double uLength;
        double vLength;
        std::vector<vec3> pixels;

        void initialize() {

            //Camera attribs
            pHeight = static_cast<int>(imageW /aspectRatio);
            center = point3(0,0,0);
            double focalLength = 1;
            int vpHeight = 2;
            double vpWidth = (double)vpHeight * ((double)imageW/pHeight);
            vec3 forward = vec3(0,0,1);
            up = vec3(0,1,0);
            pixel_samples_scale = 1.0 / samples_per_pixel;


            imageH = (double)imageW/aspectRatio;
            int pixelCount = (imageW*imageH);
            pixels.resize(pixelCount);
            
            std::clog << "pHeight: " << pHeight << std::endl;
            std::clog << "vpH: " << vpWidth << "imageW" << imageW << std::endl;
            std::clog << "vpWidth: " << vpWidth << std::endl;
            

            std::clog << "imageW: " << imageW << " imageH: " << imageH << std::endl;
            std::clog << "vpWidth: " << vpWidth << " vpHeight: " << vpHeight << std::endl;
            //Find VP origin & right vector

            point3 vpOrigin = center + (forward*focalLength);
             vpRight = cross(forward, up);

                std::clog << "vporigin: " << vpOrigin << ". vpRight: " << vpRight;
            
            //Finding Top Middle and Bottom Middle Point of VP
            point3 topMiddle = vpOrigin + ((0.5*vpHeight)*up);
            point3 bottomMiddle =  vpOrigin - ((0.5*vpHeight)*up);

               // std::cout << "topMiddle: " << topMiddle << ". bottomMiddle: " << bottomMiddle;

             topLeft = topMiddle - ((0.5*vpWidth)* vpRight);
            point3 topRight = topMiddle + ((0.5*vpWidth)* vpRight);
            
            point3 bottomLeft = bottomMiddle - ((0.5*vpWidth)* vpRight);
            point3 bottomRight = bottomMiddle + ((0.5*vpWidth)* vpRight);

                std::clog << "topLeft: " << topLeft << ". topRight: " << topRight << std::endl;
                std::clog << "bottomLeft: " << bottomLeft << ". bottomRight: " << bottomRight << std::endl;

            //Calculate distance along horizontal(u) and vertical(v) axes            
             uLength = (topLeft - topRight).length();
             vLength = (topLeft - bottomLeft).length();

               std::clog << "uLength: " << uLength << ". vLength: " << vLength << '\n';


            //Calculate distance between pixels
             uDist = (double)uLength/imageW;
             vDist = ((double)vLength/imageH);

            std::clog << "uDist: " << uDist << ". vDist: " << vDist << std::endl;

            
        }

        ray get_ray(int j, int i) const {
            // Constructs camera-orig to pixel ray + offset
            auto offset = sample_square();
            int index = j+(imageW*i);
            auto pixelSample = pixels[index] + (offset.y() *(vDist*vpRight)) + ( offset.x() * (uDist*up));
            auto rayDirection = pixelSample - center;
            return ray(center, rayDirection);

        }


        vec3 sample_square() const {
            // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
            return vec3(random_double() - 0.5, random_double() - 0.5, 0);
        }

        color ray_color(const ray& r, int depth, const hittable& world) {
        // If we've exceeded the ray bounce limit, no more light is gathered.
            if (depth <= 0)
                return color(0,0,0);

            hit_record rec;

            if (world.hit(r, interval(0.001, infinity), rec)) {
                // std::clog << "hit!";
                vec3 direction = randomOnHemisphere(rec.normal);
                return 0.5 * (ray_color(ray(rec.p, direction), depth-1, world));
            }

            vec3 unit_direction = unit_vector(r.direction());
            auto a = 0.5*(unit_direction.y() + 1.0);
            return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
        }
        


};

#endif
