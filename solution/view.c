#include "view.h"

void
view_init(view_t *v)
{
    v->center_re = -0.5;      /* set spans -2.5 to 1.0; -0.5 centres it on screen */
    v->center_im = 0.0;
    v->scale = 3.5 / WIDTH;   /* 3.5 complex units covers the interesting width */
}

void
view_pan(view_t *v, double dre, double dim)
{
    v->center_re += dre * WIDTH * v->scale;   /* dre=0.1 shifts 10% of screen width */
    v->center_im += dim * HEIGHT * v->scale;
}

void
view_zoom(view_t *v, double factor)
{
    v->scale *= factor;   /* factor < 1 zooms in, factor > 1 zooms out */
}

double
pixel_to_re(int x, view_t *v)
{
    return (v->center_re + (x - WIDTH / 2) * v->scale);
}

double
pixel_to_im(int y, view_t *v)
{
    return (v->center_im + (y - HEIGHT / 2) * v->scale);
}
