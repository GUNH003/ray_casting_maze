#include <math.h>
#include "Comparator.h"

/**
 * Compares two floats for equality.
 *
 * @param a the first float
 * @param b the second float
 * @return 0 if the absolute value between the two floats are smaller than DELTA, -1 if the first float is smaller than
 * the second float, 1 if the first float is greater than the second float
 */
int CompareFloats(float a, float b)
{
	if (fabsf(a - b) < DELTA)
	{return 0;}
	else if (a < b)
	{return -1;}
	else
	{return 1;}
}