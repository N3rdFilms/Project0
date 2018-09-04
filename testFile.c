#include <stdio.h>
#include <stdlib.h>
#include "integer.h"
#include "da.h"
#include "cda.h"
#include "stack.h"
#include "queue.h"

static void showItems(DA *items);
static void showCDAItems(CDA *items);
static void showSTACKItems(STACK *items);
static void showQUEUEItems(QUEUE *items);

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

	printf("\nEND OF DA TESTING\nSTART OF CDA TESTING\n\n");

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

	printf("\nEND OF CDA TESTING\nSTART OF STACK TESTING\n\n");

	STACK *stackItems = newSTACK();
	STACK *secondstackItems = newSTACK();
	setSTACKfree(stackItems,freeINTEGER);
	showSTACKItems(stackItems);
	push(stackItems,newINTEGER(3));
	push(stackItems,newINTEGER(2));
	push(stackItems,newINTEGER(1));
	showSTACKItems(stackItems);
	printf("Peek value: %p\n", peekSTACK(stackItems));
	push(secondstackItems,newINTEGER(8));
	push(secondstackItems,newINTEGER(3));
	printf("Going to show second items\n");
	showSTACKItems(secondstackItems);
	printf("The value ");
	//printf("%p", pop(stackItems));
	INTEGER *k = pop(stackItems);
	displayINTEGER(k,stdout);
	printf(" was removed.\n");
	freeINTEGER(k);
	showSTACKItems(stackItems);
	int z = getINTEGER((INTEGER *) pop(stackItems));
	printf("The last item pop-able is %d.\n",z);
	printf("Freeing the list.\n");
	freeSTACK(stackItems); //TODO: BROKEN HERE

	printf("\nEND OF STACK TESTING\nSTART OF QUEUE TESTING\n\n");

	QUEUE *queueItems = newQUEUE();
	QUEUE *secondqueueItems = newQUEUE();
	setQUEUEfree(queueItems, freeINTEGER);
	showQUEUEItems(queueItems);
	enqueue(queueItems, newINTEGER(3));
	enqueue(queueItems, newINTEGER(2));
	enqueue(queueItems, newINTEGER(1));
	showQUEUEItems(queueItems);
	printf("Peek value: %p\n", peekQUEUE(queueItems));
	enqueue(secondqueueItems, newINTEGER(8));
	enqueue(secondqueueItems, newINTEGER(3));
	printf("Going to show second items\n");
	showQUEUEItems(secondqueueItems);
	printf("The value ");
	//printf("%p", dequeue(queueItems));
	INTEGER *l = dequeue(queueItems);
	displayINTEGER(l, stdout);
	printf(" was removed.\n");
	freeINTEGER(l);
	showQUEUEItems(queueItems);
	int zz = getINTEGER((INTEGER *)dequeue(queueItems));
	printf("The last item pop-able is %d.\n", zz);
	printf("Freeing the list.\n");
	freeQUEUE(queueItems);

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

static void
showSTACKItems(STACK *items)
{
  int old;
  setSTACKdisplay(items,displayINTEGER);
  printf("The items are ");
  displaySTACK(items,stdout);
  printf(".\n");
  printf("The items (debugged) are ");
  old = debugSTACK(items,1);
  setSTACKdisplay(items,0);
  displaySTACK(items,stdout);
  printf(".\n");
  debugSTACK(items,old);
}

static void
showQUEUEItems(QUEUE *items)
{
	int old;
	setQUEUEdisplay(items, displayINTEGER);
	printf("The items are ");
	displayQUEUE(items, stdout);
	printf(".\n");
	printf("The items (debugged) are ");
	old = debugQUEUE(items, 1);
	setQUEUEdisplay(items, 0);
	displayQUEUE(items, stdout);
	printf(".\n");
	debugQUEUE(items, old);
}
