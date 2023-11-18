#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "../my_vm.h"

#define BYTES 8192
#define NUMS 2048
#define PTRS 10



// #define NUM_ENTRIES (PGSIZE / sizeof(pde_t))
// #define OFFSET_BITS ((unsigned long)log2f(PGSIZE))
// #define PT_BITS  (((sizeof(pde_t) * 8) - OFFSET_BITS) / 2)
// #define PD_BITS (((sizeof(pde_t) * 8) - OFFSET_BITS) % 2) + PT_BITS
// #define VIRT_BITS (PT_BITS + PD_BITS)
// #define VBMAP_SIZE (VIRT_BITS % 8) == 0 ? (VIRT_BITS / 8) : ((VIRT_BITS / 8) + 1)

int main() {
    void *ptr[PTRS];

    // Allocate 2 pages for each pointer. Put 2 pages of ints in memory for each pointer.
    // Get 2 pages of ints from memory for each pointer. Validate that last int is 2 * (NUMS - 1)
    // for each pointer.
    printf("__________________________Test 1_____________________________\n");
    for(int i = 0; i < PTRS; i++){
        ptr[i] = t_malloc( BYTES);
    }

    int *ordered = (int *)malloc(sizeof(int) * NUMS);
    for(int i = 0; i < NUMS; i++){
        ordered[i] = 2*i;
    }

    for(int i = 0; i < PTRS; i++){
        put_value(ptr[i], ordered, sizeof(int) * NUMS);
    }

    int *recv = (int *)malloc(sizeof(int) * NUMS);
    printf("\n");
    for(int i = 0; i < PTRS; i++){
        get_value(ptr[i], recv, sizeof(int) * NUMS);
        printf("%d\n", recv[NUMS - 1]);
    }

    for(int i = 0; i < PTRS; i++){
        t_free(ptr[i], BYTES);
    }

    // Allocate 2 pages for each pointer. Put 1.5 pages of ints in memory at (virtual address + .5 pages)
    // for each pointer. Get 1.5 pages of ints from memory at virtual address + .5 pages for each pointer.
    // Ints are stored in recv, validate that ints at recv[count - 1] == count - 1 and recv[count] == 0.
    printf("\n__________________________Test 2_____________________________\n");
    for(int i = 0; i < PTRS; i++){
        ptr[i] = t_malloc( BYTES);
    }

    int count = NUMS - (NUMS/4);
    printf("\nCount: %d\n", count);
    memset(ordered, '\0', sizeof(int) * NUMS);
    for(int i = 0; i < count; i++){
        ordered[i] = i;
    }

    for(int i = 0; i < PTRS; i++){
        void * va = ((char *)ptr[i] + 2048);
        put_value(va, ordered, BYTES - 2048);
    }

    memset(recv, '\0', sizeof(int) * NUMS);
    for(int i = 0; i < PTRS; i++){
        void *va = ((char *)ptr[i] + 2048);
        get_value(va, recv, BYTES - 2048);
        printf("%d - %d\n", recv[count - 1], recv[count]);
        memset(recv, '\0', sizeof(int) * NUMS);
    }

    for(int i = 0; i < PTRS; i++){
        t_free(ptr[i], BYTES);
    }

    free(recv);
    free(ordered);

    return 0;
}