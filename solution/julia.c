#include "julia.h"

int
julia(double z_re, double z_im,
      double c_re, double c_im,
      int max_iter, double *mag_out)
{
    double re;
    double im;
    double new_re;
    double sq;
    int    i;

    re = z_re;   /* z starts at the pixel — not at zero as in Mandelbrot */
    im = z_im;
    i = 0;
    while (i < max_iter) {
        sq = re * re + im * im;
        if (sq > 4.0) {             /* |z|^2 > 4: point has escaped */
            if (mag_out)
                *mag_out = sq;      /* squared magnitude for smooth colouring */
            return (i);
        }
        new_re = re * re - im * im + c_re; /* real part of z^2 + c */
        im = 2.0 * re * im + c_im;         /* imaginary part — uses old re */
        re = new_re;
        i++;
    }
    if (mag_out)
        *mag_out = re * re + im * im;
    return (max_iter); /* never escaped: point is in the Julia set */
}
