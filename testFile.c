// I need to remember to delete this, I am just testing stuff
/*
#include "da.h"

int main(void)
{
  DA *someDa = newDA();
  insertDA(someDa, 0, (void*)7);
  displayDA(someDa, stdout);
  insertDA(someDa, 2, (void*)15);
  displayDA(someDa, stdout);
  return 0;
}
*/
#include <stdio.h>
#include <stdlib.h>
#include "integer.h"
#include "da.h"
#include "cda.h"

static void showItems(DA *items);
static void showCDAItems(CDA *items);

int
main(void)
{
  srandom(1);
  DA *items = newDA();
  DA *secondItems = newDA();
  setDAfree(items,freeINTEGER);
  showItems(items);
  insertDA(items,0,newINTEGER(3));                 //insert at front
  insertDA(items,sizeDA(items),newINTEGER(2));     //insert at back
  insertDA(items,1,newINTEGER(1));                 //insert at middle
  showItems(items);
  insertDA(secondItems, 0,newINTEGER(8));
  insertDA(secondItems, 0,newINTEGER(3));
  printf("Going to show second items\n");
  showItems(secondItems);
  unionDA(items, secondItems);
  printf("Union the two, output now\n");
  showItems(items);
  printf("The value ");
  INTEGER *i = removeDA(items,0);                  //remove from front
  displayINTEGER(i,stdout);
  printf(" was removed.\n");
  freeINTEGER(i);
  showItems(items);
  int x = getINTEGER((INTEGER *) getDA(items,0));  //get the first item
  printf("The first item is %d.\n",x);
  printf("Freeing the list.\n");
  freeDA(items);

printf("END OF DA TESTING\nSTART OF CDA TESTING\n\n");

  CDA *cdaItems = newCDA();
  CDA *secondcdaItems = newCDA();
  setCDAfree(cdaItems,freeINTEGER);
  showCDAItems(cdaItems);
  insertCDA(cdaItems,0,newINTEGER(3));                 //insert at front
  insertCDA(cdaItems,sizeCDA(cdaItems),newINTEGER(2));     //insert at back
  insertCDA(cdaItems,1,newINTEGER(1));                 //insert at middle
  showCDAItems(cdaItems);
  insertCDA(secondcdaItems, 0,newINTEGER(8));
  insertCDA(secondcdaItems, 0,newINTEGER(3));
  printf("Going to show second items\n");
  showCDAItems(secondcdaItems);
  unionCDA(cdaItems, secondcdaItems);
  printf("Union the two, output now\n");
  showCDAItems(cdaItems);
  printf("The value ");
  INTEGER *j = removeCDA(cdaItems,0);                  //remove from front
  displayINTEGER(j,stdout);
  printf(" was removed.\n");
  freeINTEGER(j);
  showCDAItems(cdaItems);
  int y = getINTEGER((INTEGER *) getCDA(cdaItems,0));  //get the first item
  printf("The first item is %d.\n",y);
  printf("Freeing the list.\n");
  freeCDA(cdaItems);
  return 0;
}

static void
showItems(DA *items)
{
  int old;
  setDAdisplay(items,displayINTEGER);
  printf("The items are ");
  displayDA(items,stdout);
  printf(".\n");
  printf("The items (debugged) are ");
  old = debugDA(items,1);
  setDAdisplay(items,0);
  displayDA(items,stdout);
  printf(".\n");
  debugDA(items,old);
}

static void
showCDAItems(CDA *items)
{
  int old;
  setCDAdisplay(items,displayINTEGER);
  printf("The items are ");
  displayCDA(items,stdout);
  printf(".\n");
  printf("The items (debugged) are ");
  old = debugCDA(items,1);
  setCDAdisplay(items,0);
  displayCDA(items,stdout);
  printf(".\n");
  debugCDA(items,old);
}
