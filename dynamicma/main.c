#include <stdio.h>
#include "mymalloc.h"

int main() {
    // Allocate memory
    int* ptr1 = (int*) mymalloc(sizeof(int));
    int* ptr2 = (int*) mymalloc(3*sizeof(int));

    // Store values in allocated memory
    *ptr1 = 42;
    ptr2[0] = 1;
    ptr2[1] = 2;
    ptr2[2] = 3;

    // Print values
    printf("Value at ptr1: %d\n", *ptr1);
    printf("Values at ptr2: %d %d %d\n", ptr2[0], ptr2[1], ptr2[2]);

    // Free allocated memory
    myfree(ptr1);
    myfree(ptr2);

    return 0;
}
