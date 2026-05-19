#include "render.h"
#include "mandelbrot.h"
#include "julia.h"
#include "colour.h"

void
render_init(state_t *s)
{
    s->tex = SDL_CreateTexture(s->ren,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        WIDTH, HEIGHT);
    if (!s->tex)
        SDL_Log("SDL_CreateTexture: %s", SDL_GetError());
    view_init(&s->view);
    s->fractal = 0;
    s->colour_scheme = 0;
    s->julia_re = -0.7;
    s->julia_im = 0.27;
}

void
render_frame(state_t *s)
{
    int      x;
    int      y;
    int      i;
    double   re;
    double   im;
    double   mag;
    uint32_t colour;

    y = 0;
    while (y < HEIGHT) {
        x = 0;
        while (x < WIDTH) {
            re = pixel_to_re(x, &s->view);
            im = pixel_to_im(y, &s->view);
            if (s->fractal == 0)
                i = mandelbrot(re, im, MAX_ITER, &mag);            /* c = pixel, z0 = 0 */
            else if (s->fractal == 1)
                i = julia(re, im, s->julia_re, s->julia_im,        /* z0 = pixel, c = click */
                          MAX_ITER, &mag);
            else
                i = burning_ship(re, im, MAX_ITER, &mag);
            if (s->colour_scheme == 0)
                colour = colour_linear(i, MAX_ITER);
            else
                colour = colour_smooth(i, MAX_ITER, mag);
            s->pixels[y * WIDTH + x] = colour;
            x++;
        }
        y++;
    }
    SDL_UpdateTexture(s->tex, NULL, s->pixels, WIDTH * sizeof(uint32_t));
    SDL_RenderClear(s->ren);
    SDL_RenderCopy(s->ren, s->tex, NULL, NULL);
    SDL_RenderPresent(s->ren);
}

void
render_free(state_t *s)
{
    SDL_DestroyTexture(s->tex);
    SDL_DestroyRenderer(s->ren);
    SDL_DestroyWindow(s->win);
    SDL_Quit();
}
