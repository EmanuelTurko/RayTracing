#pragma once

#include "helper.h"
#include "hittable.h"

class Sphere : public Hittable {
public:
  Sphere(const point3 &center, double radius)
      : _center(center), _radius(std::fmax(0, radius)) {}

  auto hit(const Ray &ray,Interval interval,
           hitRecord &record) const -> bool override {
    vec3 oc = _center - ray.origin();
    auto a = ray.direction().lengthSquared();
    auto h = dot(ray.direction(), oc);
    auto c = oc.lengthSquared() - _radius * _radius;

    auto discriminant = h * h - a * c;
    if (discriminant < 0)
      return false;

    auto sqrtd = std::sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    auto root = (h - sqrtd) / a;
    if (!interval.sorrounds(root)) {
      root = (h + sqrtd) / a;
      if (!interval.sorrounds(root))
        return false;
    }

    record._t = root;
    record._point = ray.at(record._t);
    vec3 outwardNormal = (record._point - _center) / _radius;
    record.setFaceNormal(ray, outwardNormal);

    return true;
  }

private:
  point3 _center{};
  double _radius{};
};