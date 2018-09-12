all:
	gcc integer.c testFile.c da.c cda.c stack.c queue.c -Wall -o project0 -Wextra
valgrind: testRun
	valgrind ./project0
test: 
	gcc integer.c testFile.c da.c cda.c stack.c queue.c -Wall -o testRun -Wextra
	./testRun
clean: 
	-rm *.o $(objects) *.exe