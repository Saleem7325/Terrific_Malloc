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

    // 1) Double Free
    void *ptr = t_malloc(10000);
    t_free(ptr, 10000);
    t_free(ptr, 10000);


    printf("\nTest 2_____________________________________________\n");
    t_free((void *)0xffc6b010, 100);

    printf("\nTest 3_____________________________________________\n");
    void *ptr5 = t_malloc(10);
    void *ptr6 = t_malloc(10);

    t_free(ptr5, 5000);
    t_free(ptr6, 10);


    return 0;
}