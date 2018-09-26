OBJS = da.o cda.o stack.o queue.o integer.o testFile.o real.o string.o
OOPTS = -Wall -Wextra -g -std=c99 -c 
LOPTS = -Wall -Wextra -g 

all : project0

project0 : $(OBJS)
	gcc $(LOPTS) $(OBJS) -o project0

da.o : da.h da.c
	gcc $(OOPTS) da.c

cda.o : cda.h cda.c
	gcc $(OOPTS) cda.c

stack.o : stack.h stack.c
	gcc $(OOPTS) stack.c

queue.o : queue.h queue.c
	gcc $(OOPTS) queue.c

integer.o : integer.h integer.c
	gcc $(OOPTS) integer.c

real.o : real.h real.c
	gcc $(OOPTS) real.c

string.o : string.h string.c
	gcc $(OOPTS) string.c

testFile.o : testFile.c da.h cda.h integer.h queue.h
	gcc $(OOPTS) testFile.c

test : project0
	./project0

valgrind : project0
	valgrind project0

clean:
	rm -f $(OBJS) project0
