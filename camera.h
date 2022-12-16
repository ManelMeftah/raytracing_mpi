#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "util.h"
class camera {
private:
    point3 origin;
    point3 basGauche;
    vec3 axeX;
    vec3 axeY;
public:
     camera() ;

    ray getRay(double u, double v) const;
};
#endif