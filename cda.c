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
void doubleCDAStorage(CDA *items)
{
  items->capacity *= 2;
  items->data = (void**)realloc(items->data, sizeof(void*) * items->capacity);
}

// Function made for halving storage size for the remove function
void halfCDAStorage(CDA *items)
{
  items->capacity /= 2;
  items->data = (void**)realloc(items->data, sizeof(void*) * items->capacity);
}

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

void setCDAdisplay(CDA *items, void (*displayInput)(void *,FILE *) )
{
  items->displayMethod = displayInput;
}

void setCDAfree(CDA *items, void (*freeInput)(void *))
{
  items->freeMethod = freeInput;
}

void *getCDA(CDA *items, int index)
{
  assert(index >= 0 && index < items->sizeDA); // TODO: Verify capacity is 0 index and this is valid
  if (items->startIndex + index > items->sizeDA)
    index = (index + items->startIndex) - items->sizeDA;
  return items->data[index];
}

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

void *removeCDA(CDA *items, int index)
{
  assert(index < items->sizeDA && index > -1);
  void *returnVal = items->data[index];
  for (int i = index; i < items->sizeDA-1; i++)
  {
    items->data[i] = items ->data[i+1];
  }
  items->sizeDA-=1;
  if ((float)(items->sizeDA / items->capacity) <= 0.25f)
    halfCDAStorage(items);
  return returnVal;
}

int sizeCDA(CDA *items)
{
  return items->sizeDA;
}

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

void displayCDA(CDA *items, FILE *fp) // TODO: MAKE CORRECTIONS FOR NON-0 INDEX
{
  fprintf(fp, "[");
  for (int i = items->startIndex; i < items->sizeDA; i++)
  {
    if (i > 0)
      fprintf(fp, ",");
    if (items->displayMethod == NULL)
      fprintf(fp, "@%p", items->data[i]);
    else
      items->displayMethod(items->data[i], fp);
  }
  fprintf(fp, "]");
}

// Outputs the stored values followed by the number of unfilled slots
int debugCDA(CDA *items,int level)
{
  items->debugFlag = level;
  return items->capacity - items->sizeDA;
}

void freeCDA(CDA *items)
{
  if (items->freeMethod != NULL)
  {
    for (int i = 0; i < items->sizeDA; i++)
    {
      items->freeMethod(items->data[(items->startIndex+i)%items->capacity]);
    }
  }
}

/*
void insertCDAfront(CDA *items, void *value)
{
  if (items->startIndex == 0)
    items->startIndex = items->capacity -1;
  else
    items-> startIndex -= 1;
  items->data[items->startIndex] = value;
}*/

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
