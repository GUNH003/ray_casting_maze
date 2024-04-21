#ifndef RAY_CASTING_MAZE_CASTER_H_
#define RAY_CASTING_MAZE_CASTER_H_

#define COORDINATE_OFFSET 0.01f   // used to correct hit detection result
#define MAX_DDA_ITERATION 10      // used to prevent infinite loop for the DDA algorithm
#define HORIZONTAL_WALL (-1.0f)   // representing a horizontal wall, passed as the z component in 3D vector
#define VERTICAL_WALL 1.0f        // representing a vertical wall, passed as the z component in 3D vector
#define RAY_HEIGHT_COEFFICIENT 16 // changing the rectangle height for rendering

#include "../Vec3/Vec3.h"
#include "../../Map/Map.h"

/**
 * Calculates the final intersection between the ray cast by the player and a cell that represents a wall. If first
 * calculates the first horizontal and first vertical intersections, then calculates the euclidean distance between the
 * player position and the two intersection points respectively, the intersection that produces the shorter distance is
 * returned. 3D vectors are used for the calculation, assuming that the z component is 0.0f.
 *
 * @param playerPosition 	the vector representing the player position
 * @param rayCastedByPlayer the vector representing the ray casted by the player
 * @param mapCellSize 		the size of each cell in the map grid
 * @param map 				1D array representing the map, each element in the array represents a cell in the map grid
 * @param mapSize 			the side length of the square map grid (mapSize * mapSize == map.size())
 * @return the final vector representing the intersection between the ray cast by player and a map cell
 * that represents a wall
 */
Vec3*
CalculateFinalIntersection(const Vec3* playerPosition, const Vec3* playerDirection, float mapCellSize, const int map[],
		int mapSize);

/**
 * Calculates all the intersections between the rays cast by the player and the cells that represent walls.
 * 3D vectors are used for the calculation, assuming that the z component is 0.0f.
 *
 * @param playerPosition    the vector representing the player position
 * @param rayCastedByPlayer the vector representing the ray casted by the player
 * @param mapCellSize       the size of each cell in the map grid
 * @param map        		1D array representing the map, each element in the array represents a cell in the map grid
 * @param mapSize 			the side length of the square map grid (mapSize * mapSize == map.size())
 * @param fieldOfView 		the angle in radians
 * @param numOfRays 		the number of rays casted by the player within the field of view
 * @return an array of vector that represents all the intersections between the rays cast by player and the cells
 * that represent walls
 */
Vec3*
CalculateIntersections(const Vec3* playerPosition, const Vec3* playerDirection, float mapCellSize, const int map[],
		int mapSize, float fieldOfView, int numOfRays);

/**
* Calculates the all the heights used for first-person view rendering based on the length of each ray vector.
 *
 * @param allIntersections the vectors representing all the intersection points
 * @param playerPosition   the vector representing the player position
 * @param playerDirection  the vector representing the direction that the player is facing, this vector is a unit vector
 * @param numOfRays 	   the number of rays casted by the player within the field of view
 * @param windowHeight     the height of the SDL window
 * @return an array of float that represents the height used to render the rectangles in the SDL renderer
 */
float* CalculateHeights(const Vec3* allIntersections, const Vec3* playerPosition, const Vec3* playerDirection,
		int numOfRays, float windowHeight);

/**
  * Gets the index of the cell whose wall is pointed by the player's crosshair.
 *
 * @param playerDirectionIntersection the point of intersection between the cell wall and the ray casted by player
 * 									  along the player direction vector
 * @param playerDirection 			  the vector representing the direction that the player is facing, this vector is
 * 									  a unit vector
 * @param mapCellSize 				  the size of each cell in the map grid
 * @param mapSize 					  the side length of the square map grid (mapSize * mapSize == map.size())
 * @return the index of the cell whose wall is pointed by the player's crosshair
 */
int GetPointedNonWallCellIndex(const Vec3* playerDirectionIntersection, const Vec3* playerDirection,
		float mapCellSize, int mapSize);

#endif
