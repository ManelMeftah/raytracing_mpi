#include "color.h"
#include <fstream>
using namespace std;

void write_color(string fname, color c, int echParPixel) 
{
    double r = c.x();
    double g = c.y();
    double b = c.z();

    double scale = 1.0 / echParPixel;
    r*=scale;
    g*=scale;
    b*=scale;

    fstream f;
    f.open(fname, ios::app);
    r = (int)(256 * clamp(r, 0.0, 0.9));
    g =(int)(256 * clamp(g, 0.0, 0.9));
    b = (int)(256 * clamp(b, 0.0, 0.9));
    f<< r << " "<< g << " " << b <<endl; 
    f.close();
}
