/*
QUEUE Implementation File
This is file contains the implementation for the stack.h header file

File author: Connor Adams
*/

#include "queue.h"
#include "cda.h"

struct queue
{
	CDA *cda;
	void(*displayMethod)(void *, FILE *);
	void(*freeMethod)(void *);
	int debugFlag;
};

// Again, for refrencing
struct cda
{
	void **data;
	int capacity, sizeDA, debugFlag, startIndex;
	void(*displayMethod)(void *, FILE *);
	void(*freeMethod)(void *);
};

// Creates a new QUEUE struct
QUEUE *newQUEUE(void)
{
	QUEUE *newQ;
	newQ = (QUEUE *)malloc(sizeof(QUEUE));
	newQ->cda = newCDA();
	return newQ;
}

// Stores the diplay method in the QUEUE via the CDA
void setQUEUEdisplay(QUEUE *items, void(*dpMethod)(void *dpMethod, FILE *))
{
	setCDAdisplay(items->cda, dpMethod);
	items->displayMethod = dpMethod;
}

// Stores the free method in the QUEUE via the CDA
void setQUEUEfree(QUEUE *items, void(*freeMethod)(void *))
{
	setCDAfree(items->cda, freeMethod);
	items->freeMethod = freeMethod;
}

// Enqueues a value, which just adds it to the end of the CDA
void enqueue(QUEUE *items, void *value)
{
	insertCDAback(items->cda, value);
}

// Dequeues a value, just takes the first items from the CDA
void *dequeue(QUEUE *items)
{
	return removeCDAfront(items->cda);
}

// Shows the next value to be dequeued
void *peekQUEUE(QUEUE *items)
{
	return getCDA(items->cda, sizeCDA(items->cda) - 1);
}

// Shows the values in order from lowest to highest index
void displayQUEUE(QUEUE *items, FILE *fp)
{
	fprintf(fp, "<");
	for (int i = items->cda->startIndex; i < sizeCDA(items->cda); i++)
	{
		if (i != items->cda->startIndex)
			fprintf(fp, ",");
		if (items->displayMethod == NULL)
			fprintf(fp, "@%p", getCDA(items->cda, i % items->cda->capacity));
		else
			items->displayMethod(getCDA(items->cda, i % items->cda->capacity), fp);
	}
	if (items->debugFlag > 0)
	{
		if (sizeCDA(items->cda) > 0)
			fprintf(fp, ",<%d>", items->cda->capacity - items->cda->sizeDA);
		else
			fprintf(fp, "<%d>", items->cda->capacity - items->cda->sizeDA);
	}
	fprintf(fp, ">");
}

// Runs the debug for level
int debugQUEUE(QUEUE *items, int level)
{
	int prevVal = items->debugFlag;
	items->debugFlag = level;
	return prevVal;
}

// Runs the stores free algo on the cda
void freeQUEUE(QUEUE *items)
{
	freeCDA(items->cda);
}

// Returns the size of the queue
int sizeQUEUE(QUEUE *items)
{
	return sizeCDA(items->cda);
}