#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

#include <iostream>

void write_color(std::ostream &out, color c, int echParPixel) {
    double r = c.x();
    double g = c.y();
    double b = c.z();

    double scale = 1.0 / echParPixel;
    r*=scale;
    g*=scale;
    b*=scale;

    // Write the translated [0,255] value of each color component.
    out << (int)(256 * clamp(r, 0.0, 0.9)) << ' '
        << (int)(256 * clamp(g, 0.0, 0.9)) << ' '
        << (int)(256 * clamp(b, 0.0, 0.9)) << '\n';
}

#endif
