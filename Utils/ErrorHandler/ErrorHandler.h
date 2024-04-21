#ifndef RAY_CASTING_MAZE_ERRORHANDLER_H_
#define RAY_CASTING_MAZE_ERRORHANDLER_H_

// Error codes
#define MEMORY_ALLOCATION_ERROR 1
#define ACCESSING_NULL_POINTER_ERROR 2
#define POPPING_FROM_EMPTY_STACK_ERROR 3
#define UNKNOWN_ERROR 9

/**
 * Handles error based on the given error code. It exits the program and prints corresponding error message on
 * the console.
 *
 * @param errorCode the given error code
 */
void ErrorHandler(int errorCode);

#endif
