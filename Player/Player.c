#include "Player.h"
#include "../Utils/Collision/Collision.h"
#include "../Utils/ErrorHandler/ErrorHandler.h"

const float P_ABS_TURNING_ANGLE = 0.05f;    // absolute unit turning angle in radians
const float P_STEP_SCALAR = 2.0f;           // scale coefficient for change in player's position
const float P_RECT_SIZE = 0.5f;             // the size of the square bounding box for the player
const float P_FOV = M_PI / 3;               // player's field of view
const int P_NUM_RAYS = 1200;                // the number of rays cast by player within the field of view
int P_TURN_CW = 0;                          // flag variable representing if the right arrow key is pressed
int P_TURN_CCW = 0;                         // flag variable representing if the left arrow key is pressed
int P_MOVE_FORWARD = 0;                     // flag variable representing if the up arrow key is pressed
int P_MOVE_BACKWARD = 0;                    // flag variable representing if the down arrow key is pressed
float* P_RAY_HEIGHTS = NULL;                // the converted height information for the rays cast by player
Vec3* P_POS = NULL;                         // player position vector
Vec3* P_DIR = NULL;                         // player direction vector, this is always a unit vector
Vec3* P_RAYS = NULL;                        // array of vectors representing the intersections points between rays cast
											// by player and walls, within the field of view

/**
 * Turns the player based on key pressed. Turning clockwise when right arrow key flag is on, turning counter clockwise
 * when left arrow key flag is on.  In-place modification is made to the player position vector.
 *
 * @param isTurningClockwise		 flag variable representing if right arrow key is pressed
 * @param isTurningCounterClockwise  flag variable representing if left arrow key is pressed
 * @param playerDirection 			 the vector representing the direction that the player is facing, this vector is
 									 a unit vector
 * @param playerAbsoluteTurningAngle the unit turning angle in radians, representing the amount turned each time the
 									 corresponding turning key is pressed
 */
void TurnPlayer(int isTurningClockwise, int isTurningCounterClockwise, Vec3* playerDirection,
		float playerAbsoluteTurningAngle)
{
	if (playerDirection == NULL)
	{ErrorHandler(ACCESSING_NULL_POINTER_ERROR);}
	if (isTurningClockwise) // turn right
	{
		printf("Turned clockwise.\n");
		printf("Theta before turning:  %f\n", atanf(playerDirection->y / playerDirection->x));
		Rotate3D(playerDirection, playerAbsoluteTurningAngle);
		printf("Theta  after turning:  %f\n", atanf(playerDirection->y / playerDirection->x));
	}
	if (isTurningCounterClockwise) // turn left
	{
		printf("Turned counter-clockwise.\n");
		printf("Theta before turning:  %f\n", atanf(playerDirection->y / playerDirection->x));
		Rotate3D(playerDirection, -playerAbsoluteTurningAngle);
		printf("Theta  after turning:  %f\n", atanf(playerDirection->y / playerDirection->x));
	}
}

/**
 * Moves the player based on key pressed. Moves forward when up arrow key is pressed, moves backward when down arrow
 * key is pressed. In-place modification is made to the player position vector. The player's position will only be
 * updated if the position of the next move is not in collision with any walls in the map.
 *
 * @param isMovingForward 		flag variable representing if up arrow key is pressed
 * @param isMovingBackWard		flag variable representing if down arrow key is pressed
 * @param playerPosition		the vector representing the player position
 * @param playerDirection		the vector representing the direction that the player is facing, this vector is
								a unit vector
 * @param playerStepSizeScalar 	the scalar that used to scale the vector representing the player's next move
 * @param playerSize			the side length of the player's square bounding box
 * @param mapRectArray			the rectangle array representing walls in map
 * @param mapRectArraySize		the length of the rectangle array
 */
void MovePlayer(int isMovingForward, int isMovingBackWard, Vec3* playerPosition, Vec3* playerDirection,
		float playerStepSizeScalar, float playerSize, SDL_FRect* mapRectArray, int mapRectArraySize)
{
	if (playerPosition == NULL || playerDirection == NULL || mapRectArray == NULL)
	{ErrorHandler(ACCESSING_NULL_POINTER_ERROR);}
	Vec3 playerNextPosition = *playerPosition;
	// Updates next position forward
	if (isMovingForward)
	{
		Vec3* newDir = Vec3D(playerDirection->x, playerDirection->y, playerDirection->z);
		Scale3D(newDir, playerStepSizeScalar);
		Translate3D(&playerNextPosition, newDir);
		free(newDir);
		printf("Current position:      (%f, %f)\n", playerPosition->x, playerPosition->y);
	}
		// Updates next position backward
	else if (isMovingBackWard)
	{
		Vec3* newDir = Vec3D(playerDirection->x, playerDirection->y, playerDirection->z);
		Scale3D(newDir, playerStepSizeScalar);
		Invert3D(newDir);
		Translate3D(&playerNextPosition, newDir);
		free(newDir);
		printf("Current position:      (%f, %f)\n", playerPosition->x, playerPosition->y);
	}
	// next rectangle, for collision detection
	SDL_FRect nextPosRect;
	// Create a rectangle representing the next position of the player
	nextPosRect.x = playerNextPosition.x - (playerSize / 2);
	nextPosRect.y = playerNextPosition.y - (playerSize / 2);
	nextPosRect.w = playerSize;
	nextPosRect.h = playerSize;
	// updates playerPosition if no collision
	if (!CheckCollisionWithMapRectArray(&nextPosRect, mapRectArray, mapRectArraySize))
	{
		playerPosition->x = playerNextPosition.x;
		playerPosition->y = playerNextPosition.y;
	}
}

/**
 * Updates player's position. This function checks if the keys controlling player movement are pressed and calls
 * corresponding functions to update player's position. In-place modification is made to the player position vector.
 *
 * @param keyboardState  				keeps track of key board state using scan codes
 * @param isMovingForward				flag variable representing if up arrow key is pressed
 * @param isMovingBackWard				flag variable representing if down arrow key is pressed
 * @param isTurningClockwise 			flag variable representing if right arrow key is pressed
 * @param isTurningCounterClockwise 	flag variable representing if left arrow key is pressed
 * @param playerPosition 				the vector representing the player position
 * @param playerDirection 				the vector representing the direction that the player is facing, this vector is
 									 	a unit vector
 * @param playerStepSizeScalar 			the scalar that used to scale the vector representing the player's next move
 * @param playerSize 					the side length of the player's square bounding box
 * @param playerAbsoluteTurningAngle 	the unit turning angle in radians, representing the amount turned each time the
 									 	corresponding turning key is pressed
 * @param mapRectArray 					the rectangle array representing walls in map
 * @param mapRectArraySize 				the length of the rectangle array
 */
void UpdatePlayerPosition(const Uint8* keyboardState, int isMovingForward, int isMovingBackWard, int isTurningClockwise,
		int isTurningCounterClockwise, Vec3* playerPosition, Vec3* playerDirection, float playerStepSizeScalar,
		float playerSize, float playerAbsoluteTurningAngle, SDL_FRect* mapRectArray, int mapRectArraySize)
{
	if (keyboardState == NULL || playerPosition == NULL || playerDirection == NULL || mapRectArray == NULL)
	{ErrorHandler(ACCESSING_NULL_POINTER_ERROR);}
	// Update action states
	isMovingForward = keyboardState[SDL_SCANCODE_UP] > 0;
	isMovingBackWard = keyboardState[SDL_SCANCODE_DOWN] > 0;
	isTurningClockwise = keyboardState[SDL_SCANCODE_RIGHT] > 0;
	isTurningCounterClockwise = keyboardState[SDL_SCANCODE_LEFT] > 0;
	TurnPlayer(isTurningClockwise, isTurningCounterClockwise, playerDirection,
			playerAbsoluteTurningAngle);
	MovePlayer(isMovingForward, isMovingBackWard, playerPosition, playerDirection,
			playerStepSizeScalar, playerSize, mapRectArray, mapRectArraySize);
}

/**
 * Gets the index of the cell in which the player is currently located.
 *
 * @param playerPosition	the vector representing the player position
 * @param mapCellSize 		the size of each cell in the map grid
 * @param mapSize 			the side length of the square map grid
 * @return the index of the cell in which the player is currently located
 */
int GetPlayerCellIndex(Vec3* playerPosition, float mapCellSize, int mapSize)
{
	if (playerPosition == NULL)
	{ErrorHandler(ACCESSING_NULL_POINTER_ERROR);}
	return (int)(playerPosition->y / mapCellSize) * mapSize + (int)(playerPosition->x / mapCellSize);
}