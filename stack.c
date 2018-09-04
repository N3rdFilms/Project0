/*
STACK Implementation File
This is file contains the implementation for the stack.h header file

File author: Connor Adams
*/

#include "stack.h"
#include "da.h"

struct stack
{
	DA *dynamicArr;
};

// Creates a new STACK struct
STACK *newSTACK(void)
{
	STACK *newST;
	newST = (STACK *) malloc(sizeof(STACK));
	newST->dynamicArr = newDA();
	return newST;
}

// Stores the diplay method in the STACK via the DA
void setSTACKdisplay(STACK *items,void (*dpMethod)(void *dpMethod,FILE *))
{
	setDAdisplay(items->dynamicArr, dpMethod);
}

// Stores the free method in the STACK via the DA
void setSTACKfree(STACK *items,void (*freeMethod)(void *))
{
	setDAfree(items->dynamicArr, freeMethod);
}

// Adds a value onto the stack
void push(STACK *items, void *value)
{
	if (capacityDA(items->dynamicArr) == (sizeDA(items->dynamicArr)))
		doubleStorage(items->dynamicArr);
	insertDA(items->dynamicArr, sizeDA(items->dynamicArr), value);
}

// Pops the next value from the stack
void *pop(STACK *items)
{
	void *returnVal = removeDA(items->dynamicArr, sizeDA(items->dynamicArr) -1);
	if ((float)(sizeDA(items->dynamicArr) / capacityDA(items->dynamicArr) <= 0.25f && capacityDA(items->dynamicArr) > 1))
		halfStorage(items->dynamicArr);
	return returnVal;
}

// Shows what is next to be popped
void *peekSTACK(STACK *items)
{
	return getDA(items->dynamicArr, sizeDA(items->dynamicArr) - 1);
}

// Returns how many items are on the stack
int sizeSTACK(STACK *items)
{
	return sizeDA(items->dynamicArr);
}

// Shows the items in the stack in reverse order they were pushed, so index order
void displaySTACK(STACK *items, FILE *fp)
{
	displayDA(items->dynamicArr, fp);
}

// Shows the items in the order the debug mode dictates
int debugSTACK(STACK *items, int level)
{
	return debugDA(items->dynamicArr, level);
}

// Frees the data with the given method
void freeSTACK(STACK *items)
{
	freeDA(items->dynamicArr); // TODO: THIS WAS ABORTING AND THEN STOPPED MYSTERIOUSLY
}