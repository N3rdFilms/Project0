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
}

// Stores the free method in the QUEUE via the CDA
void setQUEUEfree(QUEUE *items, void(*freeMethod)(void *))
{
	setCDAfree(items->cda, freeMethod);
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
	displayCDA(items->cda, fp);
}

// Runs the debug for level
int debugQUEUE(QUEUE *items, int level)
{
	return debugCDA(items->cda, level);
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