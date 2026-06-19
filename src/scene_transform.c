/* scene_transform.c - apply an animated 2x2 matrix to the unit square / grid.
 *
 * Build the transform with the linalg library (e.g. a 2x2 Mat, or compose
 * rotation/scale), apply it to a set of points, and draw original vs.
 * transformed with raylib. `t` is elapsed seconds for animation.
 */
#include "raylib.h"
#include "scenes.h"
#include "linalg/linalg.h"

void scene_transform_draw(View v, float t) {
    /* TODO (we'll pair on this):
     *   - build a 2x2 transform M (animate an entry with sin(t), or rotate)
     *   - take the unit square corners (and/or the basis vectors)
     *   - map each point p -> M p using the linalg Mat multiply
     *   - draw the original shape faint and the transformed shape bright
     */
    (void)v; (void)t;
    DrawText("scene_transform: TODO", 12, 44, 18, (Color){180,180,190,255});
}
