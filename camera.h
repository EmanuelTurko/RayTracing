#pragma once

#include "color.h"
#include "helper.h"
#include "hittable.h"

class Camera {

public:
  auto render(const Hittable &world) -> void {

    initialize();
    std::cout << "P3\n" << _imageWidth << ' ' << _imageHeight << "\n255\n";

    for (int j = 0; j < _imageHeight; ++j) {
      std::clog << "\rScanlines remaining: " << (_imageHeight - j) << ' '
                << std::flush;
      for (int i = 0; i < _imageWidth; ++i) {
        color pixelColor(0,0,0);
        for(int sample = 0; sample < _samplesPerPixel;++sample){
            Ray ray = getRay(i,j);
            pixelColor += rayColor(ray,world);
        }
        writeColor(std::cout, _pixelSamplesScale * pixelColor);
      }
    }

    std::clog << "\rDone.                   \n";
  }

  auto setAspectRatio(double aspectRatio) -> void {
    _aspectRatio = aspectRatio;
  }
  auto setImageWidth(int imageWidth) -> void { _imageWidth = imageWidth; }
  auto setSamplesPerPixel(int samplesPerPixel) -> void {_samplesPerPixel = samplesPerPixel;}

private:
  double _aspectRatio{1.0};   // Ratio of image width over height
  int _imageWidth{100};       // Rendered image width in pixel count
  int _samplesPerPixel{10};   // Count of random samples for each pixel
  int _imageHeight{};         // Rendered image height
  double _pixelSamplesScale{}; // Color scale factor for a sum of pixel samples
  point3 _center{};           // Camera center
  point3 _pixel100Location{}; // Location of pixel 0, 0
  vec3 _pixelDeltaH{};        // Offset to pixel to the right - horizontal
  vec3 _pixelDeltaV{};        // Offset to pixel below - vertical

  auto initialize() -> void {
    _imageHeight = static_cast<int>(_imageWidth) / _aspectRatio;
    _imageHeight = _imageHeight < 1 ? 1 : _imageHeight;

    _pixelSamplesScale = 1.0 / _samplesPerPixel;
    _center = point3();

    auto focalLegth = 1.0;
    auto viewportHeight = 2.0;
    auto viewportWidth =
        viewportHeight * static_cast<double>(_imageWidth) / _imageHeight;
    auto cameraCenter = point3();

    // Calculate the vectors across the horizontal and down the vertical
    // viewport edges.
    auto viewportH = vec3(viewportWidth, 0, 0);
    auto viewportV = vec3(0, -viewportHeight, 0);

    // Calculate the horizontal and vertical delta vectors from pixel to
    // pixel.
    _pixelDeltaH = viewportH / _imageWidth;
    _pixelDeltaV = viewportV / _imageHeight;

    // Calculate the location of the upper left pixel.
    auto viewportUpperLeft =
        cameraCenter - vec3(0, 0, focalLegth) - viewportH / 2 - viewportV / 2;
    _pixel100Location = viewportUpperLeft + 0.5 * (_pixelDeltaH + _pixelDeltaV);
  }

  auto rayColor(const Ray &ray, const Hittable &world) -> color {

    hitRecord record{};
    if (world.hit(ray, Interval(0, infinity), record))
      return 0.5 * (record._normal + color(1, 1, 1));

    vec3 unitDirection = unit(ray.direction());
    auto a = 0.5 * (unitDirection.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
  }
  auto sampleSquare() const -> vec3{
    // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit
    // square.
    return vec3(randomDouble() - 0.5,randomDouble() - 0.5,0);
  }
  auto getRay(int i,int j) const -> Ray{
    // Construct a camera ray originating from the origin and directed at
    // randomly sampled point around the pixel location i, j.

    auto offset = sampleSquare();
    auto pixelSample = _pixel100Location
    + ((i + offset.x()) * _pixelDeltaH)
    + ((j + offset.y()) * _pixelDeltaV);

    auto rayOrigin = _center;
    auto rayDirection = pixelSample - rayOrigin;

    return Ray(rayOrigin,rayDirection);
  }
};