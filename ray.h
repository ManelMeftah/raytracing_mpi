#pragma once
#ifndef RAY_H
#define RAY_H

#include "util.h"
#include "vec3.h"

class ray {
public:
	ray();
	ray(const point3& origin, const vec3& direction);
	point3 orig() const;
	vec3 dir() const;

	point3 at(double t) const;

public: 
	point3 origin;
	vec3 direction;
};
#endif
