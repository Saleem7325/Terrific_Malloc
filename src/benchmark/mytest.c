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

    void *ptr[50];
    for(int i = 0; i < 1; i++){
        ptr[i] = t_malloc(1000);
    }

    int ordered[10];
    for(int i = 0; i < 10; i++){
        ordered[i] = 2*i;
    }

    put_value(ptr[0], &ordered, sizeof(int) * 10);

    int recv[10];
    get_value(ptr[0], &recv, sizeof(int) * 10);

    for(int i = 0; i < 10; i++){
        printf("%d\n", recv[i]);
    }

    for(int i = 0; i < 1; i++){
        t_free(ptr[i], 1000);
    }




    return 0;
}