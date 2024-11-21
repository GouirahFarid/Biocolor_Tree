CC = gcc
CFLAGS = -Wall -g
TARGET = rb_avl_trees
OBJS = rbtree.o avltree.o main.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

rbtree.o: rbtree.c rbtree.h
	$(CC) $(CFLAGS) -c rbtree.c

avltree.o: avltree.c avltree.h
	$(CC) $(CFLAGS) -c avltree.c

main.o: main.c rbtree.h avltree.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f $(OBJS) $(TARGET)
