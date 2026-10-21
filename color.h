#pragma once


#include "vec3.h"


using color = vec3;

auto writeColor(std::ostream& out, const color& pixelColor) -> void{
    auto r = pixelColor.x();
    auto g = pixelColor.y();
    auto b = pixelColor.z();

    // Translate the [0,1] component values to the byte range [0,255].
    int rByte = static_cast<int>(255.999*r);
    int gByte = static_cast<int>(255.999*g);
    int bByte = static_cast<int>(255.999*b);

    // Write out the pixel color components.
    out << rByte << ' ' << gByte << ' ' << bByte << '\n';
}