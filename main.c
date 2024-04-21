#include <SDL.h>
#include "Map/Map.h"
#include "Player/Player.h"
#include "Utils/RayCaster/RayCaster.h"

// -------------------------------------- GLOBALS ---------------------------------------
const Uint8* KEYBOARD_STATE = NULL; // keyboard state
const int W_W = 1024;               // SDL window width
const int W_H = 768;                // SDL window height
SDL_Window* WINDOW = NULL;          // SDL window
SDL_Renderer* RENDERER = NULL;      // SDL renderer
int IS_RUNNING = 1;                 // main loop flag
int SHOW_MAP = 0;                   // flag representing if the top-down map or the first person view should be rendered
int HAS_WON = 0;                    // flag representing if the game is won. The game is won if player reaches the
									// bottom-right cell of the maze

// -------------------------------------- FUNCTIONS ---------------------------------------
/**
 * Clears the background and sets the background color to black.
 */
void ClearBackground()
{
	SDL_SetRenderDrawColor(RENDERER, 0, 0, 0, SDL_ALPHA_OPAQUE); // Set background color
	SDL_RenderClear(RENDERER); // clear RENDERER
}

/**
 * Renders the wall rectangles representing walls.
 */
void DrawMapWallRectangles()
{
	for (int i = 0; i < M_WALL_RECTS_LENGTH; ++i)
	{
		SDL_SetRenderDrawColor(RENDERER, 128, 128, 128, SDL_ALPHA_OPAQUE);
		SDL_RenderFillRectF(RENDERER, &M_WALL_RECTS[i]);
	}
}

/**
 * Renders the floor in first-person view.
 */
void DrawFloor()
{
	SDL_FRect rect;
	rect.x = 0.0f;
	rect.y = (float)W_H / 2;
	rect.h = (float)W_H / 2;
	rect.w = (float)W_W;
	SDL_SetRenderDrawColor(RENDERER, 65, 65, 65, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRectF(RENDERER, &rect);
}

/**
 * Renders the ceiling in first-person view.
 */
void DrawCeiling()
{
	SDL_FRect rect;
	rect.x = 0.0f;
	rect.y = 0.0f;
	rect.h = (float)W_H / 2.0f;
	rect.w = (float)W_W;
	SDL_SetRenderDrawColor(RENDERER, 95, 95, 95, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRectF(RENDERER, &rect);
}

/**
 * Renders the line representing the direction that the player is facing.
 */
void DrawPlayerDirection()
{
	Vec3* playerDirectionIntersection = CalculateFinalIntersection(P_POS, P_DIR,
			M_CELL_SIZE, MAP, M_SIZE);
	if (playerDirectionIntersection->z == 1.0f) // red line if player direction ray intersects with vertical wall
	{SDL_SetRenderDrawColor(RENDERER, 225, 0, 0, SDL_ALPHA_OPAQUE);}
	else if (playerDirectionIntersection->z == -1.0f) // blue line if player direction ray intersects with vertical wall
	{SDL_SetRenderDrawColor(RENDERER, 0, 0, 225, SDL_ALPHA_OPAQUE);}
	SDL_RenderDrawLineF(RENDERER, playerDirectionIntersection->x, playerDirectionIntersection->y, P_POS->x,
			P_POS->y);
	free(playerDirectionIntersection);
}

/**
 * Renders all the rays cast by player with in the field of view.
 */
void DrawRays()
{
	if (P_RAYS != NULL)
	{free(P_RAYS);}
	P_RAYS = CalculateIntersections(P_POS, P_DIR, M_CELL_SIZE, MAP, M_SIZE,
			P_FOV, P_NUM_RAYS);
	SDL_SetRenderDrawColor(RENDERER, 125, 225, 125, SDL_ALPHA_OPAQUE);
	for (int i = 0; i < P_NUM_RAYS; ++i)
	{
		SDL_RenderDrawLineF(RENDERER, P_RAYS[i].x, P_RAYS[i].y, P_POS->x, P_POS->y);
	}
}

/**
 * Renders the crosshair.
 */
void DrawCrosshair()
{
	SDL_FRect rect;
	rect.x = (float)W_W / 2 - 5;
	rect.y = (float)W_H / 2 - 5;
	rect.h = 10;
	rect.w = 10;
	SDL_RenderFillRectF(RENDERER, &rect);
}

/**
 * Renders the first-person view.
 */
void DrawFirstPersonView()
{
	DrawCeiling();
	DrawFloor();
	if (P_RAYS != NULL)
	{free(P_RAYS);}
	P_RAYS = CalculateIntersections(P_POS, P_DIR, M_CELL_SIZE, MAP, M_SIZE,
			P_FOV, P_NUM_RAYS);
	if (P_RAY_HEIGHTS != NULL)
	{free(P_RAY_HEIGHTS);}
	P_RAY_HEIGHTS = CalculateHeights(P_RAYS, P_POS, P_DIR, P_NUM_RAYS,
			(float)W_H);
	float rectWidth = (float)W_W / (float)P_NUM_RAYS;
	for (int i = 0; i < P_NUM_RAYS; ++i)
	{
		if (P_RAYS[i].z == -1)
		{SDL_SetRenderDrawColor(RENDERER, 155, 155, 155, SDL_ALPHA_OPAQUE);}
		else
		{SDL_SetRenderDrawColor(RENDERER, 195, 195, 195, SDL_ALPHA_OPAQUE);}
		SDL_FRect rect;
		rect.x = (float)i * rectWidth;
		rect.y = (float)W_H / 2 - P_RAY_HEIGHTS[i] / 2;
		rect.h = P_RAY_HEIGHTS[i];
		rect.w = rectWidth;
		SDL_RenderFillRectF(RENDERER, &rect);
	}
	Vec3* playerDirectionIntersection = CalculateFinalIntersection(P_POS, P_DIR,
			M_CELL_SIZE, MAP, M_SIZE);
	// Updates the status of the cell where the player is currently located, changes the status to visited
	int currentPlayerCellIndex = GetPlayerCellIndex(P_POS, M_CELL_SIZE, M_SIZE);
	MAP_STATUS[currentPlayerCellIndex] = 2;

	// Gets the index of the cell pointed by the cross-hairs
	int currentPointedCellIndex = GetPointedNonWallCellIndex(playerDirectionIntersection, P_DIR,
			M_CELL_SIZE, M_SIZE);
	if (MAP_STATUS[currentPointedCellIndex] == 2)
	{SDL_SetRenderDrawColor(RENDERER, 225, 0, 0, SDL_ALPHA_OPAQUE);}
	else
	{SDL_SetRenderDrawColor(RENDERER, 0, 225, 0, SDL_ALPHA_OPAQUE);}
	DrawCrosshair();
}

/**
 * Renders the top-down view.
 */
void DrawTopDownView()
{
	DrawRays();
	DrawPlayerDirection();
}

/**
 * Renders top-down view or first-person view based on user input.
 */
void Draw()
{
	ClearBackground();
	DrawMapWallRectangles();
	UpdatePlayerPosition(KEYBOARD_STATE, P_MOVE_FORWARD, P_MOVE_BACKWARD,
			P_TURN_CW, P_TURN_CCW, P_POS, P_DIR,
			P_STEP_SCALAR, P_RECT_SIZE, P_ABS_TURNING_ANGLE,
			M_WALL_RECTS, M_WALL_RECTS_LENGTH);
	if (SHOW_MAP)
	{DrawTopDownView();}
	else
	{DrawFirstPersonView();}
}

/**
 * Updates the game status on whether the winning condition is achieved.
 */
void UpdateGameStatus()
{
	if (GetPlayerCellIndex(P_POS, M_CELL_SIZE, M_SIZE) == M_SIZE * M_SIZE - M_SIZE - 2)
	{
		HAS_WON = 1;
	}
}

/**
 * Renders the end state after the winning condition is achieved. The end state rotates the player slowly automatically.
 */
void DrawEndState()
{
	Rotate3D(P_DIR, 0.01f);
	ClearBackground();
	DrawMapWallRectangles();
	if (SHOW_MAP)
	{
		DrawTopDownView();
	}
	else
	{
		DrawFirstPersonView();
	}
	SDL_RenderPresent(RENDERER); // Updates buffer
}

// ------------------------------------------ SDL RENDERING PIPELINE ------------------------------------------
/**
 * Initializes SDL2 video system and creates SDL window and SDL renderer.
 */
void Initialize()
{
	SDL_Init(SDL_INIT_VIDEO);
	WINDOW = SDL_CreateWindow("RayCastingMaze",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			W_W,
			W_H,
			SDL_WINDOW_SHOWN);
	RENDERER = SDL_CreateRenderer(WINDOW, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	KEYBOARD_STATE = SDL_GetKeyboardState(NULL);
	// Initializes map
	InitializeMap(&MAP_STATUS, &MAP, &M_SIZE, 23, &M_CELL_SIZE, 32.0f);
	// Create rectangles representing walls
	M_WALL_RECTS = CreateMapWallRects(&M_WALL_RECTS_LENGTH, M_CELL_SIZE, MAP, M_SIZE);
	// Initializes player position vector, player always starts at the top-left cell in the maze
	P_POS = Vec3D(M_CELL_SIZE + 1.0f, M_CELL_SIZE + 1.0f, 0.0f);
	// Initializes player direction vector, direction vector is always a unit vector
	P_DIR = Vec3D(1.0f, 0.0f, 0.0f);
}

/**
 * Runs program's main loop.
 */
void RunMainLoop()
{
	while (IS_RUNNING)
	{
		// Event queue
		SDL_Event event;
		// Handles event
		while (SDL_PollEvent(&event))
		{
			// clicks on Close or presses ESCAPE to quit
			if (event.type == SDL_QUIT || event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			{IS_RUNNING = !IS_RUNNING;}
			// presses SPACE to render top-down map
			if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.scancode == SDL_SCANCODE_SPACE)
				{SHOW_MAP = !SHOW_MAP;}
			}
		}
		// Checks winning status
		if (HAS_WON)
		{
			DrawEndState();
			continue;
		}
		// Update wining flag
		UpdateGameStatus();
		// Draw
		Draw();
		// Updates buffer
		SDL_RenderPresent(RENDERER);
	}
}

/**
 * Cleans up used memory and quit program.
 */
void CleanUp()
{
	if (P_POS != NULL)
	{free(P_POS);} 					// frees player position vector
	if (P_DIR != NULL)
	{free(P_DIR);} 					// frees player direction vector
	if (P_RAYS != NULL)
	{free(P_RAYS);} 				// frees the ray array representing rays cast by players
	if (MAP != NULL)
	{free(MAP);}					// frees the map array
	if (MAP_STATUS != NULL)
	{free(MAP_STATUS);}				// frees the map status array
	if (M_WALL_RECTS != NULL)
	{free(M_WALL_RECTS);} 			// frees rectangle array representing walls
	SDL_DestroyWindow(WINDOW); 		// free SDL window
	SDL_DestroyRenderer(RENDERER); 	// free SDL renderer
	SDL_Quit();						// quits
}

int main()
{
	// Initialization
	Initialize();
	// Main loop
	RunMainLoop();
	// Clean up
	CleanUp();
	return 0;
}