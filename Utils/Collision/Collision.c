#include "Collision.h"

/**
 * Checks if rectangle a is in collision with rectangle b using AABB (Axis-Aligned Bounding Box) collision detection
 * method.
 *
 * @param a the rectangle a
 * @param b the rectangle b
 * @return 1 if the two rectangle are in collision, 0 otherwise
 */
int AABBCollisionTest(const SDL_FRect* a, const SDL_FRect* b)
{
	if (a->x + a->w < b->x || a->x > b->x + b->w || a->y + a->h < b->y || a->y > b->y + b->h)
	{return 0;}
	else
	{return 1;}
}

/**
 * Checks if a given rectangle is in collision with any rectangle from an array of rectangle.
 *
 * @param rectangle 	the given rectangle
 * @param rectArray 	the rectangle array
 * @param rectArraySize the size of the rectangle array
 * @return 1 if the given rectangle is in collision with any rectangle form the array, false otherwise
 */
int CheckCollisionWithMapRectArray(const SDL_FRect* rectangle, const SDL_FRect rectArray[], int rectArraySize)
{
	for (int i = 0; i < rectArraySize; ++i)
	{
		if (AABBCollisionTest(rectangle, &rectArray[i]))
		{return 1;}
	}
	return 0;
}
