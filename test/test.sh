#!/bin/bash

set -o pipefail

# ─────────────────────────────────────────────────────────────────────────────
# c04-the-infinite tester
# Run from your working directory alongside mandelbrot.c, julia.c, view.c,
# colour.c, mandelbrot.h, julia.h, view.h, colour.h, and game.h.
# No SDL2 required.
# ─────────────────────────────────────────────────────────────────────────────

CC="gcc"
CFLAGS="-Wall -Wextra -g -std=c99"
PASS=0
FAIL=0

pass() { echo "  PASS  $1"; PASS=$((PASS + 1)); }
fail() { echo "  FAIL  $1"; FAIL=$((FAIL + 1)); }

# ─────────────────────────────────────────────────────────────────────────────
# Check: required source files are present
# ─────────────────────────────────────────────────────────────────────────────
echo ""
echo "Check 1 — required files"

REQUIRED="mandelbrot.c mandelbrot.h julia.c julia.h view.c view.h colour.c colour.h game.h"
for f in $REQUIRED; do
    if [[ -f "$f" ]]; then
        pass "$f present"
    else
        fail "$f missing"
    fi
done

# ─────────────────────────────────────────────────────────────────────────────
# Check: SDL2 headers not present in platform-independent files
# ─────────────────────────────────────────────────────────────────────────────
echo ""
echo "Check 2 — platform separation (no SDL2 in core files)"

CORE_FILES="mandelbrot.c mandelbrot.h julia.c julia.h view.c view.h colour.c colour.h game.h"
SDL_CLEAN=true
for f in $CORE_FILES; do
    if [[ -f "$f" ]] && grep -q "SDL" "$f"; then
        fail "$f includes SDL2 — platform separation violated"
        SDL_CLEAN=false
    fi
done
if [[ "$SDL_CLEAN" == "true" ]]; then
    pass "no SDL2 includes in core files"
fi

# ─────────────────────────────────────────────────────────────────────────────
# Copy test source files into working directory (if run from test/ directly)
# ─────────────────────────────────────────────────────────────────────────────
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# ─────────────────────────────────────────────────────────────────────────────
# Suite 1 — escape time (mandelbrot, julia, burning_ship)
# ─────────────────────────────────────────────────────────────────────────────
echo ""
echo "Suite 1 — escape time"

$CC $CFLAGS \
    mandelbrot.c julia.c \
    "$SCRIPT_DIR/test_mandelbrot.c" \
    -I. -o _test_mandelbrot -lm 2>&1

if [[ $? -ne 0 ]]; then
    fail "compile test_mandelbrot"
else
    pass "compile test_mandelbrot"
    output=$(./_test_mandelbrot 2>&1)
    echo "$output" | grep -E "PASS|FAIL"
    if [[ $? -eq 0 ]]; then
        failed_count=$(echo "$output" | grep -c "FAIL" || true)
        if [[ "$failed_count" -eq 0 ]]; then
            pass "all escape-time tests passed"
        else
            fail "$failed_count escape-time test(s) failed"
        fi
    fi
fi

# ─────────────────────────────────────────────────────────────────────────────
# Suite 2 — viewport mapping (view_init, pixel_to_re, pixel_to_im, view_zoom)
# ─────────────────────────────────────────────────────────────────────────────
echo ""
echo "Suite 2 — viewport mapping"

$CC $CFLAGS \
    view.c \
    "$SCRIPT_DIR/test_view.c" \
    -I. -o _test_view -lm 2>&1

if [[ $? -ne 0 ]]; then
    fail "compile test_view"
else
    pass "compile test_view"
    output=$(./_test_view 2>&1)
    echo "$output" | grep -E "PASS|FAIL"
    if [[ $? -eq 0 ]]; then
        failed_count=$(echo "$output" | grep -c "FAIL" || true)
        if [[ "$failed_count" -eq 0 ]]; then
            pass "all viewport tests passed"
        else
            fail "$failed_count viewport test(s) failed"
        fi
    fi
fi

# ─────────────────────────────────────────────────────────────────────────────
# Cleanup
# ─────────────────────────────────────────────────────────────────────────────
rm -f _test_mandelbrot _test_view

# ─────────────────────────────────────────────────────────────────────────────
# Summary
# ─────────────────────────────────────────────────────────────────────────────
echo ""
echo "─────────────────────────────────────────"
echo "  $PASS passed   $FAIL failed"
echo "─────────────────────────────────────────"
echo ""

[[ "$FAIL" -eq 0 ]]
