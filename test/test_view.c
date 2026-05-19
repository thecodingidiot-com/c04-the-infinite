#include <stdio.h>
#include <math.h>
#include "view.h"

static int g_passed = 0;
static int g_failed = 0;

static void
check_double(const char *label, double got, double expected, double tol)
{
    double diff = got - expected;
    if (diff < 0.0)
        diff = -diff;
    if (diff <= tol) {
        printf("  PASS  %s → %.6f\n", label, got);
        g_passed++;
    } else {
        printf("  FAIL  %s → got %.6f, expected %.6f\n", label, got, expected);
        g_failed++;
    }
}

int
main(void)
{
    view_t v;

    printf("Suite 2 — viewport mapping\n");

    view_init(&v);

    /* centre pixel maps to (center_re, center_im) */
    check_double("pixel_to_re(WIDTH/2)",
        pixel_to_re(WIDTH / 2, &v), v.center_re, 1e-12);
    check_double("pixel_to_im(HEIGHT/2)",
        pixel_to_im(HEIGHT / 2, &v), v.center_im, 1e-12);

    /* zoom in by 0.9 — scale shrinks by the same factor */
    double scale_before = v.scale;
    view_zoom(&v, 0.9);
    check_double("view_zoom(0.9) — scale",
        v.scale, scale_before * 0.9, 1e-15);

    /* centre unchanged by zoom */
    check_double("view_zoom(0.9) — center_re unchanged",
        v.center_re, -0.5, 1e-12);

    printf("\n%d passed, %d failed\n", g_passed, g_failed);
    return (g_failed > 0 ? 1 : 0);
}
