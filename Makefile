CC = gcc

example:example.c lite-queue.c
	$(CC) $^ -o $@ -I. -Wall -lpthread


.PHONY:clean
clean:
	rm exmaple 
