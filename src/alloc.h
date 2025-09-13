#ifndef ALLOC_H
#define ALLOC_H

#include <unistd.h>

struct arena {
	void *head;
	void *next;
	size_t size;
};

struct arena new_arena(size_t size);
void free_arena(struct arena *arena_p);
void *alloc(struct arena *arena_p, size_t size);

#endif // ALLOC_H
