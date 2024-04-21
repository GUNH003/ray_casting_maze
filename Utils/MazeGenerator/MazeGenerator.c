#include <stdlib.h>
#include "MazeGenerator.h"
#include "../ErrorHandler/ErrorHandler.h"

// -------------------------------------- STATIC GLOBAL VARIABLES --------------------------------------
static const int TOTAL_NUM_NEIGHBORS = 4;        // total number of neighbors
static const int INVALID_NEIGHBOR_INDEX = -1;    // invalid neighbor index

// -------------------------------------- FUNCTIONS --------------------------------------
/**
 * Checks if the current cell has valid neighbors.
 *
 * @param neighborIndex the neighbor index array
 * @return 1 if the current cell has at least one valid neighbor, 0 if the current cell has no valid neighbors
 */
int hasValidNeighbors(const int neighborIndex[])
{
	int numInvalidNeighbors = 0;
	for (int i = 0; i < TOTAL_NUM_NEIGHBORS; ++i)
	{
		if (neighborIndex[i] == INVALID_NEIGHBOR_INDEX)
		{++numInvalidNeighbors;}
	}
	return numInvalidNeighbors != TOTAL_NUM_NEIGHBORS;
}

/**
 * Populates neighbor array and chooses a random neighbor from the neighbor index array and return the chosen
 * neighbor's index. It assumes that each element in array neighbors is initialized to INVALID_NEIGHBOR_INDEX.
 * A neighbor of the current cell(C) is defined as the cell(X) that is two cells away form the current cell, as
 * shown below:
 *        X
 *        #
 *    X # C # X
 *        #
 *        X
 *
 * @param currentIndex  the index of the current cell
 * @param neighborIndex the neighbor index array
 * @param maze 			the maze array
 * @param mazeSize 		the size of the maze array
 * @return the index of the chosen neighbor, -1 if no valid neighbor exists
 */
int GetRandomNeighborIndex(int currentIndex, int neighborIndex[], const int maze[], int mazeSize)
{
	if (neighborIndex == NULL || maze == NULL)
	{ErrorHandler(ACCESSING_NULL_POINTER_ERROR);}
	if (currentIndex - 2 * mazeSize >= 0 && maze[currentIndex - 2 * mazeSize] == UNVISITED)   // up
	{
		neighborIndex[0] = currentIndex - 2 * mazeSize;
	}
	if (currentIndex + 2 * mazeSize < mazeSize * mazeSize && maze[currentIndex + 2 * mazeSize] == UNVISITED)  // down
	{
		neighborIndex[1] = currentIndex + 2 * mazeSize;
	}
	if (currentIndex % mazeSize >= 2 && maze[currentIndex - 2] == UNVISITED)  // left
	{
		neighborIndex[2] = currentIndex - 2;
	}
	if (currentIndex % mazeSize < mazeSize - 2 && maze[currentIndex + 2] == UNVISITED)   // right
	{
		neighborIndex[3] = currentIndex + 2;
	}
	uint32_t randomIndex = INVALID_NEIGHBOR_INDEX;
	// If no valid neighbor exits, return -1
	if (!hasValidNeighbors(neighborIndex))
	{return (int)randomIndex;}
	// If valid neighbor exists, picks one valid neighbor
	while (1)
	{
		randomIndex = arc4random_uniform(TOTAL_NUM_NEIGHBORS);
		if (!(neighborIndex[randomIndex] != -1 && maze[neighborIndex[randomIndex]] != VISITED))
		{continue;}
		else
		{break;}
	}
	return (int)randomIndex;
}

/**
 * Traverses the maze array and generates maze. In-place modification is made to the maze array.
 *
 * @param maze 	   the maze array
 * @param mazeSize the size of the maze array
 */
void GenerateMaze(int maze[], int mazeSize)
{
	if (maze == NULL)
	{ErrorHandler(ACCESSING_NULL_POINTER_ERROR);}
	// Always starts depth-first traversal from the top-left corner of the map
	int startIndex = mazeSize + 1;
	Stack* stack = CreateStack();
	Push(stack, startIndex);
	while (!IsEmpty(stack))
	{
		int currentIndex = Top(stack);
		maze[currentIndex] = VISITED;
		// Get valid neighbor index
		int neighborIndex[TOTAL_NUM_NEIGHBORS];
		for (int i = 0; i < TOTAL_NUM_NEIGHBORS; ++i)
		{neighborIndex[i] = -1;}
		int nextMove = GetRandomNeighborIndex(currentIndex, neighborIndex, maze, mazeSize);
		// If no valid neighbor was found, backtrack
		if (nextMove == -1)
		{Pop(stack);}
			// If a valid neighbor was found, connect the current cell with the chosen cell, and pushes the chosen
			// cell into stack
		else
		{
			int nextIndex = neighborIndex[nextMove];
			// Connect with nextMove index in maze
			if (nextMove == 0)
			{maze[nextIndex + mazeSize] = VISITED;}
			else if (nextMove == 1)
			{maze[nextIndex - mazeSize] = VISITED;}
			else if (nextMove == 2)
			{maze[nextIndex + 1] = VISITED;}
			else
			{maze[nextIndex - 1] = VISITED;}
			// Pushes valid neighbors to the stack
			Push(stack, nextIndex);
		}
	}
	DestroyStack(stack);
}

/**
 * Creates maze map array.
 *
 * @param mazeSize size of the maze map array
 * @return the maze map array
 */
int* CreateMazeMap(int mazeSize)
{
	int* maze = (int*)calloc(mazeSize * mazeSize, sizeof(int));
	if (maze == NULL)
	{ErrorHandler(MEMORY_ALLOCATION_ERROR);}
	for (int i = 0; i < mazeSize * mazeSize; ++i)
	{maze[i] = UNVISITED;}
	GenerateMaze(maze, mazeSize);
	return maze;
}