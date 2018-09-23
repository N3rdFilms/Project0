OBJS = da.o cda.o stack.o queue.o integer.o testFile.o real.o string.o
OOPTS = -Wall -Wextra -g -std=c99 -c 
LOPTS = -Wall -Wextra -g 

all : project0

project0 : $(OBJS)
	gcc $(LOPTS) $(OBJS) -o project0

da.o : da.c da.h
	gcc $(OOPTS) da.c

cda.o : cda.c cda.h
	gcc $(OOPTS) cda.c

stack.o : stack.c stack.h
	gcc $(OOPTS) stack.c

queue.o : queue.c queue.h
	gcc $(OOPTS) queue.c

integer.o : integer.c integer.h
	gcc $(OOPTS) integer.c

real.o : real.c real.h
	gcc $(OOPTS) real.c

string.o : string.c string.h
	gcc $(OOPTS) string.c

testFile.o :	testFile.c da.h cda.h integer.h queue.h
	gcc $(OOPTS) testFile.c

test : project0
	./project0

valgrind : project0
	valgrind project0

clean	:
	rm -f $(OBJS) project0
