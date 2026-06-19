/* scene_transform.c - apply an animated 2x2 matrix to the unit square / grid.
 */
#include "raylib.h"
#include "scenes.h"
#include "linalg/linalg.h"
#include <math.h>

void scene_transform_draw(View v, float t) {
    double corners[8] = { 0,1,1,0,
                          1,1,0,0 };
    Mat *P = mat_from_array(2, 4, corners);
    double ms[4] = { 1.0, -sin(t),
                    0.0,  1.0 };
    double mr[4] = { cos(t), -sin(t),
                    sin(t),  cos(t) };
    
    Mat *Ms = mat_from_array(2, 2, ms);
    Mat *Mr = mat_from_array(2, 2, mr);
    Mat *TPs = mat_mul(Ms, P);
    Mat *TPr = mat_mul(Mr, P);
    for (int j = 0; j < 4; ++j) {
        int k = (j + 1) % 4;
        Vector2 p0 = world_to_screen(v, mat_get(TPs, 0, j), mat_get(TPs, 1, j));
        Vector2 p1 = world_to_screen(v, mat_get(TPs, 0, k), mat_get(TPs, 1, k));
        DrawLineEx(p0, p1, 3.0f, YELLOW);
    }
    for (int j = 0; j < 4; ++j) {
        int k = (j + 1) % 4;
        Vector2 p0 = world_to_screen(v, mat_get(TPr, 0, j), mat_get(TPr, 1, j));
        Vector2 p1 = world_to_screen(v, mat_get(TPr, 0, k), mat_get(TPr, 1, k));
        DrawLineEx(p0, p1, 3.0f, Fade(GREEN, 0.5f));
    }
    for (int j = 0; j < 4; ++j) {
        int k = (j + 1) % 4;
        Vector2 p0 = world_to_screen(v, mat_get(P, 0, j), mat_get(P, 1, j));
        Vector2 p1 = world_to_screen(v, mat_get(P, 0, k), mat_get(P, 1, k));
        DrawLineEx(p0, p1, 3.0f, Fade(YELLOW, 0.25f));
    }

    mat_free(Ms);
    mat_free(Mr);
    mat_free(P);
    mat_free(TPs);
    mat_free(TPr);
}
