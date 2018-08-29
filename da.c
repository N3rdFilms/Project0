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
  int sizeOfData;
  // Pointers to functions

};

// This function is just going to double the size of a dynamic array
void doubleStorage(DA *dynamicArr)
{
  if (dynamicArr->data == NULL)
  {
    dynamicArr->data = (void**)malloc(sizeof(void*) * dynamicArr->sizeOfData);
    for (int i = 0; i < dynamicArr->sizeOfData; i++)
    {
      printf("%d\n", i);
      dynamicArr->data[i] = NULL;
    }
    return;
  }
  void **holderArr = (void**)malloc(sizeof(void*) * dynamicArr->sizeOfData);
  for (int i = 0; i < dynamicArr->sizeOfData; i++)
  {
    holderArr[i] = dynamicArr->data[i];
  }
  free(dynamicArr->data);
  dynamicArr->sizeOfData *=2;
  dynamicArr->data = (void**)malloc(sizeof(void*) * dynamicArr->sizeOfData);
  for (int i = 0; i < dynamicArr->sizeOfData; i++)
  {
    printf("%d\n", i);
    if (i < dynamicArr->sizeOfData/2)
      dynamicArr->data[i] = holderArr[i];
    else
      dynamicArr->data[i] = NULL;
  }
  free(holderArr);
}

// The constructor that returns the newly initalized DA
DA *newDA(void)
{
  DA *newDA;
  newDA = (DA *) malloc(sizeof(DA));
  newDA->data = NULL;
  newDA->sizeOfData = 1;
  doubleStorage(newDA);
  return newDA;
}

// Inserts an element at the given index to the given DA
void insertDA(DA *items,int index,void *value)
{
  if (items->sizeOfData > index)
  {
    if (items->data[index] == NULL)
    {
      items->data[index] = value;
    }
    else
    {
      void* shiftVal = items->data[index];
      void* holder = NULL;
      items->data[index] = value;
      for (int i = index+1; i < items->sizeOfData; i++)
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
      int prevSize = items->sizeOfData;
      doubleStorage(items); // At this point the loop as run and the rest is full
      items->data[prevSize] = shiftVal;
      free(shiftVal);
      free(holder);
    }
  }
  else
  {
    while(index > items->sizeOfData -1)
    {
      doubleStorage(items);
    }
    items->data[index] = value;
  }
}

// Returns the number of items in use
int sizeDA(DA *items)
{
  int numFilled = 0;
  for (int i = 0; i < items->sizeOfData; i++)
  {
    if (items->data[i] != NULL)
      numFilled++;
  }
  return numFilled;
}

void displayDA(DA *items, FILE *fp)
{
  fprintf(fp, "[");
  for (int i = 0; i < items->sizeOfData; i++)
  {
    if (i > 0)
      fprintf(fp, ",");
    fprintf(fp, "@%p", items->data[i]);
  }
  fprintf(fp, "]\n");
}
