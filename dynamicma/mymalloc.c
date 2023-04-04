#include "mymalloc.h"
#include <sys/mman.h>

typedef struct Page {
    struct Page* next;
    size_t size;
    size_t free_count;
    void* free_ptrs[0];
} Page;

static Page* first_page = NULL;

void* mymalloc(size_t size) {
    if (size == 0) {
        return NULL;
    }

    size_t total_size = size + sizeof(size_t);

    // Round the size to multiple of page size
    int page_size = getpagesize();
    size_t alloc_over = total_size % page_size;
    if (alloc_over > 0) {
        total_size += page_size - alloc_over;
    }

    // Check for available memory in previous pages
    Page* page = first_page;
    while (page != NULL) {
        if (page->free_count > 0) {
            void* ptr = page->free_ptrs[--page->free_count];
            *((size_t*)ptr) = size;
            return ptr + sizeof(size_t);
        }
        page = page->next;
    }

    // Allocate new page
    page = mmap(NULL, total_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (page == MAP_FAILED) {
        return NULL;
    }
    page->next = first_page;
    first_page = page;
    page->size = total_size;
    page->free_count = 0;

    // Store the size and return the pointer to allocated memory
    *((size_t*)page) = total_size;
    return ((void*)page) + sizeof(size_t);
}

void myfree(void* ptr) {
    if (ptr == NULL) {
        return;
    }

    // Get the size of the allocation
    void* page_ptr = ptr - sizeof(size_t);
    size_t size = *((size_t*)page_ptr);

    // Find the page and store the pointer to freed memory
    Page* page = first_page;
    while (page != NULL) {
        if (((void*)page <= page_ptr) && ((void*)page + page->size > page_ptr)) {
            if (page->free_count == 0) {
                page->free_ptrs[0] = page_ptr;
                page->free_count = 1;
            } else {
                // Find the correct place to insert the freed pointer
                size_t i;
                for (i = 0; i < page->free_count; i++) {
                    if (page->free_ptrs[i] > page_ptr) {
                        break;
                    }
                }
                // Shift the pointers to make room for the new one
                for (size_t j = page->free_count; j > i; j--) {
                    page->free_ptrs[j] = page->free_ptrs[j - 1];
                }
                page->free_ptrs[i] = page_ptr;
                page->free_count++;
                // Try to combine adjacent free memory blocks
                while ((i > 0) && (page->free_ptrs[i - 1] == (void*)((char*)page->free_ptrs[i] - size))) {
                    i--;
                    size += *((size_t*)(page->free_ptrs[i] - sizeof(size_t)));
                    page->free_ptrs[i] = page->free_ptrs[i + 
