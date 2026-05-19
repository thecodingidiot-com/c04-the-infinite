#ifndef COLOUR_H
#define COLOUR_H

#include <stdint.h>

uint32_t colour_linear(int iter, int max_iter);
uint32_t colour_smooth(int iter, int max_iter, double sq_mag);

#endif
