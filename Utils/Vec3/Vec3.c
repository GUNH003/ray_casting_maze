#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "Vec3.h"
#include "../ErrorHandler/ErrorHandler.h"
#include "../Comparator/Comparator.h"

/**
 * Creates a 3D vector.
 *
 * @param x the x component of the vector
 * @param y the y component of the vector
 * @param z the z component of the vector
 * @return a Vec3 object
 */
Vec3* Vec3D(float x, float y, float z)
{
	Vec3* vector = (Vec3*)calloc(1, sizeof(Vec3));
	if (vector == NULL)
	{ ErrorHandler(MEMORY_ALLOCATION_ERROR); }
	vector->x = x;
	vector->y = y;
	vector->z = z;
	return vector;
}

/**
 * Calculates the dot product of two vectors. The dot product is used to calculate the projection of a on b.
 *
 * @param a vector a
 * @param b vector b
 * @return the result of the dot product
 */
float Dot3D(const Vec3* a, const Vec3* b)
{
	if (a == NULL || b == NULL)
	{ ErrorHandler(ACCESSING_NULL_POINTER_ERROR); }
	return (a->x) * (b->x) + (a->y) * (b->y) + (a->z) * (b->z);
}

/**
 * Translates vector a by vector b. In-place modification is made to the translated vector.
 *
 * @param a the vector to be translated
 * @param b the translated vector
 */
void Translate3D(Vec3* a, const Vec3* b)
{
	if (a == NULL || b == NULL)
	{ ErrorHandler(ACCESSING_NULL_POINTER_ERROR); }
	a->x += b->x;
	a->y += b->y;
	a->z += b->z;
}

/**
 * Rotates vector a by a given angle. In-place modification is made to the rotated vector.
 * Note: vector a is treated as a 2D vector, assuming the z component is zero.
 * The rotation is only applied to the x and y component of vector a using the rotation matrix:
 * [[cos(theta), - sin(theta)],
 *  [sin(theta),   cos(theta)]]
 *
 * @param a the vector to be rotated
 * @param angle the angle of rotation, in radians
 */
void Rotate3D(Vec3* a, float angle)
{
	if (a == NULL)
	{ ErrorHandler(ACCESSING_NULL_POINTER_ERROR); }
	float temp = a->x;
	a->x = cosf(angle) * temp - sinf(angle) * a->y;
	a->y = sinf(angle) * temp + cosf(angle) * a->y;
}

/**
 * Scales a vector. In-place modification is made to the scaled vector.
 *
 * @param a the scaled vector
 * @param scalar the scalar
 */
void Scale3D(Vec3* a, float scalar)
{
	if (a == NULL)
	{ ErrorHandler(ACCESSING_NULL_POINTER_ERROR); }
	a->x *= scalar;
	a->y *= scalar;
	a->z *= scalar;
}

/**
 * Inverts the direction of the vector. In-place modification is made to the inverted vector.
 *
 * @param a the vector to be inverted
 */
void Invert3D(Vec3* a)
{
	if (a == NULL)
	{ ErrorHandler(ACCESSING_NULL_POINTER_ERROR); }
	a->x = -a->x;
	a->y = -a->y;
	a->z = -a->z;
}

/**
 * Normalizes a vector. In-place modification is made to the normalized vector.
 *
 * @param a the vector to be normalized
 */
void Normalize3D(Vec3* a)
{
	if (a == NULL)
	{ ErrorHandler(ACCESSING_NULL_POINTER_ERROR); }
	float vecLength = sqrtf((a->x) * (a->x) + (a->y) * (a->y) + (a->z) * (a->z));
	if (!(CompareFloats(vecLength, ZERO) == 0))
	{
		a->x = (a->x) / vecLength;
		a->y = (a->y) / vecLength;
		a->z = (a->z) / vecLength;
	}
}

/**
 * Calculates the euclidean distance between two vectors.
 *
 * @param a the first vector
 * @param b the second vector
 * @return the euclidean distance between vector a and vector b
 */
float EuclideanDistance3D(const Vec3* a, const Vec3* b)
{
	if (a == NULL || b == NULL)
	{ ErrorHandler(ACCESSING_NULL_POINTER_ERROR); }
	float dx = a->x - b->x;
	float dy = a->y - b->y;
	float dz = a->z - b->z;
	return sqrtf(dx * dx + dy * dy + dz * dz);
}