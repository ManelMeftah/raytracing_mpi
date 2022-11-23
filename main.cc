#include "util.h"

#include "color.h"
#include "surface_list.h"
#include "sphere.h"
#include "camera.h"

#include <iostream>

//purple gradient for bg
color couleurRayon(const ray& r, const surface& monde) {
    contacte_rec rec;
    if (monde.contacte(r, 0, infinity, rec))
    {
        return 0.5 * (rec.normale + color(1,1,1));
    }
    vec3 dir_unitaire = unit_vector(r.dir());
    // t entre [0, 1]
    double t = 0.5*(dir_unitaire.y() + 1.0);
    // interpolation: (1-t) * startVal + t*endVal 
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5,0.2,1.0);
}

int main() {

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~IMAGE :~~~~~~~~~~~~~~~~~~~~~~~~~~
    //Img properties : 16:9 400 x 255 
    const double ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = (int)(image_width / ratio);
    const int echantillonsParPixel = 100;

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~MONDE :~~~~~~~~~~~~~~~~~~~~~~~~~~
    surface_list monde;
    monde.add(make_shared<sphere>(point3(0,0,-1), 0.5));
    monde.add(make_shared<sphere>(point3(0,-100.5,-1), 100));

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~CAMERA :~~~~~~~~~~~~~~~~~~~~~~~~~~
    camera cam;

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~RENDU :~~~~~~~~~~~~~~~~~~~~~~~~~~

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height-1; j >= 0; --j)
    {
        std::cerr << "\rLignes restantes : " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) 
        {
            color pixel_color(0,0,0);
            for(int k =0; k<echantillonsParPixel; k++)
            {
                auto u = double(i) / (image_width-1);
                auto v = double(j) / (image_height-1);
                // ray r(origin, basGauche + u*axeX + v*axeY);
                ray r = cam.getRay(u, v);
                pixel_color += couleurRayon(r, monde);
            }
            write_color(std::cout, pixel_color, echantillonsParPixel);            
        }
    }

    std::cerr << "\nOK.\n";
}
