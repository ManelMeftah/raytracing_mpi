#include "surface_list.h"


        surface_list::surface_list() {}
        surface_list::surface_list(shared_ptr<surface> objet) { add(objet); }

        void surface_list::clear() { objets.clear(); }
        void surface_list::add(shared_ptr<surface> objet) { objets.push_back(objet); }


        


bool surface_list::contacte(const ray& r, double t_min, double t_max, contacte_rec& rec) const
{      
    contacte_rec temp_rec;//tempom
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
