/* main.c - window, main loop, coordinate grid, and scene switching.
 *
 * This is the app's plumbing. The interesting per-scene drawing lives in
 * scene_*.c. Press 1/2/3 to switch scenes; ESC to quit.
 */
#include "raylib.h"
#include "scenes.h"
#include "linalg/linalg.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define WIDTH  1000
#define HEIGHT 700

/* World<->screen mapping: world +y points up, so we subtract for screen y. */
Vector2 world_to_screen(View v, float x, float y) {
    return (Vector2){ v.origin.x + x * v.scale, v.origin.y - y * v.scale };
}

void draw_vector(View v, float x0, float y0, float x1, float y1, Color color) {
    Vector2 a = world_to_screen(v, x0, y0);
    Vector2 b = world_to_screen(v, x1, y1);
    DrawLineEx(a, b, 3.0f, color);
    /* arrowhead */
    Vector2 dir = { b.x - a.x, b.y - a.y };
    float len = sqrtf(dir.x * dir.x + dir.y * dir.y);
    if (len > 1e-3f) {
        dir.x /= len; dir.y /= len;
        Vector2 perp = { -dir.y, dir.x };
        float s = 12.0f;
        Vector2 tip = b;
        Vector2 left  = { b.x - dir.x * s + perp.x * s * 0.5f, b.y - dir.y * s + perp.y * s * 0.5f };
        Vector2 right = { b.x - dir.x * s - perp.x * s * 0.5f, b.y - dir.y * s - perp.y * s * 0.5f };
        DrawTriangle(tip, left, right, color);
    }
}

/* Draw a faint unit grid and the x/y axes. */
static void draw_grid_axes(View v) {
    Color faint = (Color){ 60, 60, 70, 255 };
    int span = 12;
    for (int i = -span; i <= span; i++) {
        Vector2 vstart = world_to_screen(v, (float)i, -span);
        Vector2 vend   = world_to_screen(v, (float)i,  span);
        DrawLineV(vstart, vend, faint);
        Vector2 hstart = world_to_screen(v, -span, (float)i);
        Vector2 hend   = world_to_screen(v,  span, (float)i);
        DrawLineV(hstart, hend, faint);
    }
    /* axes */
    DrawLineEx(world_to_screen(v, -span, 0), world_to_screen(v, span, 0), 2.0f, GRAY);
    DrawLineEx(world_to_screen(v, 0, -span), world_to_screen(v, 0, span), 2.0f, GRAY);
}

int main(void) {
    InitWindow(WIDTH, HEIGHT, "linalg-viz");
    SetTargetFPS(60);

    View view = { .origin = { WIDTH / 2.0f, HEIGHT / 2.0f }, .scale = 50.0f };

    int scene = 1;
    float t = 0.0f;

    /* Headless capture: if LINALG_VIZ_CAPTURE is set, render the scene given by
     * LINALG_VIZ_SCENE (default 1) for a few frames, save a PNG, and exit.
     * Lets the viz be snapshotted without a human at the keyboard. */
    const char *capture_path = getenv("LINALG_VIZ_CAPTURE");
    const char *capture_scene = getenv("LINALG_VIZ_SCENE");
    if (capture_scene) scene = atoi(capture_scene);
    int frame = 0;

    const char *titles[] = {
        "", "1: Vectors (add / dot / cross)", "2: Matrix transform", "3: Eigenvectors"
    };

    while (!WindowShouldClose()) {
        t += GetFrameTime();
        if (IsKeyPressed(KEY_ONE))   scene = 1;
        if (IsKeyPressed(KEY_TWO))   scene = 2;
        if (IsKeyPressed(KEY_THREE)) scene = 3;

        BeginDrawing();
        ClearBackground((Color){ 24, 24, 30, 255 });
        draw_grid_axes(view);

        switch (scene) {
            case 1: scene_vectors_draw(view);      break;
            case 2: scene_transform_draw(view, t); break;
            case 3: scene_eigen_draw(view);        break;
        }

        DrawText(titles[scene], 12, 12, 20, RAYWHITE);
        DrawText("press 1 / 2 / 3 to switch scenes", 12, HEIGHT - 28, 16, GRAY);
        DrawText(TextFormat("linalg %s", linalg_version()), WIDTH - 130, HEIGHT - 28, 16, GRAY);
        EndDrawing();

        if (capture_path) {
            /* let a couple of frames settle (animation uses t), then snapshot */
            if (++frame >= 30) {
                TakeScreenshot(capture_path);
                break;
            }
        }
    }

    CloseWindow();
    return 0;
}
