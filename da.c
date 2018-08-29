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
  int capacity, sizeDA; // Capacity == Total size, size == used size
  void (*displayMethod)(void *,FILE *);
  void (*freeMethod)(void *);
};

// This function is just going to double the size of a dynamic array
void doubleStorage(DA *dynamicArr)
{
  if (dynamicArr->data == NULL)
  {
    dynamicArr->data = (void**)malloc(sizeof(void*) * dynamicArr->capacity);
    for (int i = 0; i < dynamicArr->capacity; i++)
    {
      dynamicArr->data[i] = NULL;
    }
    return;
  }
  dynamicArr->capacity *= 2;
  dynamicArr->data = (void**)realloc(dynamicArr->data, sizeof(void*) * dynamicArr->capacity);
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
  doubleStorage(newDA);
  return newDA;
}

<<<<<<< HEAD
// Inserts value at items index, if it isn't valid then double size
=======
// Inserts an element at the given index to the given DA
>>>>>>> 8cd9f71fc4880d221d4f72a865a5ed9827ff4f4e
void insertDA(DA *items,int index,void *value)
{
  assert(index > 0 && index <= items->capacity);
  /*if (items->capacity > index)
  {
    if (items->data[index] == NULL) // TODO: Fix this to not be null
    {
      items->data[index] = value;
    }
    else
    {
      void* shiftVal = items->data[index];
      void* holder = NULL;
      items->data[index] = value;
      for (int i = index+1; i < items->capacity; i++)
      {
        if (items->data[i] != NULL)
        {
          holder = items->data[i];
          items->data[i] = shiftVal;
          shiftVal = holder;
        }
        else
        {
          items->data[i] = shiftVal;
          free(shiftVal);
          free(holder);
          return;
        }
      }
      int prevSize = items->capacity;
      doubleStorage(items); // At this point the loop as run and the rest is full
      items->data[prevSize] = shiftVal;
      free(shiftVal);
      free(holder);
    }
  }
  else
  {
    while(index > items->capacity -1)
    {
      doubleStorage(items);
    }
    items->data[index] = value;
  }*/
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
    doubleStorage(items);
  }
  items->sizeDA++;
}

// Returns the number of items in use
int sizeDA(DA *items)
{
  return items->sizeDA;
}

void setDAdisplay(DA *items,void (*dpMethod)(void *dpMethod,FILE *))
{
  items->displayMethod = dpMethod;
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
  assert(index > 0 && index < items->capacity);
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
  return items->sizeDA;
}
