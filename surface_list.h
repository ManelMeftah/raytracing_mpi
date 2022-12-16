#pragma once
#ifndef SURFACE_LIST_H
#define SURFACE_LIST_H

#include "util.h"

#include "surface.h"

#include <memory>
#include <vector>

class surface_list : public surface{
public:
    surface_list();
    surface_list(shared_ptr<surface> objet);

    void clear();
    void add(shared_ptr<surface> objet);
    bool contacte(
        const ray& r, double t_min, double t_max, contacte_rec& rec) const override;
public:
    std::vector<shared_ptr<surface>> objets;
};

#endif
