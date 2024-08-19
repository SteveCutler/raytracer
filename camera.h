#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"

class camera{

    public:
        camera(){}
        camera(const point3& origin, 
               const vec3& forward, 
               const vec3& up,
               const int vpHeight, 
               const int width, 
               const double focalLength,
               const double aspectRatio
               ) 
               : orig(origin), forward(forward), up(up), vpH(vpHeight), imageW(width), focalLength(focalLength), aspectRatio(aspectRatio)
               {
                     populatePixels();
                }


    //1. calculate the center of the viewport - simple
    //2. find the up and right vector's corresponding to the camera origin, the viewport origin, and the forward vector
    //3. using the height and width, map out the 4 corners of the viewport
    //4. using the aspect ratio, 0,0 and 1,1 and the width/height determine how far apart each pixel is
    //5. using this u and v number, and based on the orientation of the viewport, determine the location of each pixel
    //6. add these pixels to the pixel array.
    //7. cast rays from camera origin through these pixels
    //8. return colors based on viewport pixel height and add these to image output
    //9. integrate sphere so that if they hit the sphere return a color.
            

        int populatePixels(){
            int imageH = imageW/aspectRatio;
            int pixelCount = (imageW*imageH);
            pixels.resize(pixelCount);
            double vpW = (double)vpH * ((double)imageW/imageH);

            std::clog << "imageW: " << imageW << " imageH: " << imageH << std::endl;
            std::clog << "vpW: " << vpW << " vpH: " << vpH << std::endl;
            //Find VP origin & right vector

            point3 vpOrigin = orig + (forward*focalLength);
            point3 vpRight = cross(up, forward);

                std::clog << "vporigin: " << vpOrigin << ". vpRight: " << vpRight;
            
            //Finding Top Middle and Bottom Middle Point of VP
            point3 topMiddle = vpOrigin + ((0.5*vpH)*up);
            point3 bottomMiddle =  vpOrigin - ((0.5*vpH)*up);

               // std::cout << "topMiddle: " << topMiddle << ". bottomMiddle: " << bottomMiddle;

            point3 topLeft = topMiddle - ((0.5*vpW)* vpRight);
            point3 topRight = topMiddle + ((0.5*vpW)* vpRight);
            
            point3 bottomLeft = bottomMiddle - ((0.5*vpW)* vpRight);
            point3 bottomRight = bottomMiddle + ((0.5*vpW)* vpRight);

                std::clog << "topLeft: " << topLeft << ". topRight: " << topRight << std::endl;
                std::clog << "bottomLeft: " << bottomLeft << ". bottomRight: " << bottomRight << std::endl;

            //Calculate distance along horizontal(u) and vertical(v) axes            
            double uLength = (topLeft - topRight).length();
            double vLength = (topLeft - bottomLeft).length();

               std::clog << "uLength: " << uLength << ". vLength: " << vLength << '\n';


            //Calculate distance between pixels
            double uDist = (double)uLength/imageW;
            double vDist = 2*((double)vLength/imageH);

                std::clog << "uDist: " << uDist << ". vDist: " << vDist << std::endl;
            
            //std::clog << "imageW " << imageW << " imageH " << imageH;

            for(int i = 0; i<imageH; i++){
                for(int j = 0; j<imageW; j++){
                    point3 newPoint = topLeft + ((0.5*uDist)*vpRight) + ((-0.5*vDist)*up) + (vpRight * (uLength*((double)j/imageW))) - (up*(vLength*((double)i/imageH)));
                    //point3 newPoint = topLeft + (vpRight * (uDist * j)) - (up * (vDist * i));

                    pixels[i*imageW + j] = newPoint;
                   // std::clog << "new point " << newPoint << " addition to right: " << (vpRight * (uLength*((double)j/imageW))) << std::endl;
                   // std::clog << (up*(vLength*((double)i/imageH))) << std::endl;

                   // if(j == 0 ){
                   // std::clog << newPoint << std::endl;
                  //  }
                }
            }
            
            return 0;
        };

         // Getter for pixels
        const std::vector<vec3>& getPixels() const {
            return pixels;
        }


    private:
        point3 orig;
        vec3 forward;
        vec3 up;
        double focalLength;
        int vpH;
        int imageW;
        double aspectRatio;
        std::vector<vec3> pixels;
        


};

#endif
