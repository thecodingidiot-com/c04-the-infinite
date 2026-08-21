# c04-the-infinite

Companion repository for **c04 — The Infinite** at
[thecodingidiot.com](https://thecodingidiot.com).

---

## Follow my journey

Working through c04 alongside the implementation pages? Build the
renderer step by step, then run the tester.

Clone this repository and copy the test files into your working directory:

```bash
git clone https://github.com/thecodingidiot-com/c04-the-infinite.git
cp c04-the-infinite/test/test.sh ~/c04-practice/
cp c04-the-infinite/test/test_mandelbrot.c ~/c04-practice/
cp c04-the-infinite/test/test_view.c ~/c04-practice/
cd ~/c04-practice
bash test.sh
```

The tester compiles `mandelbrot.c`, `julia.c`, and `view.c` directly
into test binaries — no SDL2 required. This is possible because the
platform separation rule keeps those files free of SDL2 headers.

---

## Follow your journey

Building the renderer independently? Here is the full project brief.

**Target:** `./infinite` — an interactive SDL2 fractal renderer.
Compile with `gcc -Wall -Wextra -g -std=c99`, no warnings.

**Fractals:**
- Mandelbrot — `c` = pixel, $z_0 = 0$
- Julia — `c` fixed by mouse click, $z_0$ = pixel; left click in
  Mandelbrot mode picks the constant and switches to Julia view
- Burning Ship — same loop as Mandelbrot with `|re|` and `|im|` taken
  before each squaring

**Colour schemes:**
- Linear — escape count mapped to hue via HSV, full colour wheel
- Smooth — fractional escape value using final magnitude eliminates
  banding; press `C` to toggle

**Controls:**

| Key / action         | Effect                                  |
|----------------------|-----------------------------------------|
| Arrow keys           | Pan the viewport                        |
| `=` / `-`            | Zoom in / zoom out                      |
| `M`                  | Switch to Mandelbrot mode               |
| `J`                  | Switch to Julia mode (current constant) |
| `B`                  | Switch to Burning Ship mode             |
| `C`                  | Toggle linear / smooth colouring        |
| Left click           | Pick Julia constant, switch to Julia    |
| Escape / close       | Quit                                    |

**Platform separation rule:** `mandelbrot.c`, `julia.c`, `view.c`, and
`colour.c` must not include any SDL2 header. SDL2 belongs only in
`render.c` and `main.c`. This is what makes the tester work without SDL2.

**Build target:** `make re` must produce `./infinite`.

Use `solution/` to compare once you are done, not before.

---

## What the tester checks

**Check 1 — required files.** Verifies that all platform-independent
source and header files are present in the working directory.

**Check 2 — platform separation.** Scans `mandelbrot.c`, `julia.c`,
`view.c`, `colour.c`, and their headers for any SDL2 include. A hit
means the platform separation rule has been violated.

**Suite 1 — escape time.** Known inputs with precomputed expected
iteration counts for `mandelbrot()`, `julia()`, and `burning_ship()`.
All three functions take a `double *mag_out` parameter — pass `NULL`
where the magnitude is not needed. The escape condition is strictly
`sq > 4.0` (not `>= 4.0`); a `>=` in your code will produce off-by-one
failures.

**Suite 2 — viewport mapping.** Given a freshly initialised `view_t`,
verifies that `pixel_to_re(WIDTH/2, &v)` returns `center_re` and
`pixel_to_im(HEIGHT/2, &v)` returns `center_im`. Also verifies that
one `view_zoom(&v, 0.9)` step scales correctly.

---

## License

MIT License. See [LICENSE](LICENSE).
