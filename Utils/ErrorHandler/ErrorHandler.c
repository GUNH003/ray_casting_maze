#include <stdio.h>
#include <stdlib.h>
#include "ErrorHandler.h"

/**
 * Handles error based on the given error code. It exits the program and prints corresponding error message on
 * the console.
 *
 * @param errorCode the given error code
 */
void ErrorHandler(int errorCode)
{
	switch (errorCode)
	{
	case MEMORY_ALLOCATION_ERROR:
		printf("ErrCode: %d. Memory allocation failed.", MEMORY_ALLOCATION_ERROR);
		exit(MEMORY_ALLOCATION_ERROR);
	case ACCESSING_NULL_POINTER_ERROR:
		printf("ErrCode: %d. Accessing null pointer.", ACCESSING_NULL_POINTER_ERROR);
		exit(ACCESSING_NULL_POINTER_ERROR);
	case POPPING_FROM_EMPTY_STACK_ERROR:
		printf("ErrCode: %d. Popping from empty stack.", POPPING_FROM_EMPTY_STACK_ERROR);
		exit(POPPING_FROM_EMPTY_STACK_ERROR);
	default:
		printf("ErrCode: %d. Unknown error.", UNKNOWN_ERROR);
		exit(UNKNOWN_ERROR);
	}
}