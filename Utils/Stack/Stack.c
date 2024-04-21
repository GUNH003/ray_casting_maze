#include <stdlib.h>
#include <stdio.h>
#include "Stack.h"
#include "../ErrorHandler/ErrorHandler.h"

/**
 * Creates an empty stack of integer.
 *
 * @return an empty stack of integer
 */
Stack* CreateStack()
{
	Stack* emptyStack = (Stack*)calloc(1, sizeof(Stack));
	if (emptyStack == NULL)
	{ ErrorHandler(MEMORY_ALLOCATION_ERROR); }
	emptyStack->size = 1;
	emptyStack->array = (int*)calloc(emptyStack->size, sizeof(int));
	emptyStack->length = 0;
	return emptyStack;
}

/**
 * Free the memory allocated for the given stack.
 *
 * @param stack the given stack
 */
void DestroyStack(Stack* stack)
{
	if (stack == NULL)
	{ ErrorHandler(ACCESSING_NULL_POINTER_ERROR); }
	free(stack->array);
	free(stack);
}

/**
 * Checks if the give stack is empty.
 *
 * @param stack the given stack
 * @return 1 if the stack is empty, 0 otherwise.
 */
int IsEmpty(Stack* stack)
{
	if (stack == NULL)
	{ ErrorHandler(ACCESSING_NULL_POINTER_ERROR); }
	return stack->length == 0;
}

/**
 * Checks if the current array in the given stack is full.
 *
 * @param stack the given stack
 * @return 1 if the current array in the given stack is full, 0 otherwise
 */
int IsFull(Stack* stack)
{
	if (stack == NULL)
	{ ErrorHandler(ACCESSING_NULL_POINTER_ERROR); }
	return stack->length == stack->size;
}

/**
 * Resizes the array in the given stack. Each time the new array allocated is RESIZE_FACTOR times the size of the
 * original array. The original array was freed before assigning the new allocated array to the given stack.
 *
 * @param stack the given stack
 */
void Resize(Stack* stack)
{
	if (stack == NULL)
	{ ErrorHandler(ACCESSING_NULL_POINTER_ERROR); }
	int* newArray = (int*)calloc((stack->size) * RESIZE_FACTOR, sizeof(int));
	for (int i = 0; i < stack->length; ++i)
	{ newArray[i] = (stack->array)[i]; }
	free(stack->array);
	stack->array = newArray;
	(stack->size) *= 2;
}

/**
 * Pushes an integer into the given stack.
 *
 * @param stack the given stack
 * @param num the integer
 */
void Push(Stack* stack, int num)
{
	if (stack == NULL)
	{ ErrorHandler(ACCESSING_NULL_POINTER_ERROR); }
	// Resizes the stack if necessary
	if (IsFull(stack))
	{ Resize(stack); }
	(stack->array)[stack->length] = num;
	++(stack->length);
}

/**
 * Pops an integer from the given stack.
 *
 * @param stack the given stack
 */
void Pop(Stack* stack)
{
	if (stack == NULL)
	{ ErrorHandler(ACCESSING_NULL_POINTER_ERROR); }
	if (!IsEmpty(stack))
	{ (stack->array)[--(stack->length)] = 0; }
	else
	{ ErrorHandler(POPPING_FROM_EMPTY_STACK_ERROR); }
}

/**
 * Gets the integer at the top of the given stack.
 *
 * @param stack the given stack
 * @return the integer at the top of the given stack
 */
int Top(Stack* stack)
{
	if (!IsEmpty(stack))
	{ return (stack->array)[stack->length - 1]; }
	else
	{
		printf("ERROR: Stack is empty.");
		return INT8_MIN;
	}
}