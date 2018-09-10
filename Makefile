all:
	gcc integer.c testFile.c da.c cda.c stack.c queue.c -Wall -o testRun -Wextra
valgrind: testRun
	valgrind ./testRun
test: 
	gcc integer.c testFile.c da.c cda.c stack.c queue.c -Wall -o testRun -Wextra
	./testRun
clean: 
	-rm *.o $(objects) *.exe