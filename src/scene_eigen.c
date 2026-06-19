/* scene_eigen.c - visualize how a 2x2 matrix maps the unit circle to an
 * ellipse, and highlight directions that don't rotate (eigenvectors).
 */
#include "raylib.h"
#include "scenes.h"
#include "linalg/linalg.h"
#include <math.h>

#define N 120

void scene_eigen_draw(View v) {
    double pts[2*N];
    for (int i = 0; i < N; ++i) {
        float th = 2.0f * PI * (float)i / (float)N;
        pts[i] = cosf(th);
        pts[N+i] = sinf(th);
    }
    Mat *C = mat_from_array(2, N, pts);

    double m[4] = { 2.0, 1.0,
                    1.0, 2.0 };
    Mat *M = mat_from_array(2, 2, m);
    Mat *E = mat_mul(M, C);

    DrawLineEx(world_to_screen(v, mat_get(C, 0, 0), mat_get(C, 1, 0)),
               world_to_screen(v, mat_get(C, 0, N-1), mat_get(C, 1, N-1)),
               2.0f, Fade(WHITE, 0.25f));
    for (int i = 0; i < N-1; ++i) {
        DrawLineEx(world_to_screen(v, mat_get(C, 0, i), mat_get(C, 1, i)),
                   world_to_screen(v, mat_get(C, 0, i+1), mat_get(C, 1, i+1)),
                   2.0f, Fade(WHITE, 0.25f));
    }
    DrawLineEx(world_to_screen(v, mat_get(E, 0, 0), mat_get(E, 1, 0)),
               world_to_screen(v, mat_get(E, 0, N-1), mat_get(E, 1, N-1)),
               2.0f, Fade(YELLOW, 0.75f));
    for (int i = 0; i < N-1; ++i) {
        DrawLineEx(world_to_screen(v, mat_get(E, 0, i), mat_get(E, 1, i)),
                   world_to_screen(v, mat_get(E, 0, i+1), mat_get(E, 1, i+1)),
                   2.0f, Fade(YELLOW, 0.75f));
    }

    for (int j = 0; j < N; ++j) {
        float vx = mat_get(C,0,j), vy = mat_get(C,1,j);
        float ex = mat_get(E,0,j), ey = mat_get(E,1,j);
        float cross = vx*ey - vy*ex;
        if (fabsf(cross) < 0.05f) {
            draw_vector(v, 0,0, ex, ey, Fade(ORANGE, 1.0f));
            draw_vector(v, 0,0, vx, vy, Fade(SKYBLUE, 0.75f));
        }
    }

    mat_free(C);
    mat_free(M);
    mat_free(E);
}
