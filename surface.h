#ifndef SURFACE_H
#define SURFACE_H
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



// tout object avec lequel il y a eu contacte avec un rayon
// pour P(t) : point de contacte, normale à l'objet, face avant

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
