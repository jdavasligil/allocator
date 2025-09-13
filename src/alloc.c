#include "alloc.h"
#include <sys/mman.h>


/* Maps contiguous memory in the virtual address space of the program.
 * 
 * Arena allocation is the most simple and efficient allocation strategy.
 *
 * The allocator stores the beginning address (head), the next available
 * address (next), and the size in bytes of available memory.
 *
 * Allocation is done by returning the next address and adding the size of 
 * memory requested as an offset to get the new next address.
 *
 * To free memory, the entire arena must be freed at once.
 *
 * We allocate the default page size for ease. It is possible to allocate
 * larger page sizes on most systems, which would improve performance in
 * the case of large data. See the mmap man page for details.
 */
struct arena new_arena(size_t size)
{
	struct arena a;

	a.head = mmap(NULL,                      // Let kernel find address
			   size,                         // Bytes to allocate 
			   PROT_READ | PROT_WRITE,       // Memory access permissions
			   MAP_PRIVATE | MAP_ANONYMOUS,  // Memory visibility, no file
			   -1, 0);

	a.next = a.head;
	a.size = size;

	return a;
}


/* Frees the underlying virtual address space for the arena.
 *
 * Using the arena after it is freed is undefined behavior. 
 */
void free_arena(struct arena *arena_p)
{
	munmap(arena_p->head, arena_p->size);
}


/* Returns the address to a free block of memory within the arena.
 *
 * Caller must check for NULL.
 */
void *alloc(struct arena *arena_p, size_t size)
{
	if ( (arena_p->next + size) > (arena_p->head + arena_p->size) )
		return NULL;

	void *free_addr = arena_p->next;
	arena_p->next += size;

	return free_addr;
}
