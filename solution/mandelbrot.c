#include "mandelbrot.h"

int
mandelbrot(double c_re, double c_im, int max_iter, double *mag_out)
{
    double re;
    double im;
    double new_re;
    double sq;
    int    i;

    re = 0.0;   /* z starts at zero: z0 = 0 + 0i */
    im = 0.0;
    i = 0;
    while (i < max_iter) {
        sq = re * re + im * im;
        if (sq > 4.0) {             /* |z|^2 > 4, i.e. |z| > 2: point has escaped */
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
    return (max_iter); /* never escaped: point is in the set */
}

int
burning_ship(double c_re, double c_im, int max_iter, double *mag_out)
{
    double re;
    double im;
    double new_re;
    double sq;
    int    i;

    re = 0.0;   /* z starts at zero, same as Mandelbrot */
    im = 0.0;
    i = 0;
    while (i < max_iter) {
        sq = re * re + im * im;
        if (sq > 4.0) {             /* |z|^2 > 4: point has escaped */
            if (mag_out)
                *mag_out = sq;
            return (i);
        }
        if (re < 0.0)
            re = -re;               /* |Re(z)| — fold negative real to positive */
        if (im < 0.0)
            im = -im;               /* |Im(z)| — fold negative imaginary to positive */
        new_re = re * re - im * im + c_re; /* real part of (|z|)^2 + c */
        im = 2.0 * re * im + c_im;         /* imaginary part — uses folded re */
        re = new_re;
        i++;
    }
    if (mag_out)
        *mag_out = re * re + im * im;
    return (max_iter); /* never escaped: point is in the set */
}
