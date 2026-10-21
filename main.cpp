#include "color.h"
#include "ray.h"
#include "iostream"

auto hitSphere(const point3& center, double radius, const Ray& r)->bool{

    vec3 oc = center - r.origin();
    auto a = dot(r.direction(),r.direction());
    auto b = -2.0*dot(r.direction(),oc);
    auto c = dot(oc,oc) - radius*radius;
    auto discriminant = b*b - 4*a*c;
    return discriminant >=0;
}
auto rayColor(const Ray& r) -> color {
    if(hitSphere(point3(0,0,-1),0.5,r))
        return color(1,0,0);

    vec3 unitDirection = unit(r.direction());
    auto a = 0.5*(unitDirection.y() + 1.0);
    return (1.0-a)*color(1.0,1.0,1.0) + a*color(0.5,0.7,1.0);
}

int main(){

    //  Image

    auto aspectRatio = 16.0/9.0;
    int imageWidth = 400;

    // Calculate the image height, and ensure that it's at least 1.
    int imageHeight = static_cast<int>(imageWidth/aspectRatio);
    imageHeight = imageHeight<1 ? 1: imageHeight;

    // Camera

    auto focalLegth = 1.0;
    auto viewportHeight = 2.0;
    auto viewportWidth = viewportHeight * static_cast<double>(imageWidth) /imageHeight;
    auto cameraCenter = point3();

    // Calculate the vectors across the horizontal and down the vertical
    // viewport edges.
    auto viewportU = vec3(viewportWidth,0,0);
    auto viewportV = vec3(0,-viewportHeight,0);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    auto pixelDeltaU = viewportU / imageWidth;
    auto pixelDeltaV = viewportV / imageHeight;

    // Calculate the location of the upper left pixel.
    auto viewportUpperLeft = cameraCenter - vec3(0,0,focalLegth) - viewportU / 2 - viewportV/2;
    auto pixel100Loc = viewportUpperLeft + 0.5 * (pixelDeltaU + pixelDeltaV);


    // Render


    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for(size_t j = 0; j < imageHeight; ++j){
        std::clog << "\rScanlines remaining: " << (imageHeight -j) << ' '<< std::flush;
        for(size_t i = 0; i < imageWidth; ++i){
            auto pixelCenter = pixel100Loc + (i * pixelDeltaU) + (j* pixelDeltaV);
            auto rayDirection = pixelCenter - cameraCenter;

            Ray r(cameraCenter,rayDirection);
            color pixelColor = rayColor(r);
        
            writeColor(std::cout,pixelColor);
        }
    }

    std::clog << "\rDone.                   \n"; }