#ifndef RAY_CASTING_MAZE_MAP_H_
#define RAY_CASTING_MAZE_MAP_H_

#define WALL 1

#include <SDL.h>
#include "../Utils/MazeGenerator/MazeGenerator.h"

// ------------------------------------------- GLOBALS -------------------------------------------
extern int M_SIZE; 				// map width
extern float M_CELL_SIZE; 		// cell size in map grid
extern int* MAP; 				// 1D array representing the world, where 1 represents a wall and 0 represents empty
								// space
extern int* MAP_STATUS; 		// 1D array representing the cell status in the map, all cells are initialized as
								// unvisited, the status of each cell is changed in runtime
extern SDL_FRect *M_WALL_RECTS; // array of walls drawn in map, walls are represented and drawn using SDL rectangles
extern int M_WALL_RECTS_LENGTH; // length of the array of wall rectangles drawn in map, initialized to 0

// ------------------------------------------- FUNCTIONS -------------------------------------------
/**
 * Initializes map array and the map status array. Initializes the square map side length, the cell size in map grid,
 * the map array and the map status array.
 *
 * @param mapStatus   the global variable representing the map status array
 * @param map 		  the global variable representing the map array
 * @param mapSize     the global variable representing the square map's side length
 * @param size 		  the value assigned to the map's side length
 * @param mapCellSize the global variable representing the size of the cell in the map grid
 * @param cellSize    the value assigned to the cell's size
 */
void InitializeMap(int** mapStatus, int** map, int* mapSize, int size, float* mapCellSize, float cellSize);

/**
 * Creates the array of rectangles representing walls in map. Assign number of rectangles drawn to the global variable
 * rectArrayLength as side effect.
 *
 * @param rectArrayLength the global variable storing the length of the array of rectangle
 * @param cellSize 		  the value assigned to the cell's size
 * @param map 			  the global variable representing the map array
 * @param mapSize 		  the global variable representing the square map's side length
 * @return the array of SDL rectangle objects representing walls in the map
 */
SDL_FRect* CreateMapWallRects(int* rectArrayLength, float cellSize, const int map[], int mapSize);

#endif
