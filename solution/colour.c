#include <math.h>
#include "colour.h"

static uint32_t
hsv_to_rgb(double h, double s, double v)
{
    double c;
    double x;
    double m;
    double r;
    double g;
    double b;
    int    sector;

    c = v * s;                                           /* chroma: colour intensity */
    x = c * (1.0 - fabs(fmod(h / 60.0, 2.0) - 1.0));   /* secondary component */
    m = v - c;                                           /* brightness offset for all channels */
    sector = (int)(h / 60.0);                            /* which 60-degree slice of the wheel */
    r = g = b = 0.0;
    if (sector == 0) { r = c; g = x; }       /* 0-60:   red to yellow */
    else if (sector == 1) { r = x; g = c; }  /* 60-120: yellow to green */
    else if (sector == 2) { g = c; b = x; }  /* 120-180: green to cyan */
    else if (sector == 3) { g = x; b = c; }  /* 180-240: cyan to blue */
    else if (sector == 4) { r = x; b = c; }  /* 240-300: blue to magenta */
    else                  { r = c; b = x; }  /* 300-360: magenta to red */
    return ((uint32_t)(0xFF) << 24
        | (uint32_t)((r + m) * 255) << 16
        | (uint32_t)((g + m) * 255) << 8
        | (uint32_t)((b + m) * 255));
}

uint32_t
colour_linear(int iter, int max_iter)
{
    double t;
    double hue;

    if (iter == max_iter)
        return (0xFF000000);                /* black — point never escaped */
    t = (double)iter / (double)max_iter;    /* normalise to 0.0-1.0 */
    hue = t * 360.0;                        /* map to full colour wheel */
    return (hsv_to_rgb(hue, 0.8, 1.0));    /* fixed saturation and brightness */
}

uint32_t
colour_smooth(int iter, int max_iter, double sq_mag)
{
    double t;
    double hue;

    if (iter == max_iter)
        return (0xFF000000);
    t = (double)iter + 1.0 - log(log(sqrt(sq_mag))) / log(2.0);
    t = t / (double)max_iter;
    if (t < 0.0)
        t = 0.0;
    if (t > 1.0)
        t = 1.0;
    hue = t * 360.0;
    return (hsv_to_rgb(hue, 0.8, 1.0));
}
