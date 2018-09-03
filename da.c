/*
Dynamic Array Implementation File
The purpose of this file is to implement the outlined functions and such
included in the respective header file.

File author: Connor Adams
*/

#include "da.h"

struct da
{
  // Components
  void **data;
  int capacity, sizeDA, debugFlag; // Capacity == Total size, size == used size
  void (*displayMethod)(void *,FILE *);
  void (*freeMethod)(void *);
};

// This function is just going to double the size of a dynamic array
void doubleStorage(DA *items)
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
void halfStorage(DA *items)
{
  items->capacity /= 2;
  items->data = (void**)realloc(items->data, sizeof(void*) * items->capacity);
}

// The constructor that returns the newly initalized DA
DA *newDA(void)
{
  DA *newDA;
  newDA = (DA *) malloc(sizeof(DA));
  newDA->data = NULL;
  newDA->displayMethod = NULL;
  newDA->capacity = 1;
  newDA->sizeDA = 0;
  newDA->debugFlag = 0;
  doubleStorage(newDA);
  return newDA;
}

// Inserts an element at the given index to the given DA and double if needed
void insertDA(DA *items,int index,void *value)
{
  assert(index > -1 && index <= items->capacity);
  if (index == items->capacity || items->sizeDA == items->capacity)
    doubleStorage(items);
  if (index < items->sizeDA)
  {
    void *holder, *prevValue;
    prevValue = items->data[index];
    items->data[index] = value;
    for (int i = index+1; i <= items->sizeDA; i++)
    {
      holder = items->data[i];
      items->data[i] = prevValue;
      prevValue = holder;
    }
  }
  else
  {
    items->data[index] = value;
  }
  items->sizeDA++;
}

// This function will remove a given value and return it, also shift values if needed
void *removeDA(DA *items,int index)
{
  assert(index < items->sizeDA);
  void* removedVal = items->data[index];
  items->sizeDA -= 1;
  for (int i = 0; i < items->sizeDA; i++)
  {
    items->data[i] = items->data[i+1];
  }
  if ((float)(items->sizeDA/items->capacity) <= 0.25f && items->capacity > 1)
    halfStorage(items);
  return removedVal;
}

// Returns the number of items in use
int sizeDA(DA *items)
{
  return items->sizeDA;
}

// Stores the diplay method in the DA
void setDAdisplay(DA *items,void (*dpMethod)(void *dpMethod,FILE *))
{
  items->displayMethod = dpMethod;
}

// Uses the free method on an index
void freeDA(DA *items)
{
  if (items->freeMethod == NULL)
    return;
  for(int i = 0; i < items->capacity; i++)
  {
    items->freeMethod(items->data[i]);
  }
}

// The function displays held data based on output method
void displayDA(DA *items, FILE *fp)
{
  fprintf(fp, "[");
  for (int i = 0; i < items->sizeDA; i++)
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

// Gets the data at a given slot, provided index is valid
void *getDA(DA *items, int index)
{
  assert(index >= 0 && index < items->capacity);
  return items->data[index];
}

// Passed a function that knows how to free a generic datatype
void setDAfree(DA *items,void (*freeMethod)(void *))
{
  for (int i = 0; i < items->capacity; i++)
  {
    freeMethod(items->data[i]);
  }
  items->freeMethod = freeMethod;
}

// Outputs the stored values followed by the number of unfilled slots
int debugDA(DA *items,int level)
{
  items->debugFlag = level;
  return items->capacity - items->sizeDA;
}

// Replaces the value or if == size makes a new one
void *setDA(DA *items, int index, void* value )
{
  if (items->sizeDA == index)
    insertDA(items, index, value);
  else if (index > items->sizeDA)
    return NULL; // TODO: Nullptr I tihnk?
  else
    items->data[index] = value;
  return items->data[index];
}

// Moves the data from donor to recipient
void unionDA(DA *recipient, DA *donor)
{
  while (recipient->capacity < (recipient->sizeDA + donor->sizeDA)) // TODO: Veify This
    doubleStorage(recipient);
  int maxSize = recipient->sizeDA + donor->sizeDA;
  for (int i = 0; recipient->sizeDA < maxSize; i++, recipient->sizeDA++)
    recipient->data[recipient->sizeDA] = donor->data[i];
  free(donor);
}
