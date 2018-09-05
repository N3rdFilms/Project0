all:
	gcc integer.c testFile.c da.c cda.c stack.c queue.c -Wall -o testRun -Wextra
valgrind: testRun
	valgrind ./testRun
