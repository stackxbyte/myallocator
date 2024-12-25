#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <sys/types.h>
#include <unistd.h>

typedef struct chunk {
    size_t chunk_size;      // Size of the chunk including overhead
    size_t prev_size;
    
    // Only used when chunk is free
    struct chunk *free_fd;  // Forward pointer in the free list
    struct chunk *free_bk;  // Backward pointer in the free list
} chunk;


typedef struct heap_info {
    size_t free_space;        // Total free space in the heap
    size_t heap_size;         // Total size of the heap
    chunk* first_chunk;       // Pointer to the first chunk in the heap
    chunk* last_chunk;        // Pointer to the last chunk in the heap
    chunk* first_freed_chunk; // Pointer to first free chunk
    chunk* free_list_head;    // Head of the free list
    void* heap_start;         // Starting address of the heap
    void* heap_end;           // Current end address of the heap
    int page_count;
} heap_info;

void* alloc(size_t size);
void dealloc(void *ptr);

#endif
