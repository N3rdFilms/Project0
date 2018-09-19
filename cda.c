/*
Circular Dynamic Array Implementation File
This is file contains the implementation for the cda.h header file

File author: Connor Adams
*/

#include "cda.h"

struct cda
{
	void **data;
	int capacity, sizeDA, debugFlag, startIndex;
	void (*displayMethod)(void *,FILE *);
	void (*freeMethod)(void *);
};

// This function is just going to double the size of a dynamic array
void doubleCDAStorage(CDA *items) //TODO: VERIFY THE CHANGE FROM REALLOC WORKED
{
	void **holder = (void**)malloc(sizeof(void*) * items->capacity * 2);
	for (int i = items->startIndex; i < items->sizeDA; i++)
	{
		holder[i % (items->capacity * 2)] = items->data[i % (items->capacity)];
	}
	items->capacity *= 2;
	free(items->data);
	items->data = (void**)malloc(sizeof(void*) * items->capacity);
	for (int i = items->startIndex; i < items->sizeDA; i++)
	{
		items->data[i % (items->capacity)] = holder[i % (items->capacity)];
	}
	free(holder);
}

// Function made for halving storage size for the remove function
void halfCDAStorage(CDA *items)
{
	items->capacity /= 2;
	items->data = (void**)realloc(items->data, sizeof(void*) * items->capacity);
}

// Creates a new CDA and returns it
CDA *newCDA(void)
{
	CDA *newCDA;
	newCDA = (CDA *) malloc(sizeof(CDA));
	newCDA->data = (void**)malloc(sizeof(void*));
	newCDA->capacity = 1;
	newCDA->sizeDA = 0;
	newCDA->debugFlag = 0;
	newCDA->startIndex = 0;
	newCDA->freeMethod = NULL;
	newCDA->displayMethod = NULL;
	return newCDA;
}

// Takes in and stores the display method for CDA
void setCDAdisplay(CDA *items, void (*displayInput)(void *,FILE *) )
{
	items->displayMethod = displayInput;
}

// Takes in and stores the free method for CDA
void setCDAfree(CDA *items, void (*freeInput)(void *))
{
	items->freeMethod = freeInput;
}

// Returns the value at index, corrected for index start num
void *getCDA(CDA *items, int index)
{
	assert(index >= 0 && index < items->sizeDA); // TODO: Verify capacity is 0 index and this is valid
	if (items->startIndex + index > items->sizeDA)
		index = (index + items->startIndex) - items->sizeDA;
	return items->data[index];
}

// Inserts a value at the index, corrected for index start
void insertCDA(CDA *items, int index, void *value)
{
	assert(index <= items->sizeDA && index > -1);
	if (items->sizeDA == items->capacity)
		doubleCDAStorage(items);
	void *holder = NULL;
	void *prevValue = value;
	// Shift values
	for (int i = index + items->startIndex; i <= items->sizeDA + items->startIndex; i++)
	{
		holder = items->data[i % items->capacity];
		items->data[i % items->capacity] = prevValue;
		prevValue = holder;
	}
	items->sizeDA++;
}

// Removes data at index, corrected for index start
void *removeCDA(CDA *items, int index)
{
	assert(index < items->sizeDA && index > -1);
	void *returnVal = items->data[index];
	for (int i = index; i < items->sizeDA-1; i++)
	{
		items->data[i%items->capacity] = items->data[(i+1) % items->capacity];
	}
	items->sizeDA-=1;
	while (((float)(items->sizeDA / (float)items->capacity) < 0.25f && items->capacity > 1) )
		halfCDAStorage(items);
	return returnVal;
}

// Returns the size of the given CDA
int sizeCDA(CDA *items)
{
	return items->sizeDA;
}

// Combines the donor into the recipient
void unionCDA(CDA *recipient, CDA *donor)
{
	while (recipient->capacity < recipient->sizeDA + donor->sizeDA)
		doubleCDAStorage(recipient);
	int donorSize = donor->sizeDA;
	for (int i = 0; i < donorSize; i++) //TODO: MAKE THIS RUN IN THE RIGHT TIME YOU FUCK
	{
		recipient->data[(recipient->sizeDA + i) % recipient->capacity] = donor->data[(donor->startIndex + i) % donor->capacity];
	}
	recipient->sizeDA += donor->sizeDA;
	donor->sizeDA = 0;
	donor->capacity = 1;
	donor->data = malloc(sizeof(void*));
}

// Uses the stored display method to display the data
void displayCDA(CDA *items, FILE *fp)
{
	fprintf(fp, "(");
	for (int i = items->startIndex; i < items->sizeDA; i++)
	{
		if (i != items->startIndex)
			fprintf(fp, ",");
		if (items->displayMethod == NULL)
			fprintf(fp, "@%p", items->data[i%items->capacity]);
		else
			items->displayMethod(items->data[i%items->capacity], fp);
	}
	if (items->debugFlag > 0)
	{
		if(items->sizeDA > 0)
			fprintf(fp, ",(%d)", items->capacity - items->sizeDA);
		else
			fprintf(fp, "(%d)", items->capacity - items->sizeDA);
	}
	fprintf(fp, ")");
}

// Just returns the current capacity
int capacityCDA(CDA *items)
{
	return items->capacity;
}

// Made for refrencing values from the queue
int startIndexCDA(CDA *items)
{
	return items->startIndex;
}

// Outputs the stored values followed by the number of unfilled slots
int debugCDA(CDA *items,int level)
{
	int prevVal = items->debugFlag;
	items->debugFlag = level;
	return prevVal;
}

void freeCDA(CDA *items)
{
	if (items->freeMethod != NULL)
	{
		for (int i = 0; i < items->sizeDA; i++)
		{
			items->freeMethod(items->data[(items->startIndex + i) % items->capacity]);
		}
		free(items->data);
		items->freeMethod(items);
	}
}

// Replaces the value or if == size makes a new one
void *setCDA(CDA *items, int index, void* value )
{
	assert(index >= -1 && index <= items->capacity);
	if (items->sizeDA == index)
	{
		insertCDA(items, index, value);
		return NULL;
	}
	else if (index == -1)
	{
		insertCDAfront(items, value);
		return NULL;
	}
	else if (index > items->sizeDA)
		return NULL; // TODO: Nullptr I tihnk?
	else
		items->data[index] = value;
	return items->data[index];
}
