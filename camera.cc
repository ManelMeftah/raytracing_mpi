#include "camera.h"
#include "vec3.h"

camera::camera()
        {
            double ratio = 16.0 / 9.0;
            double viewport_height = 2.0;
            double viewport_width = ratio * viewport_height;
            double focal_length = 1.0;

            origin = point3(0, 0, 0);
            axeX = vec3(viewport_width, 0, 0);
            axeY = vec3(0, viewport_height, 0);
            basGauche = origin - axeX/2 - axeY/2 - vec3(0, 0, focal_length);
        }

        ray camera::getRay(double u, double v) const
        {
            return ray(origin, basGauche + u*axeX + v*axeY - origin);
        }
