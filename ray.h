#pragma once

#include "vec3.h"

class Ray {
public:
  Ray() {}

  Ray(const point3 &origin, const vec3 &direction)
      : _origin(origin), _direction(direction) {}

  auto origin() const -> point3 { return _origin; }
  auto direction() const -> vec3 { return _direction; }

  auto at(double d) const -> point3 { return _origin + d * _direction; }

private:
  point3 _origin;
  vec3 _direction;
};
