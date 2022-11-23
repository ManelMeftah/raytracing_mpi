#ifndef CYLINDER_H
#define CYLINDER_H

#include "util.h"

#include "surface.h"


class cylinder : public surface {
    public:
        cylinder() {}

        cylinder(double R, double r)
            : R(R), r(r) {};

        virtual bool contacte(
            const ray& r, double t_min, double t_max, contacte_rec& rec) const override;

    public:
        double R;
        double r
        
};


bool cylinder::contacte(const ray& r, double t_min, double t_max, contacte_rec& rec) const {
 
    // vec3 oc = r.orig() - center;
    // double a = r.dir().length_squared();
    // double half_b = dot(oc, r.dir());
    // double c = oc.length_squared() - radius*radius;

    // double x, y, z;
    // tmp = 

    // si le point de contacte est bien dans l'intervalle [t_min, t_max] on l"enregistre 
    double root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root) 
    {        
        // on verifie l'autre racine :
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root)
            return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    vec3 normale_surface = (rec.p - center) / radius;
    rec.set_face_normal(r, normale_surface);


    return true;
}


#endif
