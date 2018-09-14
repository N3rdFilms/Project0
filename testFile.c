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
	int someNum = 5000;
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

}

void stackTester()
{
	int someNum = 5000;
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
	freeSTACK(testSTACK);

}

void cdaTester()
{
	int someNum = 5000;
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
	freeCDA(testCDA);

}

void queueTester()
{
	int someNum = 5000;
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
	freeQUEUE(testQUEUE);

}

int main(void)
{
	printf("Going to test the DA lib\n");
	daTester();
	printf("\nGoing to test the STACK lib\n");
	stackTester();
	printf("\nGoing to test the CDA lib\n");
	cdaTester();
	printf("\nGoing to test the QUEUE lib\n");
	queueTester();
	return 0;
}
