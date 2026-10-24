#pragma once

#include "vec3.h"
#include "interval.h"

using color = vec3;

inline auto writeColor(std::ostream &out, const color &pixelColor) -> void {
  auto r = pixelColor.x();
  auto g = pixelColor.y();
  auto b = pixelColor.z();

  // Translate the [0,1] component values to the byte range [0,255].
  static const Interval intensity(0.000,0.999);
  auto rByte = static_cast<int>(256 * intensity.clamp(r));
  auto gByte = static_cast<int>(256 * intensity.clamp(g));
  auto bByte = static_cast<int>(256 * intensity.clamp(b));

  // Write out the pixel color components.
  out << rByte << ' ' << gByte << ' ' << bByte << '\n';
}