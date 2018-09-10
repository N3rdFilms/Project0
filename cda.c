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
void doubleCDAStorage(CDA *items) //TODO: FIC THE REALLOC ERROR: WILL NOT SHIFT AS NEEDED!!
{
	void **holder = (void**)malloc(sizeof(void*) * items->capacity * 2);
	for (int i = items->startIndex; i < items->sizeDA; i++)
	{
		holder[i % (items->capacity * 2)] = items->data[i % (items->capacity)];
	}
	items->capacity *= 2;
	items->data = (void**)malloc(sizeof(void*) * items->capacity);
	for (int i = items->startIndex; i < items->sizeDA; i++)
	{
		items->data[i % (items->capacity)] = holder[i % (items->capacity)];
	}
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
  newCDA->displayMethod = NULL;
  newCDA->capacity = 1;
  newCDA->sizeDA = 0;
  newCDA->debugFlag = 0;
  newCDA->startIndex = 0;
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
  void *holder;
  void *prevValue = value;
  // Shift values
  for (int i = index + items->startIndex; i <= items->sizeDA + items->startIndex; i++)
  {
    holder = items->data[i];
    items->data[i] = prevValue;
    prevValue = holder;
  }
  items->sizeDA++;
}

// Removes data at index, corrected for index start
void *removeCDA(CDA *items, int index) // TODO: Make this correct for index
{
  assert(index < items->sizeDA && index > -1);
  void *returnVal = items->data[index];
  for (int i = index; i < items->sizeDA-1; i++)
  {
    items->data[i] = items ->data[i+1];
  }
  items->sizeDA-=1;
  if (((float)(items->sizeDA / (float)items->capacity) < 0.25f && items->capacity > 1) || (items->sizeDA == 0 && items->capacity > 1))
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
  while (recipient->capacity < recipient->sizeDA + recipient->sizeDA)
    doubleCDAStorage(recipient);
  for (int i = 0; i < donor->sizeDA; i++)
  {
    recipient->data[(recipient->startIndex + recipient->sizeDA)%recipient->capacity] = donor->data[i];
    recipient->sizeDA++;
  }
}

// Uses the stored display method to display the data
void displayCDA(CDA *items, FILE *fp) // TODO: MAKE CORRECTIONS FOR NON-0 INDEX
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
	for (int i = 0; i < items->sizeDA; i++)
		{
			items->freeMethod(items->data[(items->startIndex+i)%items->capacity]);
		}
}

// Replaces the value or if == size makes a new one
void *setCDA(CDA *items, int index, void* value )
{
	if (items->sizeDA == index)
	insertCDA(items, index, value);
	else if (index == -1)
	insertCDAfront(items, value);
	else if (index > items->sizeDA)
	return NULL; // TODO: Nullptr I tihnk?
	else
	items->data[index] = value;
	return items->data[index];
}
