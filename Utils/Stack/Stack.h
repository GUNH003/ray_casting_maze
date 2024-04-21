#ifndef RAY_CASTING_MAZE_STACK_H_
#define RAY_CASTING_MAZE_STACK_H_

#define RESIZE_FACTOR 2 // previousSize * RESIZE_FACTOR = newSize, used to allocate memory for new array

/**
 * Stack of integer.
 */
typedef struct Stack_struct
{
    int size;
    int length;
    int* array;
}Stack;

/**
 * Creates an empty stack of integer.
 *
 * @return an empty stack of integer
 */
Stack* CreateStack();

/**
 * Free the memory allocated for the given stack.
 *
 * @param stack the given stack
 */
void DestroyStack(Stack* stack);

/**
 * Checks if the give stack is empty.
 *
 * @param stack the given stack
 * @return 1 if the stack is empty, 0 otherwise.
 */
int IsEmpty(Stack* stack);

/**
 * Pushes an integer into the given stack.
 *
 * @param stack the given stack
 * @param num the integer
 */
void Push(Stack* stack, int num);

/**
 * Pops an integer from the given stack.
 *
 * @param stack the given stack
 */
void Pop(Stack* stack);

/**
 * Gets the integer at the top of the given stack.
 *
 * @param stack the given stack
 * @return the integer at the top of the given stack
 */
int Top(Stack* stack);

#endif
