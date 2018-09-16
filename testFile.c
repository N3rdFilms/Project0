#include <stdio.h>
#include <stdlib.h>
#include "da.h"
#include "cda.h"
#include "stack.h"
#include "queue.h"
#include "integer.h"


struct stack
{
	DA *dynamicArr;
	void(*displayMethod)(void *, FILE *);
	void(*freeMethod)(void *);
	int debugFlag;
};

struct queue
{
	CDA *cda;
	void(*displayMethod)(void *, FILE *);
	void(*freeMethod)(void *);
	int debugFlag;
};


void daTester()
{
	int someNum = 100;
	DA *testDA = newDA();
	setDAdisplay(testDA, displayINTEGER);
	displayDA(testDA, stdout);
	printf("\n");
	debugDA(testDA, 1);
	displayDA(testDA, stdout);
	for (int i = 0; i < someNum; i++)
	{
		insertDA(testDA, 0, newINTEGER(rand() % 100));
	}
	printf("\n");
	displayDA(testDA, stdout);
	printf("\nThere are currently %d elements in the DA\n", sizeDA(testDA));
	for (int i = someNum; i > 0; i--)
	{
		removeDA(testDA, rand() % i);
		if (i % 500 == 0)
			displayDA(testDA, stdout);
	}
	printf("\nThere are now %d elements\n\n", sizeDA(testDA));
	displayDA(testDA, stdout);
	debugDA(testDA, 2);
	displayDA(testDA, stdout);
	debugDA(testDA, 3);
	displayDA(testDA, stdout);
	freeDA(testDA);
	testDA = newDA();
	DA *donorDA = newDA();
	for (int i = 0; i < someNum; i++)
	{
		insertDA(testDA, 0, newINTEGER(rand() % 100));
	}
	for (int i = 0; i < someNum; i++)
	{
		insertDA(donorDA, 0, newINTEGER(rand() % 100));
	}
	setDAdisplay(testDA, displayINTEGER);
	displayDA(testDA, stdout);
	printf("\n");
	setDAdisplay(donorDA, displayINTEGER);
	displayDA(donorDA, stdout);
	printf("\n");
	unionDA(testDA, donorDA);
	displayDA(testDA, stdout);
	printf("\n");
	printf("\nThere are currently %d elements in the DA\n", sizeDA(testDA));
	for (int i = someNum; i > 0; i--)
	{
		removeDA(testDA, rand() % i);
		if (i % 500 == 0)
			displayDA(testDA, stdout);
	}
	freeDA(testDA);
	freeDA(donorDA);
}

void stackTester()
{
	int someNum = 100;
	STACK *testSTACK = newSTACK();
	setSTACKdisplay(testSTACK, displayINTEGER);
	displaySTACK(testSTACK, stdout);
	printf("\n");
	debugSTACK(testSTACK, 0);
	displaySTACK(testSTACK, stdout);
	for (int i = 0; i < someNum; i++)
	{
		push(testSTACK, newINTEGER(rand() % 100));
	}
	printf("\n");
	displaySTACK(testSTACK, stdout);
	printf("\nThere are currently %d elements in the STACK\n", sizeSTACK(testSTACK));
	for (int i = someNum; i > 0; i--)
	{
		pop(testSTACK);
		if (i % 500 == 0)
			displaySTACK(testSTACK, stdout);
	}
	printf("\nThere are now %d elements\n\n", sizeSTACK(testSTACK));
	displaySTACK(testSTACK, stdout);
	debugSTACK(testSTACK, 1);
	displaySTACK(testSTACK, stdout);
	debugSTACK(testSTACK, 2);
	displaySTACK(testSTACK, stdout);
	STACK *donorStack = newSTACK();
	setSTACKdisplay(donorStack, displayINTEGER);
	displaySTACK(donorStack, stdout);
	printf("\n");
	for (int i = 0; i < someNum; i++)
	{
		push(donorStack, newINTEGER(rand() % 100));
	}
	printf("\n");
	displaySTACK(donorStack, stdout);
	unionDA(testSTACK->dynamicArr, donorStack->dynamicArr);
	printf("\n");
	displaySTACK(testSTACK, stdout);
	for (int i = 0; i < someNum; i++)
	{
		push(testSTACK, newINTEGER(rand() % 100));
	}
	for (int i = 0; i < someNum; i++)
	{
		push(donorStack, newINTEGER(rand() % 100));
	}
	printf("\n");
	displaySTACK(donorStack, stdout);
	freeSTACK(testSTACK);
	freeSTACK(donorStack);
}

void cdaTester()
{
	int someNum = 100;
	CDA *testCDA = newCDA();
	setCDAdisplay(testCDA, displayINTEGER);
	displayCDA(testCDA, stdout);
	printf("\n");
	debugCDA(testCDA, 1);
	displayCDA(testCDA, stdout);
	for (int i = 0; i < someNum; i++)
	{
		insertCDA(testCDA, 0, newINTEGER(rand() % 100));
	}
	printf("\n");
	displayCDA(testCDA, stdout);
	printf("\nThere are currently %d elements in the CDA\n", sizeCDA(testCDA));
	for (int i = someNum; i > 0; i--)
	{
		removeCDA(testCDA, rand() % i);
		if (i % 500 == 0)
			displayCDA(testCDA, stdout);
	}
	printf("\nThere are now %d elements\n\n", sizeCDA(testCDA));
	displayCDA(testCDA, stdout);
	debugCDA(testCDA, 1);
	displayCDA(testCDA, stdout);
	debugCDA(testCDA, 2);
	displayCDA(testCDA, stdout);
	CDA *donorCDA = newCDA();
	setCDAdisplay(donorCDA, displayINTEGER);
	displayCDA(donorCDA, stdout);
	printf("\n");
	for (int i = 0; i < someNum; i++)
	{
		insertCDA(donorCDA, 0, newINTEGER(rand() % 100));
	}
	for (int i = 0; i < someNum; i++)
	{
		insertCDA(testCDA, 0, newINTEGER(rand() % 100));
	}
	displayCDA(testCDA, stdout);
	unionCDA(testCDA, donorCDA);
	printf("\nUnion size is: %d\n", sizeCDA(testCDA));
	displayCDA(testCDA, stdout);
	printf("\n");
	freeCDA(testCDA);
	freeCDA(donorCDA);

}

void queueTester()
{
	int someNum = 100;
	QUEUE *testQUEUE = newQUEUE();
	setQUEUEdisplay(testQUEUE, displayINTEGER);
	displayQUEUE(testQUEUE, stdout);
	printf("\n");
	debugQUEUE(testQUEUE, 0);
	displayQUEUE(testQUEUE, stdout);
	for (int i = 0; i < someNum; i++)
	{
		enqueue(testQUEUE, newINTEGER(rand() % 100));
	}
	printf("\n");
	displayQUEUE(testQUEUE, stdout);
	printf("\nThere are currently %d elements in the QUEUE\n", sizeQUEUE(testQUEUE));
	for (int i = someNum; i > 0; i--)
	{
		dequeue(testQUEUE);
		if (i % 500 == 0)
			displayQUEUE(testQUEUE, stdout);
	}
	printf("\nThere are now %d elements\n\n", sizeQUEUE(testQUEUE));
	displayQUEUE(testQUEUE, stdout);
	debugQUEUE(testQUEUE, 1);
	displayQUEUE(testQUEUE, stdout);
	debugQUEUE(testQUEUE, 2);
	displayQUEUE(testQUEUE, stdout);

	QUEUE *donorQUEUE = newQUEUE();
	setQUEUEdisplay(donorQUEUE, displayINTEGER);
	displayQUEUE(donorQUEUE, stdout);
	printf("\n");
	for (int i = 0; i < someNum; i++)
	{
		enqueue(donorQUEUE, newINTEGER(rand() % 100));
	}
	for (int i = 0; i < someNum; i++)
	{
		enqueue(testQUEUE, newINTEGER(rand() % 100));
	}
	displayQUEUE(testQUEUE, stdout);
	unionCDA(testQUEUE->cda, donorQUEUE->cda);
	printf("\nUnion size is: %d\n", sizeQUEUE(testQUEUE));
	displayQUEUE(testQUEUE, stdout);
	printf("\n");
	freeQUEUE(testQUEUE);
	freeQUEUE(donorQUEUE);


	freeQUEUE(testQUEUE);
	freeQUEUE(donorQUEUE);

}

void attemptToBreakCDA()
{
	CDA *testCDA = newCDA();
	for (int i = 0; i < 10; i++)
	{
		insertCDA(testCDA, 0, newINTEGER(rand() % 100));
	}
	setCDAdisplay(testCDA, displayINTEGER);
	displayCDA(testCDA, stdout);
	printf("\n");
	for (int i = 0; i < 10; i++)
	{
		insertCDAback(testCDA, newINTEGER(rand() % 100));
		insertCDAfront(testCDA, newINTEGER(rand() % 100));
	}
	displayCDA(testCDA, stdout);
	printf("\n");
	removeCDAfront(testCDA);
	setCDA(testCDA, -1, newINTEGER(99999));
	displayCDA(testCDA, stdout);

	freeCDA(testCDA);
}

int main(void)
{
	printf("Going to test the DA lib\n\n\n");
	daTester();
	printf("\nGoing to test the STACK lib\n\n\n");
	stackTester();
	printf("\nGoing to test the CDA lib\n\n\n");
	cdaTester();
	printf("\nGoing to test the QUEUE lib\n\n\n");
	queueTester();
	printf("\nNow, time to try and break the CDA\n\n\n");
	attemptToBreakCDA();
	return 0;
}
