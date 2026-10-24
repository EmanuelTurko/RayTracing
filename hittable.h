#pragma once


#include "ray.h"
#include "interval.h"

class hitRecord{
    public:
      point3 _point;
      vec3 _normal;
      double _t;
      bool _frontFace;

      auto setFaceNormal(const Ray& ray, const vec3& outwardNormal) -> void {
        // Sets the hit record normal vector.
        // NOTE: the parameter `outwardNormal` is assumed to have unit length.

        _frontFace = dot(ray.direction(), outwardNormal) < 0;
        _normal = _frontFace? outwardNormal : -outwardNormal;
      }
};


class Hittable{
    public:
      virtual ~Hittable() = default;
      virtual auto hit(const Ray &ray, Interval interval,
                       hitRecord &record) const -> bool = 0;
};