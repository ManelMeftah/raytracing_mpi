#pragma once
#ifndef SPHERE_H
#define SPHERE_H

#include "util.h"

#include "surface.h"

class sphere : public surface {
public:
    sphere();

    sphere(point3 cen, double r);
     bool contacte(const ray& r, double t_min, double t_max, contacte_rec& rec) const override;
//      point3 center() const;
// 	vec3 radius() const;


public:
    point3 center;
    double radius;

};
#endif
