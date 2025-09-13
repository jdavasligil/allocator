#include <string.h>
#include <stdio.h>
#include "alloc.h"

int main(void)
{
	struct arena hello_arena = new_arena(4096);

	// Allocate a 64 byte buffer for the string.
	char *s = (char *)alloc(&hello_arena, sizeof(char) * 64);

	// Allocate remaining bytes (4032 + 64 = 4096).
	char *s2 = (char *)alloc(&hello_arena, sizeof(char) * 4032);

	// Attempting to allocate further will yield NULL.

	memcpy(s, "Hello, world!", 14);
	memcpy(s2, "A chip off the old block.", 26);

    puts(s);
    puts(s2);

	// Data can be obtained directly from the arena data.
	//puts((char *)hello_arena.head);
	//puts((char *)hello_arena.head + 64);

	free_arena(&hello_arena);

	// The arena is now invalid. Using after free will segfault.
	// This means ALL pointers obtained by alloc from that arena are invalid.

	//puts(s);  // Don't do this!
	//puts(s2); // Or this!
 
    return 0;
}
