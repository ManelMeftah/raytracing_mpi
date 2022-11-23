#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

#include <iostream>

void write_color(std::ostream &out, color c) {
    // Write the translated [0,255] value of each color component.
    out << (int)(255 * c.x()) << ' '
        << (int)(255 * c.y()) << ' '
        << (int)(255 * c.z()) << '\n';
}

#endif
