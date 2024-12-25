#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include "allocator.h"

#define PAGE_SIZE 4096 
#define FREE_CHUNK 0 
#define USED_CHUNK 1 

void* heap = NULL;

void* alloc(size_t size){
    // the size increased by 16 to store the metadata 
    size += sizeof(size_t) * 2;                                   

    // this aligns the size provided by user with 32 bytes including 16 bytes overhead 
    if(size % 32 != 0){
        size = (size + 31) & ~31; 
    }


    // creating heap if there is no heap is present 
    if(!heap){
        void* current_sbrk = sbrk(0);                   
        heap = current_sbrk;
        void* requested_sbrk = (void*)sbrk(PAGE_SIZE);

        if(requested_sbrk == (void*)-1){
            return NULL;
        }
        else{
        
            // updating heap metadata for newly created heap  
            heap_info* new_heap = (heap_info*)heap;
            new_heap->heap_size = PAGE_SIZE;
            new_heap->heap_start = heap;
            new_heap->heap_end = requested_sbrk + PAGE_SIZE;
            new_heap->free_list_head = NULL;

            // Updating chunk metadata  
            chunk* new_chunk = (chunk*)((void*)current_sbrk + sizeof(heap_info));
            // adding one to the chunk size which indicate that the perticular chunk is in use
            new_chunk->chunk_size = size + USED_CHUNK;
            new_chunk->prev_size = 0;
            new_chunk->free_bk = NULL;
            new_chunk->free_fd = NULL;
            
            // Updating the chunk information in the heap info struct 
            new_heap->first_chunk = (void*)new_chunk;
            new_heap->last_chunk = (void*)new_chunk;
            new_heap->page_count = 1;
            new_heap->first_freed_chunk = NULL;
            new_heap->free_space = PAGE_SIZE - sizeof(heap_info) + size;
                    
            return (void*)new_chunk + (sizeof(size_t) * 2); 
        }
    }

    // allocating new chunk when heap is initalize       
    heap_info* new_heap =         


}


void dealloc(void *ptr){
    
}


int main(int argc, char** argv){
    printf("Hello Allocator!\n");
    int *ptr = alloc(10);
}
