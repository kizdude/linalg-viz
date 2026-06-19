/* scene_vectors.c - visualize two vectors, their sum, and dot/cross products.
 *
 * Use the linalg library for the math (vec_dot, vec_cross, vec_norm via the
 * Mat vector helpers, or the gfx Vec3 helpers) and raylib + draw_vector() to
 * render. world_to_screen()/draw_vector() are provided in main.c.
 */
#include "raylib.h"
#include "scenes.h"
#include "linalg/linalg.h"

void scene_vectors_draw(View v) {
    /* TODO (we'll pair on this):
     *   - define two vectors a and b (in world units)
     *   - draw a (red) and b (green) from the origin with draw_vector()
     *   - draw a+b (yellow) and show the parallelogram
     *   - compute and print a.b (dot) and |a x b| (cross magnitude) with DrawText
     */
    (void)v;
    DrawText("scene_vectors: TODO", 12, 44, 18, (Color){180,180,190,255});
}
