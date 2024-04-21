#ifndef RAY_CASTING_MAZE_COLLISION_H_
#define RAY_CASTING_MAZE_COLLISION_H_

#include <SDL.h>

/**
 * Checks if rectangle a is in collision with rectangle b using AABB (Axis-Aligned Bounding Box) collision detection
 * method.
 *
 * @param a the rectangle a
 * @param b the rectangle b
 * @return 1 if the two rectangle are in collision, 0 otherwise
 */
int AABBCollisionTest(const SDL_FRect* a, const SDL_FRect* b);

/**
 * Checks if a given rectangle is in collision with any rectangle from an array of rectangle.
 *
 * @param rectangle 	the given rectangle
 * @param rectArray 	the rectangle array
 * @param rectArraySize the size of the rectangle array
 * @return 1 if the given rectangle is in collision with any rectangle form the array, false otherwise
 */
int CheckCollisionWithMapRectArray(const SDL_FRect* rectangle, const SDL_FRect rectArray[], int rectArraySize);

#endif