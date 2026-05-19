#include "game.h"
#include "render.h"
#include "view.h"

int
main(void)
{
    state_t   s;
    SDL_Event ev;
    int       running;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("SDL_Init: %s", SDL_GetError());
        return (1);
    }
    s.win = SDL_CreateWindow("infinite", SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
    s.ren = SDL_CreateRenderer(s.win, -1, SDL_RENDERER_ACCELERATED);
    render_init(&s);

    running = 1;
    while (running) {
        while (SDL_PollEvent(&ev)) {
            if (ev.type == SDL_QUIT)
                running = 0;
            if (ev.type == SDL_KEYDOWN) {
                if (ev.key.keysym.sym == SDLK_ESCAPE)
                    running = 0;
                if (ev.key.keysym.sym == SDLK_UP)
                    view_pan(&s.view, 0, -0.1);
                if (ev.key.keysym.sym == SDLK_DOWN)
                    view_pan(&s.view, 0, 0.1);
                if (ev.key.keysym.sym == SDLK_LEFT)
                    view_pan(&s.view, -0.1, 0);
                if (ev.key.keysym.sym == SDLK_RIGHT)
                    view_pan(&s.view, 0.1, 0);
                if (ev.key.keysym.sym == SDLK_EQUALS)
                    view_zoom(&s.view, 0.9);
                if (ev.key.keysym.sym == SDLK_MINUS)
                    view_zoom(&s.view, 1.1);
                if (ev.key.keysym.sym == SDLK_m)
                    s.fractal = 0;
                if (ev.key.keysym.sym == SDLK_j)
                    s.fractal = 1;
                if (ev.key.keysym.sym == SDLK_b)
                    s.fractal = 2;
                if (ev.key.keysym.sym == SDLK_c)
                    s.colour_scheme = !s.colour_scheme;
            }
            if (ev.type == SDL_MOUSEBUTTONDOWN
                    && ev.button.button == SDL_BUTTON_LEFT
                    && s.fractal != 1) {
                s.julia_re = pixel_to_re(ev.button.x, &s.view);
                s.julia_im = pixel_to_im(ev.button.y, &s.view);
                s.fractal = 1;
            }
        }
        render_frame(&s);
    }
    render_free(&s);
    return (0);
}
