#pragma once
#ifndef SURFACE_H
#define SURFACE_H

#include "util.h"

struct contacte_rec {
    point3 p;
    vec3 normale;

    double t;
    bool face_avant;

    // Trouver la bonne normale 
    // si le produit scalaire est positif : le rayon est dans l'objet, la normale est négative
    // sinon: le rayon est en dehors de l'object, la normale est positive
    inline void set_face_normal(const ray& r, const vec3& normale_surface) 
    {
        face_avant = dot(r.dir(), normale_surface) < 0;
        normale = face_avant ? normale_surface :-normale_surface;
    }
};

class surface {
public:
	virtual bool contacte(const ray& r, double t_min, double t_max, contacte_rec& rec) const = 0;
	
};

#endif
