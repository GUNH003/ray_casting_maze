#ifndef RAY_CASTING_MAZE_PLAYER_H_
#define RAY_CASTING_MAZE_PLAYER_H_

#include <SDL.h>
#include "../Utils/Vec3/Vec3.h"

// -------------------------------------- GLOBALS -----------------------------------------
extern const float P_ABS_TURNING_ANGLE;  // absolute unit turning angle in radians
extern const float P_STEP_SCALAR;        // scale coefficient for change in player's position
extern const float P_RECT_SIZE;          // the size of the square bounding box for the player
extern const float P_FOV;                // player's field of view
extern const int P_NUM_RAYS;             // the number of rays cast by player within the field of view
extern int P_TURN_CW;                    // flag variable representing if the right arrow key is pressed
extern int P_TURN_CCW;                   // flag variable representing if the left arrow key is pressed
extern int P_MOVE_FORWARD;               // flag variable representing if the up arrow key is pressed
extern int P_MOVE_BACKWARD;              // flag variable representing if the down arrow key is pressed
extern float* P_RAY_HEIGHTS;             // the converted height information for the rays cast by player
extern Vec3* P_POS;                      // player position vector
extern Vec3* P_DIR;                      // player direction vector, this is always a unit vector
extern Vec3* P_RAYS;                     // array of vectors representing the intersections points between rays cast by
										 // player and walls, within the field of view

// ------------------------------------------- FUNCTIONS -------------------------------------------
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
		float absoluteTurningAngle);

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
		float playerStepSizeScalar, float playerSize, SDL_FRect* mapRectArray, int mapRectArraySize);

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
		float playerSize, float playerAbsoluteTurningAngle, SDL_FRect* mapRectArray, int mapRectArraySize);

/**
 * Gets the index of the cell in which the player is currently located.
 *
 * @param playerPosition	the vector representing the player position
 * @param mapCellSize 		the size of each cell in the map grid
 * @param mapSize 			the side length of the square map grid
 * @return the index of the cell in which the player is currently located
 */
int GetPlayerCellIndex(Vec3* playerPosition, float mapCellSize, int mapSize);

#endif