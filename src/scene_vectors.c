/* scene_vectors.c - visualize two vectors, their sum, and dot/cross products. */
#include "raylib.h"
#include "scenes.h"
#include "linalg/linalg.h"
#include <stdio.h>

void scene_vectors_draw(View v) {
    /* Demonstrate vector addition, dot product, and cross product. */
    Vec3 a = { 2.0f, 1.0f, 0.0f };
    Vec3 b = { 1.0f, 3.0f, 0.0f };
    draw_vector(v, 0.0f, 0.0f, a.x, a.y, (Color){255,0,0,255});
    draw_vector(v, 0.0f, 0.0f, b.x, b.y, (Color){0,255,0,255});
    Vec3 sum = vec3_add(a, b);
    draw_vector(v, 0.0f, 0.0f, sum.x, sum.y, (Color){255,255,0,255});
    draw_vector(v, a.x, a.y, sum.x, sum.y, (Color){255,255,0,100});
    draw_vector(v, b.x, b.y, sum.x, sum.y, (Color){255,255,0,100});
    float dot = vec3_dot(a, b);
    Vec3 cross = vec3_cross(a, b);
    char buf[128];
    snprintf(buf, sizeof(buf), "a·b = %.2f", dot);
    DrawText(buf, 12, 70, 18, (Color){255,255,255,255});
    snprintf(buf, sizeof(buf), "|a x b| = %.2f", vec3_length(cross));
    DrawText(buf, 12, 90, 18, (Color){255,255,255,255});
}
