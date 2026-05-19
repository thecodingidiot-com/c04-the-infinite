#ifndef VIEW_H
#define VIEW_H

#include "game.h"

struct s_view {
    double center_re;
    double center_im;
    double scale;
};

void   view_init(view_t *v);
void   view_pan(view_t *v, double dre, double dim);
void   view_zoom(view_t *v, double factor);
double pixel_to_re(int x, view_t *v);
double pixel_to_im(int y, view_t *v);

#endif
