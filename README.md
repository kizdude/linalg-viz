# linalg-viz

An interactive visualizer for the [linalg](../linalg) C library, built with
[raylib](https://www.raylib.com/). It renders core linear-algebra ideas using
the library's own math.

## Scenes

Press **1 / 2 / 3** to switch; **ESC** to quit.

1. **Vectors** — two vectors, their sum (with the parallelogram), and the dot &
   cross-product magnitude.
2. **Matrix transform** — an animated shear and rotation applied to the unit
   square via `mat_mul`.
3. **Eigenvectors** — the unit circle mapped to an ellipse, with the
   eigen-directions (where `M·v` stays parallel to `v`) highlighted.

## Build & run

Requires CMake and a C compiler (GCC/MinGW). raylib is downloaded and built
automatically on first configure (needs network once); the linalg library is
bundled as a git submodule.

```sh
# get the submodule if you cloned without --recursive
git submodule update --init --recursive

cmake -S . -B build -G "MinGW Makefiles"   # omit -G for the default generator
cmake --build build
./build/linalg_viz.exe
```

## Headless snapshot

For testing or screenshots without a keyboard, set `LINALG_VIZ_CAPTURE` to an
output path (and optionally `LINALG_VIZ_SCENE` to 1/2/3); the app renders that
scene, saves a PNG, and exits:

```sh
LINALG_VIZ_CAPTURE="$PWD/shot.png" LINALG_VIZ_SCENE=3 ./build/linalg_viz.exe
```

## Layout

```
src/main.c            window, loop, coordinate grid, scene switching
src/scene_*.c         the three scenes
external/linalg       the C library (git submodule)
```
