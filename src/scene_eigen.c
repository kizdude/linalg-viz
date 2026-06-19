/* scene_eigen.c - visualize how a 2x2 matrix maps the unit circle to an
 * ellipse, and highlight directions that don't rotate (eigenvectors).
 *
 * The library doesn't compute eigenvectors yet, so this scene can start by
 * showing the unit-circle -> ellipse mapping (sampling directions and applying
 * M), then later highlight near-eigen directions where M*v stays parallel to v.
 */
#include "raylib.h"
#include "scenes.h"
#include "linalg/linalg.h"

void scene_eigen_draw(View v) {
    /* TODO (we'll pair on this, last):
     *   - sample directions around the unit circle
     *   - apply a fixed 2x2 M to each; draw the resulting ellipse
     *   - flag directions where M*v stays (nearly) parallel to v
     */
    (void)v;
    DrawText("scene_eigen: TODO", 12, 44, 18, (Color){180,180,190,255});
}
