#include "Map.h"
#include "../Utils/ErrorHandler/ErrorHandler.h"

// -------------------------------------- GLOBALS -----------------------------------------
int M_SIZE;                     // map width
float M_CELL_SIZE;              // cell size in map grid
int* MAP = NULL;                // 1D array representing the world, where 1 represents a wall and 0 represents empty
								// space
int* MAP_STATUS = NULL;         // 1D array representing the cell status in the map, all cells are initialized as
								// unvisited, the status of each cell is changed in runtime
SDL_FRect* M_WALL_RECTS = NULL; // array of walls drawn in map, walls are represented and drawn using SDL rectangles
int M_WALL_RECTS_LENGTH = 0;    // length of the array of wall rectangles drawn in map, initialized to 0


// -------------------------------------- FUNCTIONS -----------------------------------------
/**
 * Initializes the array of map status. Map status array is identical to map array when initialized. The status of each
 * cell in map status array will be modified in runtime. An unvisited cell's status will be changed to visited when the
 * player moves inside of the cell. In-place modification is made to mapStatus.
 *
 * @param mapStatus the map status array
 * @param map 		the map array
 * @param mapSize 	the map size
 */
void InitializeMapStatus(int** mapStatus, const int map[], int mapSize)
{
	if (*mapStatus != NULL)
	{free(mapStatus);}
	*mapStatus = (int*)calloc(mapSize * mapSize, sizeof(int));
	if (*mapStatus == NULL)
	{ErrorHandler(MEMORY_ALLOCATION_ERROR);}
	for (int i = 0; i < mapSize; ++i)
	{
		for (int j = 0; j < mapSize; ++j)
		{
			int index = i * mapSize + j;
			(*mapStatus)[index] = map[index]; // need parentheses, otherwise access then dereference, causing bad access
		}
	}
}

/**
 * Initializes map array and the map status array. Initializes the square map side length, the cell size in map grid,
 * the map array and the map status array. In-place modification is made to mapStatus, map, mapSize and mapCellSize.
 *
 * @param mapStatus   the global variable representing the map status array
 * @param map 		  the global variable representing the map array
 * @param mapSize 	  the global variable representing the square map's side length
 * @param size 		  the value assigned to the map's side length
 * @param mapCellSize the global variable representing the size of the cell in the map grid
 * @param cellSize    the value assigned to the cell's size
 */
void InitializeMap(int** mapStatus, int** map, int* mapSize, int size, float* mapCellSize, float cellSize)
{
	if (*mapStatus != NULL)
	{free(*mapStatus);}
	if (*map != NULL)
	{free(*map);}
	*mapSize = size;
	*mapCellSize = cellSize;
	*map = CreateMazeMap(*mapSize);
	InitializeMapStatus(mapStatus, *map, size);
}


/**
 * Creates the array of rectangles representing walls in map. Assign number of rectangles drawn to the global variable
 * rectArrayLength as side effect. In-place modification is made to rectArrayLength and map array.
 *
 * @param rectArrayLength the global variable storing the length of the array of rectangle
 * @param cellSize 		  the value assigned to the cell's size
 * @param map    		  the global variable representing the map array
 * @param mapSize		  the global variable representing the square map's side length
 * @return the array of SDL rectangle objects representing walls in the map
 */
SDL_FRect* CreateMapWallRects(int* rectArrayLength, float cellSize, const int map[], int mapSize)
{
	SDL_FRect* mapWallRectArray = (SDL_FRect*)calloc(mapSize * mapSize, sizeof(SDL_FRect));
	if (mapWallRectArray == NULL)
	{ErrorHandler(MEMORY_ALLOCATION_ERROR);}
	int mapRectsIndex = 0;
	for (int y = 0; y < mapSize; ++y)
	{
		for (int x = 0; x < mapSize; ++x)
		{
			SDL_FRect rect;
			rect.x = (float)x * cellSize;
			rect.y = (float)y * cellSize;
			rect.w = cellSize;
			rect.h = cellSize;
			int index = y * mapSize + x;
			if (map[index] == WALL)
			{
				mapWallRectArray[mapRectsIndex++] = rect;
			}
		}
	}
	*rectArrayLength = mapRectsIndex;
	return mapWallRectArray;
}