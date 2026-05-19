#include <stdio.h>
#include "mandelbrot.h"
#include "julia.h"

static int g_passed = 0;
static int g_failed = 0;

static void
check_int(const char *label, int got, int expected)
{
    if (got == expected) {
        printf("  PASS  %s → %d\n", label, got);
        g_passed++;
    } else {
        printf("  FAIL  %s → got %d, expected %d\n", label, got, expected);
        g_failed++;
    }
}

int
main(void)
{
    printf("Suite 1 — escape time\n");

    /* points inside the set: orbit never escapes */
    check_int("mandelbrot(0.0, 0.0, 100)",   mandelbrot(0.0, 0.0, 100, NULL),  100);

    /* points outside: orbit escapes immediately or very quickly */
    check_int("mandelbrot(3.0, 0.0, 100)",   mandelbrot(3.0, 0.0, 100, NULL),  1);
    check_int("mandelbrot(1.0, 1.0, 100)",   mandelbrot(1.0, 1.0, 100, NULL),  2);
    check_int("mandelbrot(0.5, 0.0, 100)",   mandelbrot(0.5, 0.0, 100, NULL),  5);

    /* burning ship — same escape condition, different iteration */
    check_int("burning_ship(0.0, 0.0, 100)", burning_ship(0.0, 0.0, 100, NULL), 100);
    check_int("burning_ship(3.0, 0.0, 100)", burning_ship(3.0, 0.0, 100, NULL), 1);

    /* julia: z starts at the pixel, c is fixed */
    /* z0 = (2.0, 2.0): |z0|^2 = 8 > 4, escapes immediately */
    check_int("julia(2.0, 2.0, -0.7, 0.27, 100)", julia(2.0, 2.0, -0.7, 0.27, 100, NULL), 0);

    printf("\n%d passed, %d failed\n", g_passed, g_failed);
    return (g_failed > 0 ? 1 : 0);
}
