#include <stdlib.h>
#include <math.h>
#include "RayCaster.h"
#include "../ErrorHandler/ErrorHandler.h"
#include "../Comparator/Comparator.h"

/**
 * Calculates the first horizontal intersection between the ray cast by player and the wall of the cell in which
 * the player is located. 3D vectors are used for the calculation, assuming that the z component is 0.0f.
 *
 * @param playerPosition	the vector representing the player position
 * @param rayCastedByPlayer the ray cast by player
 * @param mapCellSize 		the size of each cell in the map grid
 * @return the vector representing the first horizontal intersection between the ray cast by player and a map cell
 */
Vec3* CalculateFirstHorizontalIntersection(const Vec3* playerPosition, const Vec3* rayCastedByPlayer, float mapCellSize)
{
	if (playerPosition == NULL || rayCastedByPlayer == NULL)
	{ErrorHandler(ACCESSING_NULL_POINTER_ERROR);}
	Vec3* firstHorizontalIntersection = Vec3D(playerPosition->x, playerPosition->y, ZERO);
	if (!(CompareFloats(rayCastedByPlayer->x, ZERO) == 0))
	{
		float slope = rayCastedByPlayer->y / rayCastedByPlayer->x;
		float dx;
		float dy = ZERO;
		if (rayCastedByPlayer->y < 0)  // facing up
		{
			// Subtracts COORDINATE_OFFSET to correct hit detection result when facing up
			dy = floorf(playerPosition->y / mapCellSize) * mapCellSize - playerPosition->y - COORDINATE_OFFSET;
		}
		else if (rayCastedByPlayer->y > 0)  // facing down
		{
			dy = ceilf(playerPosition->y / mapCellSize) * mapCellSize - playerPosition->y;
		}
		dx = dy / slope;
		// Initialize translationVector with z component equal to 0.0f
		Vec3* translationVector = Vec3D(dx, dy, ZERO);
		Translate3D(firstHorizontalIntersection, translationVector);
		free(translationVector);
	}
	return firstHorizontalIntersection;
}

/**
 * Calculates the first vertical intersection between the ray cast by player and the wall of the cell in which
 * the player is located. 3D vectors are used for the calculation, assuming that the z component is 0.0f.
 *
 * @param playerPosition 	the vector representing the player position
 * @param rayCastedByPlayer the ray cast by player
 * @param mapCellSize 		the size of each cell in the map grid
 * @return the vector representing the first vertical intersection between the ray cast by player and a map cell
 */
Vec3* CalculateFirstVerticalIntersection(const Vec3* playerPosition, const Vec3* rayCastedByPlayer, float mapCellSize)
{
	if (playerPosition == NULL || rayCastedByPlayer == NULL)
	{ErrorHandler(ACCESSING_NULL_POINTER_ERROR);}
	Vec3* firstVerticalIntersection = Vec3D(playerPosition->x, playerPosition->y, ZERO);
	if (!(CompareFloats(rayCastedByPlayer->x, ZERO) == 0))
	{
		float slope = rayCastedByPlayer->y / rayCastedByPlayer->x;
		float dx = 0.0f;
		float dy;
		if (rayCastedByPlayer->x < 0)  // facing left
		{
			// Subtracts COORDINATE_OFFSET to correct hit detection result when facing left
			dx = floorf(playerPosition->x / mapCellSize) * mapCellSize - playerPosition->x - COORDINATE_OFFSET;
		}
		else if (rayCastedByPlayer->x > 0)  // facing right
		{
			dx = ceilf(playerPosition->x / mapCellSize) * mapCellSize - playerPosition->x;
		}
		dy = dx * slope;
		// Initialize translationVector with z component equal to 0.0f
		Vec3* translationVector = Vec3D(dx, dy, ZERO);
		Translate3D(firstVerticalIntersection, translationVector);
		free(translationVector);
	}
	return firstVerticalIntersection;
}

/**
 * Checks if the ray cast by player intersects with a cell that is a wall (represented using 1 in the map array).
 * 3D vectors are used for the calculation, assuming that the z component is 0.0f.
 *
 * @param intersection the current intersection between the ray cast by player and a cell
 * @param mapCellSize  the size of each cell in the map grid
 * @param map 		   1D array representing the map, each element in the array represents a cell in the map grid
 * @param mapSize 	   the side length of the square map grid (mapSize * mapSize == map.size())
 * @return 1 if the ray cast player intersects will a wall, 0 otherwise
 */
int HasHit(const Vec3* intersection, float mapCellSize, const int map[], int mapSize)
{
	if (intersection == NULL || map == NULL)
	{ErrorHandler(ACCESSING_NULL_POINTER_ERROR);}
	int xIndex = (int)((intersection->x) / mapCellSize);
	int yIndex = (int)((intersection->y) / mapCellSize);

	if (xIndex >= 0 && xIndex < mapSize && yIndex >= 0 && yIndex < mapSize)
	{
		if (map[yIndex * mapSize + xIndex] == WALL)
		{return 1;}
	}
	return 0;
}

/**
 * Calculates the first horizontal intersection between the ray cast by player and a cell that represents a wall.
 * 3D vectors are used for the calculation, assuming that the z component is 0.0f.
 *
 * @param playerPosition 	the vector representing the player position
 * @param rayCastedByPlayer the vector representing the ray cast by player
 * @param mapCellSize 		the size of each cell in the map grid
 * @param map 				1D array representing the map, each element in the array represents a cell in the map grid
 * @param mapSize 			the side length of the square map grid (mapSize * mapSize == map.size())
 * @return the vector representing the first horizontal intersection between the ray cast player and a map cell
 * that represents a wall
 */
Vec3* CalculateFinalHorizontalIntersection(const Vec3* playerPosition, const Vec3* rayCastedByPlayer, float mapCellSize,
		const int map[], int mapSize)
{
	if (playerPosition == NULL || rayCastedByPlayer == NULL || rayCastedByPlayer == NULL)
	{ErrorHandler(ACCESSING_NULL_POINTER_ERROR);}
	Vec3* runningHorizontalIntersection = CalculateFirstHorizontalIntersection(playerPosition, rayCastedByPlayer,
			mapCellSize);
	int i = 0;
	// If current intersection is not in a cell that represents a wall, continue translating the intersection vector
	while (!HasHit(runningHorizontalIntersection, mapCellSize, map, mapSize) &&
			i < MAX_DDA_ITERATION) // Prevents infinite loop
	{
		float slope = rayCastedByPlayer->y / rayCastedByPlayer->x;
		Vec3* translationVector = NULL;
		if (rayCastedByPlayer->y < 0)
		{
			translationVector = Vec3D(-mapCellSize / slope, -mapCellSize, ZERO);
		}
		else if (rayCastedByPlayer->y > 0)
		{
			translationVector = Vec3D(mapCellSize / slope, mapCellSize, ZERO);
		}
		else
		{
			break;
		}
		if (translationVector != NULL)
		{
			Translate3D(runningHorizontalIntersection, translationVector);
			free(translationVector);
		}
		++i;
	}
	return runningHorizontalIntersection;
}

/**
 * Calculates the first vertical intersection between the ray cast by player and a cell that represents a wall.
 * 3D vectors are used for the calculation, assuming that the z component is 0.0f.
 *
 * @param playerPosition 	the vector representing the player position
 * @param rayCastedByPlayer the vector representing the ray cast by player
 * @param mapCellSize 		the size of each cell in the map grid
 * @param map 				1D array representing the map, each element in the array represents a cell in the map grid
 * @param mapSize 			the side length of the square map grid (mapSize * mapSize == map.size())
 * @return the vector representing the first vertical intersection between the ray cast by player and a map cell
 * that represents a wall
 */
Vec3* CalculateFinalVerticalIntersection(const Vec3* playerPosition, const Vec3* rayCastedByPlayer, float mapCellSize,
		const int map[], int mapSize)
{
	if (playerPosition == NULL || rayCastedByPlayer == NULL || map == NULL)
	{ErrorHandler(ACCESSING_NULL_POINTER_ERROR);}
	Vec3* runningVerticalIntersection = CalculateFirstVerticalIntersection(playerPosition, rayCastedByPlayer,
			mapCellSize);
	int i = 0;
	// If current intersection is not in a cell that represents a wall, continue translating the intersection vector
	while (!HasHit(runningVerticalIntersection, mapCellSize, map, mapSize) &&
			i < MAX_DDA_ITERATION) // Prevents infinite loop
	{
		float slope = rayCastedByPlayer->y / rayCastedByPlayer->x;
		Vec3* translationVector = NULL;
		if (rayCastedByPlayer->x < 0)
		{
			translationVector = Vec3D(-mapCellSize, -mapCellSize * slope, ZERO);
		}
		else if (rayCastedByPlayer->x > 0)
		{
			translationVector = Vec3D(mapCellSize, mapCellSize * slope, ZERO);
		}
		else
		{
			break;
		}
		if (translationVector != NULL)
		{
			Translate3D(runningVerticalIntersection, translationVector);
			free(translationVector);
		}
		++i;
	}
	return runningVerticalIntersection;
}

/**
 * Calculates the final intersection between the ray cast by player and a cell that represents a wall. If first
 * calculates the first horizontal and first vertical intersections, then calculates the euclidean distance between the
 * player position and the two intersection points respectively, the intersection that produces the shorter distance is
 * returned. 3D vectors are used for the calculation, assuming that the z component is 0.0f.
 *
 * @param playerPosition 	the vector representing the player position
 * @param rayCastedByPlayer the vector representing the ray cast by player
 * @param mapCellSize 		the size of each cell in the map grid
 * @param map 				1D array representing the map, each element in the array represents a cell in the map grid
 * @param mapSize 			the side length of the square map grid (mapSize * mapSize == map.size())
 * @return the final vector representing the intersection between the ray cast by player and a map cell
 * that represents a wall
 */
Vec3* CalculateFinalIntersection(const Vec3* playerPosition, const Vec3* rayCastedByPlayer, float mapCellSize,
		const int map[], int mapSize)
{
	if (playerPosition == NULL || rayCastedByPlayer == NULL || map == NULL)
	{ErrorHandler(ACCESSING_NULL_POINTER_ERROR);}
	Vec3* horizontalIntersection = CalculateFinalHorizontalIntersection(
			playerPosition, rayCastedByPlayer, mapCellSize, map, mapSize);
	Vec3* verticalIntersection = CalculateFinalVerticalIntersection(
			playerPosition, rayCastedByPlayer, mapCellSize, map, mapSize);
	if (EuclideanDistance3D(playerPosition, horizontalIntersection) < EuclideanDistance3D(playerPosition,
			verticalIntersection))
	{
		free(verticalIntersection);
		horizontalIntersection->z = HORIZONTAL_WALL;
		return horizontalIntersection;
	}
	else
	{
		free(horizontalIntersection);
		verticalIntersection->z = VERTICAL_WALL;
		return verticalIntersection;
	}
}

/**
 * Calculates all the intersections between the rays cast by player and the cells that represent walls.
 * 3D vectors are used for the calculation, assuming that the z component is 0.0f.
 *
 * @param playerPosition 	the vector representing the player position
 * @param rayCastedByPlayer the vector representing the ray cast by player
 * @param mapCellSize 		the size of each cell in the map grid
 * @param map 				1D array representing the map, each element in the array represents a cell in the map grid
 * @param mapSize 			the side length of the square map grid (mapSize * mapSize == map.size())
 * @param fieldOfView 		the angle in radians
 * @param numOfRays 		the number of rays cast by player within the field of view
 * @return an array of vector that represents all the intersections between the rays cast by player and the cells
 * that represent walls
 */
Vec3* CalculateIntersections(const Vec3* playerPosition, const Vec3* playerDirection, float mapCellSize,
		const int map[], int mapSize, float fieldOfView, int numOfRays)
{
	if (playerPosition == NULL || playerDirection == NULL || map == NULL)
	{ErrorHandler(ACCESSING_NULL_POINTER_ERROR);}
	// Calculate the angle step size based on the field of view and the number of rays
	float angleIncrement = fieldOfView / (float)numOfRays;

	Vec3 runningRayDirection = *playerDirection;
	Rotate3D(&runningRayDirection, -fieldOfView / 2);
	// Allocate Vec3 array to store all intersections
	Vec3* allIntersections = (Vec3*)calloc((int)numOfRays, sizeof(Vec3));
	if (allIntersections == NULL)
	{ErrorHandler(MEMORY_ALLOCATION_ERROR);}
	// Cast a ray for each angle in the field of view
	for (int i = 0; i < numOfRays; ++i)
	{
		Rotate3D(&runningRayDirection, angleIncrement);
		// Calculate the intersection of the ray with the map
		Vec3* currentIntersection = CalculateFinalIntersection(
				playerPosition, &runningRayDirection, mapCellSize, map, mapSize);
		allIntersections[i] = *currentIntersection;
		free(currentIntersection);
	}
	return allIntersections;
}

/**
 * Calculates the height used for first-person view rendering based on the length of the ray vector. The player
 * direction vector is always a unit vector, the angle between the player direction vector and the ray vector is denoted
 * as "theta", then the perpendicular distance between the ray-wall intersection point and its projection point on the
 * camera plane (line in 2D) is equal to the dot product between the player direction vector and the ray vector.
 *
 * If playerDirection is a unit vector, then:
 * playerDirection * ray = ||playerDirection|| * ||ray|| * cos(theta) = ||ray|| * cos(theta)
 *
 * @param rayVector 	  the vector representing the ray cast by player
 * @param playerDirection the vector representing the direction that the player is facing, this vector is a unit vector
 * @param windowHeight 	  the height of the SDL window
 * @return the height converted from the ray vector length
 */
float ConvertRayLengthToHeight(const Vec3* rayVector, const Vec3* playerDirection, float windowHeight)
{
	if (rayVector == NULL || playerDirection == NULL)
	{ErrorHandler(ACCESSING_NULL_POINTER_ERROR);}
	// Calculates the length of the line segment orthogonal to the camera plane.
	// Reference: https://lodev.org/cgtutor/raycasting.html
	float height = RAY_HEIGHT_COEFFICIENT * windowHeight / Dot3D(rayVector, playerDirection);
	// Height can not exceed window height
	height = height > windowHeight ? windowHeight : height;
	return height;
}

/**
 * Calculates all the heights used for first-person view rendering based on the length of each ray vector.
 *
 * @param allIntersections the vectors representing all the intersection points
 * @param playerPosition   the vector representing the player position
 * @param playerDirection  the vector representing the direction that the player is facing, this vector is a unit vector
 * @param numOfRays 	   the number of rays casted by the player within the field of view
 * @param windowHeight     the height of the SDL window
 * @return an array of float that represents the height used to render the rectangles in the SDL renderer
 */
float* CalculateHeights(const Vec3* allIntersections, const Vec3* playerPosition, const Vec3* playerDirection,
		int numOfRays, float windowHeight)
{
	if (allIntersections == NULL || playerPosition == NULL || playerDirection == NULL)
	{ErrorHandler(ACCESSING_NULL_POINTER_ERROR);}
	float* heights = (float*)calloc(numOfRays, sizeof(float));
	if (heights == NULL)
	{ErrorHandler(MEMORY_ALLOCATION_ERROR);}
	// Retrieves player's position in order to calculate ray vector
	Vec3 playerPosForCalculation = *playerPosition;
	Invert3D(&playerPosForCalculation);

	for (int i = 0; i < numOfRays; ++i)
	{
		// Initialize each ray vector
		Vec3* rayVector = Vec3D(allIntersections[i].x, allIntersections[i].y, ZERO);
		Translate3D(rayVector, &playerPosForCalculation);
		// Calculate height based on ray vector length
		heights[i] = ConvertRayLengthToHeight(rayVector, playerDirection, windowHeight);
		free(rayVector);
	}
	return heights;
}

/**
 * Gets the index of the cell whose wall is pointed by the player's crosshair.
 *
 * @param playerDirectionIntersection the point of intersection between the cell wall and the ray casted by player
 * 									  along the player direction vector
 * @param playerDirection 			  the vector representing the direction that the player is facing, this vector
 * 									  is a unit vector
 * @param mapCellSize 				  the size of each cell in the map grid
 * @param mapSize 				      the side length of the square map grid (mapSize * mapSize == map.size())
 * @return the index of the cell whose wall is pointed by the player's crosshair
 */
int GetPointedNonWallCellIndex(const Vec3* playerDirectionIntersection, const Vec3* playerDirection,
		float mapCellSize, int mapSize)
{
	if (playerDirectionIntersection == NULL || playerDirection == NULL)
	{ErrorHandler(ACCESSING_NULL_POINTER_ERROR);}
	if (CompareFloats(playerDirectionIntersection->z, VERTICAL_WALL) == 0) // Vertical intersection
	{
		if (playerDirection->x < 0) // left intersection
		{
			return (int)(playerDirectionIntersection->y / mapCellSize) * mapSize
					+ (int)(playerDirectionIntersection->x / mapCellSize) + 1;
		}
		if (playerDirection->x > 0) // right intersection
		{
			return (int)(playerDirectionIntersection->y / mapCellSize) * mapSize
					+ (int)(playerDirectionIntersection->x / mapCellSize) - 1;
		}
	}
	if (CompareFloats(playerDirectionIntersection->z, HORIZONTAL_WALL) == 0)  // Horizontal intersection
	{
		if (playerDirection->y < 0) // upward intersection
		{
			return (int)(playerDirectionIntersection->y / mapCellSize) * mapSize
					+ (int)(playerDirectionIntersection->x / mapCellSize) + mapSize;
		}
		if (playerDirection->y > 0) // downward intersection
		{
			return (int)(playerDirectionIntersection->y / mapCellSize) * mapSize
					+ (int)(playerDirectionIntersection->x / mapCellSize) - mapSize;
		}
	}

}