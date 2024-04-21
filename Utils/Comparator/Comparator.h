#ifndef RAY_CASTING_MAZE_COMPARATOR_H_
#define RAY_CASTING_MAZE_COMPARATOR_H_

#define ZERO 0.0f 	// used as 0 for float
#define DELTA 1e-6f // precision for floating point number comparison

/**
 * Compares two floats for equality.
 *
 * @param a the first float
 * @param b the second float
 * @return 0 if the absolute value between the two floats are smaller than DELTA, -1 if the first float is smaller than
 * the second float, 1 if the first float is greater than the second float
 */
int CompareFloats(float a, float b);

#endif
