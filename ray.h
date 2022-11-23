#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
    public:
        ray() {}
        ray(const point3& origin, const vec3& direction)
            : origin(origin), direction(direction)
        {}

        point3 orig() const  { return origin; }
        vec3 dir() const { return direction; }

        point3 at(double t) const {
            return origin + t*direction;
        }

    public:
        point3 origin;
        vec3 direction;
};

#endif
