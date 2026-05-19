#ifndef RENDER_H
#define RENDER_H

#include <SDL2/SDL.h>
#include "game.h"
#include "view.h"

struct s_state {
    SDL_Window   *win;
    SDL_Renderer *ren;
    SDL_Texture  *tex;
    uint32_t      pixels[WIDTH * HEIGHT];
    view_t        view;
    int           fractal;
    int           colour_scheme;
    double        julia_re;
    double        julia_im;
};

void render_frame(state_t *s);
void render_init(state_t *s);
void render_free(state_t *s);

#endif
