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
	void (*displayMethod)(void *,FILE *);
	void (*freeMethod)(void *);
	int debugFlag;
};

// Including the DA struct for refrencing within pointers
struct da
{
	// Components
	void **data;
	int capacity, sizeDA, debugFlag; // Capacity == Total size, size == used size
	void(*displayMethod)(void *, FILE *);
	void(*freeMethod)(void *);
};

// Creates a new STACK struct
STACK *newSTACK(void)
{
	STACK *newST;
	newST = (STACK *) malloc(sizeof(STACK));
	newST->dynamicArr = newDA();
	newST->debugFlag = 0;
	return newST;
}

// This function is just going to double the size of a dynamic array
void doubleStackStorage(DA *items)
{
	if (items->data == NULL)
	{
		items->data = (void**)malloc(sizeof(void*) * items->capacity);
		for (int i = 0; i < items->capacity; i++)
		{
			items->data[i] = NULL;
		}
		return;
	}
	items->capacity *= 2;
	items->data = (void**)realloc(items->data, sizeof(void*) * items->capacity);
}

// Function made for halving storage size for the remove function
void halfStackStorage(DA *items)
{
	items->capacity /= 2;
	items->data = (void**)realloc(items->data, sizeof(void*) * items->capacity);
}


// Stores the diplay method in the STACK via the DA
void setSTACKdisplay(STACK *items,void (*dpMethod)(void *dpMethod,FILE *))
{
	setDAdisplay(items->dynamicArr, dpMethod);
	items->displayMethod = dpMethod;
}

// Stores the free method in the STACK via the DA
void setSTACKfree(STACK *items,void (*freeMethod)(void *))
{
	setDAfree(items->dynamicArr, freeMethod);
	items->freeMethod = freeMethod;
}

// Adds a value onto the stack
void push(STACK *items, void *value)
{
	if (items->dynamicArr->capacity == items->dynamicArr->sizeDA)
		doubleStackStorage(items->dynamicArr);
	insertDA(items->dynamicArr, sizeDA(items->dynamicArr), value);
}

// Pops the next value from the stack
void *pop(STACK *items)
{
	return removeDA(items->dynamicArr, items->dynamicArr->sizeDA-1);
	//while ((float)(sizeDA(items->dynamicArr) / items->dynamicArr->capacity < 0.25f && items->dynamicArr->capacity > 1))
	//	halfStackStorage(items->dynamicArr);
	//return returnVal;
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
	fprintf(fp, "|");
	for (int i = 0; i < items->dynamicArr->sizeDA; i++)
	{
		if (i > 0)
			fprintf(fp, ",");
		if (items->displayMethod == NULL)
			fprintf(fp, "@%p", getDA(items->dynamicArr, i));
		else
			items->displayMethod(getDA(items->dynamicArr, i), fp);
	}
	if (items->debugFlag > 0)
	{
		if(sizeDA(items->dynamicArr) > 0)
			fprintf(fp, ",|%d|", items->dynamicArr->capacity - sizeDA(items->dynamicArr));
		else
			fprintf(fp, "|%d|", items->dynamicArr->capacity - sizeDA(items->dynamicArr));
	}
	fprintf(fp, "|");
}

// Shows the items in the order the debug mode dictates
int debugSTACK(STACK *items, int level)
{
	int prevVal = items->debugFlag;
	items->debugFlag = level;
	return prevVal;
}

// Frees the data with the given method
void freeSTACK(STACK *items)
{
	if (items->freeMethod != NULL)
	{
		freeDA(items->dynamicArr);
		items->freeMethod(items);
		
	}
}
