#pragma once


#include "helper.h"

#include <array>
#include <cstddef>
class vec3;

using point3 = vec3;
class vec3 {
public:
  vec3() = default;
  vec3(double elem1, double elem2, double elem3)
      : _elem{elem1, elem2, elem3} {};

  auto x() const -> double { return _elem[0]; }
  auto y() const -> double { return _elem[1]; }
  auto z() const -> double { return _elem[2]; }

  auto operator-() const -> vec3 {
    return vec3(-_elem[0], -_elem[1], -_elem[2]);
  }
  auto operator[](int i) const -> double { return _elem[i]; }
  auto operator[](int i) -> double & { return _elem[i]; }
  auto operator+=(const vec3 &v) -> vec3 & {
    for (size_t i = 0; i < _elem.size(); ++i)
      _elem[i] += v._elem[i];
    return *this;
  }
  auto operator*=(double d) -> vec3 & {
    for (auto &elem : _elem)
      elem *= d;
    return *this;
  }
  auto operator/=(double d) -> vec3 & { return *this *= 1 / d; }
  auto length() const -> double { return std::sqrt(lengthSquared()); }
  auto lengthSquared() const -> double {
    return _elem[0] * _elem[0] + _elem[1] * _elem[1] + _elem[2] * _elem[2];
  }
  friend auto operator<<(std::ostream &out, const vec3 &v) -> std::ostream &;
  friend auto operator+(const vec3 &u, const vec3 &v) -> vec3;
  friend auto operator-(const vec3 &u, const vec3 &v) -> vec3;
  friend auto operator*(const vec3 &u, const vec3 &v) -> vec3;
  friend auto operator*(double d, const vec3 &v) -> vec3;
  friend auto operator*(const vec3 &v, double d) -> vec3;
  friend auto dot(const vec3 &u, const vec3 &v) -> double;
  friend auto cross(const vec3 &u, const vec3 &v) -> vec3;

private:
  std::array<double, 3> _elem{};
};

inline auto operator<<(std::ostream &out, const vec3 &v) -> std::ostream & {
  return out << v._elem[0] << ' ' << v._elem[1] << ' ' << v._elem[2];
}
inline auto operator+(const vec3 &u, const vec3 &v) -> vec3 {
  return vec3(u._elem[0] + v._elem[0], u._elem[1] + v._elem[1],
              u._elem[2] + v._elem[2]);
}
inline auto operator-(const vec3 &u, const vec3 &v) -> vec3 {
  return vec3(u._elem[0] - v._elem[0], u._elem[1] - v._elem[1],
              u._elem[2] - v._elem[2]);
}
inline auto operator*(const vec3 &u, const vec3 &v) -> vec3 {
  return vec3(u._elem[0] * v._elem[0], u._elem[1] * v._elem[1],
              u._elem[2] * v._elem[2]);
}
inline auto operator*(double d, const vec3 &v) -> vec3 {
  return vec3(d * v._elem[0], d * v._elem[1], d * v._elem[2]);
}
inline auto operator*(const vec3 &v, double d) -> vec3 { return d * v; }
inline auto operator/(const vec3 &v, double d) -> vec3 { return (1 / d) * v; }
inline auto dot(const vec3 &u, const vec3 &v) -> double {
  return u._elem[0] * v._elem[0] + u._elem[1] * v._elem[1] +
         u._elem[2] * v._elem[2];
}
inline auto cross(const vec3 &u, const vec3 &v) -> vec3 {
  return vec3(u._elem[1] * v._elem[2] - u._elem[2] * v._elem[1],
              u._elem[2] * v._elem[0] - u._elem[0] * v._elem[2],
              u._elem[0] * v._elem[1] - u._elem[1] * v._elem[0]);
}
inline auto unit(const vec3 &v) -> vec3 { return v / v.length(); }
