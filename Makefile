CC=gcc
CFLAGS=-Wall -Wextra -Werror -g

.PHONY: build clean

all: build

build: friends posts feed

UTILS = users.o linked_list.o queue.o graph.o generic_tree.o

friends: $(UTILS) friends.o social_media_friends.o
	$(CC) $(CFLAGS) -o $@ $^

posts: $(UTILS) posts.o social_media_posts.o
	$(CC) $(CFLAGS) -o $@ $^
	
feed: $(UTILS) posts.o friends.o feed.o social_media_feed.o
	$(CC) $(CFLAGS) -o $@ $^

social_media_friends.o:
	$(CC) $(CFLAGS) -c -D TASK_1 -o $@ social_media.c

social_media_posts.o:
	$(CC) $(CFLAGS) -c -D TASK_2 -o $@ social_media.c

social_media_feed.o:
	$(CC) $(CFLAGS) -c -D TASK_1 -D TASK_2 -D TASK_3 -o $@ social_media.c

graph.o: graph.c
	$(CC) $(CFLAGS) -c -o $@ $^

linked_list.o: linked_list.c
	$(CC) $(CFLAGS) -c -o $@ $^

queue.o: queue.c
	$(CC) $(CFLAGS) -c -o $@ $^

generic_tree.o: generic_tree.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -rf *.o friends posts feed