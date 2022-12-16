#include "ray.h"


ray::ray() {}
ray::ray(const point3& origin, const vec3& direction)
            : origin(origin), direction(direction)
        {}

        point3 ray::orig() const  { return origin; }
        vec3 ray::dir() const { return direction; }

        point3 ray::at(double t) const {
            return origin + t*direction;
        }
