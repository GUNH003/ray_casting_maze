#ifndef RAY_CASTING_MAZE_MAZE_H_
#define RAY_CASTING_MAZE_MAZE_H_

#define VISITED 0 	// used to mark a cell as visited
#define UNVISITED 1 // used to mark a cell as unvisited

#include "../Stack/Stack.h"

/**
 * Traverses the maze array and generates maze. In-place modification is made to the maze array.
 *
 * @param maze 	   the maze array
 * @param mazeSize the size of the maze array
 */
 void GenerateMaze(int maze[], int mazeSize);

/**
 * Creates maze map array.
 *
 * @param mazeSize size of the maze map array
 * @return the maze map array
 */
 int* CreateMazeMap(int mazeSize);
#endif
