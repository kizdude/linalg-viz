/* scenes.h - shared types and the per-scene draw interface.
 *
 * Each scene is just a function that draws into the current frame using the
 * shared View (a world<->screen mapping) so every scene shares the same
 * coordinate system and grid.
 */
#ifndef SCENES_H
#define SCENES_H

#include "raylib.h"

/* Maps math/world coordinates to screen pixels.
 * origin = the screen pixel where world (0,0) sits;
 * scale  = pixels per world unit. World +y points up (screen y is flipped). */
typedef struct {
    Vector2 origin;
    float   scale;
} View;

/* Convert a world point (x, y) to a screen pixel. Defined in main.c. */
Vector2 world_to_screen(View v, float x, float y);

/* Draw an arrow from world point (x0,y0) to (x1,y1). Defined in main.c. */
void draw_vector(View v, float x0, float y0, float x1, float y1, Color color);

/* The scenes. `t` is elapsed seconds (for animation). */
void scene_vectors_draw(View v);
void scene_transform_draw(View v, float t);
void scene_eigen_draw(View v);

#endif /* SCENES_H */
