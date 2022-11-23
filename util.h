#ifndef UTIL_H
#define UTIL_H

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>
#include <cstdlib>


// Usings

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constantess

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Fonctions

inline double degrees_to_radians(double degrees) 
{
    return degrees * pi / 180.0;
}

// [0, 1[
inline double random_double()
{
    return rand() / (RAND_MAX+1.0);
}
// [min, max[
inline double random_double(double min, double max)
{
    return min + (max-min)*random_double();
}

// clamp une valeur x a l'intervalle [min, max]
inline double clamp(double x, double min, double max)
{
    if(x<min)
        return min;
    if(x>max)
        return max;
    return x;
}


// Headers

#include "ray.h"
#include "vec3.h"


#endif
