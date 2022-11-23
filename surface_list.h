#ifndef SURFACE_LIST_H
#define SURFACE_LIST_H
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

#include <memory>
#include <vector>


class surface_list : public surface  {
    public:
        surface_list() {}
        surface_list(shared_ptr<surface> objet) { add(objet); }

        void clear() { objets.clear(); }
        void add(shared_ptr<surface> objet) { objets.push_back(objet); }

        virtual bool contacte(
            const ray& r, double t_min, double t_max, contacte_rec& rec) const override;

    public:
        std::vector<shared_ptr<surface>> objets;
};


bool surface_list::contacte(const ray& r, double t_min, double t_max, contacte_rec& rec) const {
    contacte_rec temp_rec;
    bool isContacte = false;
    double plus_proche = t_max;
    
    // on verifie pour chaque objet de la liste s'il y a contacte 
    // avec r sachant que t_max est le plus proche pour l'instant
    for (const auto& objet : objets) 
    {
        if (objet->contacte(r, t_min, plus_proche, temp_rec)) 
        {
            isContacte = true;
            plus_proche = temp_rec.t;
            rec = temp_rec;
        }
    }

    return isContacte;
}


#endif
