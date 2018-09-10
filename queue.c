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
	for (int i = startIndexCDA(items->cda); i < sizeCDA(items->cda); i++)
	{
		if (i != startIndexCDA(items->cda))
			fprintf(fp, ",");
		if (items->displayMethod == NULL)
			fprintf(fp, "@%p", getCDA(items->cda, i%capacityCDA(items->cda)));
		else
			items->displayMethod(getCDA(items->cda, i%capacityCDA(items->cda)), fp);
	}
	if (items->debugFlag > 0)
	{
		if (sizeCDA(items->cda) > 0)
			fprintf(fp, ",<%d>", capacityCDA(items->cda) - sizeCDA(items->cda));
		else
			fprintf(fp, "<%d>", capacityCDA(items->cda )- sizeCDA(items->cda));
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