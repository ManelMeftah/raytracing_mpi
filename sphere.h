#ifndef SPHERE_H
#define SPHERE_H
//==============================================================================================
// Originally written in 2016 by Peter Shirley <ptrshrl@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related and
// neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy (see file COPYING.txt) of the CC0 Public Domain Dedication
// along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
//==============================================================================================

#include "util.h"

#include "surface.h"


class sphere : public surface {
    public:
        sphere() {}

        sphere(point3 cen, double r)
            : center(cen), radius(r) {};

        virtual bool contacte(
            const ray& r, double t_min, double t_max, contacte_rec& rec) const override;

    public:
        point3 center;
        double radius;
        
};


bool sphere::contacte(const ray& r, double t_min, double t_max, contacte_rec& rec) const {
    vec3 oc = r.orig() - center;
    double a = r.dir().length_squared();
    double half_b = dot(oc, r.dir());
    double c = oc.length_squared() - radius*radius;

    double discriminant = half_b*half_b - a*c;

    if (discriminant < 0) 
        return false;

    double sqrtd = sqrt(discriminant);

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
