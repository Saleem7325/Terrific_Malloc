#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "../my_vm.h"

// #define NUM_ENTRIES (PGSIZE / sizeof(pde_t))
// #define OFFSET_BITS ((unsigned long)log2f(PGSIZE))
// #define PT_BITS  (((sizeof(pde_t) * 8) - OFFSET_BITS) / 2)
// #define PD_BITS (((sizeof(pde_t) * 8) - OFFSET_BITS) % 2) + PT_BITS
// #define VIRT_BITS (PT_BITS + PD_BITS)
// #define VBMAP_SIZE (VIRT_BITS % 8) == 0 ? (VIRT_BITS / 8) : ((VIRT_BITS / 8) + 1)

int main() {
    void *ptr = t_malloc(10000);
    t_free(ptr, 10000);
    t_free(ptr, 10000);

    void *ptr1 = t_malloc(100);
    t_free(ptr1, 100);

    void *ptr2 = t_malloc(10000);
    void *ptr3 = t_malloc(5000);
    void *ptr4 = t_malloc(100);

    t_free(ptr2, 10000);
    t_free(ptr2, 100);

    t_free(ptr3, 5000);
    t_free(ptr3, 50);

    t_free(ptr4, 100);
    t_free(ptr4, 100);

    return 0;
}