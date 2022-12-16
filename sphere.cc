#include "sphere.h"



sphere::sphere() {}

sphere::sphere(point3 cen, double r)
            : center(cen), radius(r) {};
// point3 sphere::center() const  { return cen; }
// double sphere::radius() const { return rad; }



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
