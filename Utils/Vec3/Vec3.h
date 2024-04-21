#ifndef RAY_CASTING_MAZE_VEC3_H_
#define RAY_CASTING_MAZE_VEC3_H_

/**
 * Struct for vector in R3.
 */
typedef struct Vec3_struct
{
	float x;
	float y;
	float z;
} Vec3;

/**
 * Creates a vector.
 *
 * @param x the x component of the vector
 * @param y the y component of the vector
 * @param z the z component of the vector
 * @return a Vec3 object
 */
Vec3* Vec3D(float x, float y, float z);

/**
 * Calculates the dot product of two vectors. The dot product is used to calculate the projection of a on b.
 *
 * @param a vector a
 * @param b vector b
 * @return the result of the dot product
 */
float Dot3D(const Vec3* a, const Vec3* b);

/**
 * Translates vector a by vector b. In-place modification is made to the translated vector.
 *
 * @param a the vector to be translated
 * @param b the translated vector
 */
void Translate3D(Vec3* a, const Vec3* b);

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
void Rotate3D(Vec3* a, float angle);

/**
 * Scales a vector. In-place modification is made to the scaled vector.
 *
 * @param a the scaled vector
 * @param scalar the scalar
 */
void Scale3D(Vec3* a, float scalar);

/**
 * Inverts the direction of the vector. In-place modification is made to the inverted vector.
 *
 * @param a the vector to be inverted
 */
void Invert3D(Vec3* a);

/**
 * Normalizes a vector. In-place modification is made to the normalized vector.
 *
 * @param a the vector to be normalized
 */
void Normalize3D(Vec3* a);

/**
 * Calculates the euclidean distance between two vectors.
 *
 * @param a the first vector
 * @param b the second vector
 * @return the euclidean distance between vector a and vector b
 */
float EuclideanDistance3D(const Vec3* a, const Vec3* b);

#endif
