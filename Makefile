OBJS = da.o cda.o stack.o queue.o integer.o testFile.o
OOPTS = -Wall -Wextra -g -c
LOPTS = -Wall -Wextra -g

all : test-project0

test-project0 : $(OBJS)
	gcc $(LOPTS) $(OBJS) -o test-project0

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

testFile.o :	testFile.c da.h cda.h integer.h queue.h
	gcc $(OOPTS) testFile.c

test : test-project0
	./test-project0

valgrind : test-project0
	valgrind test-project0

clean	:
	rm -f $(OBJS) test-project0
