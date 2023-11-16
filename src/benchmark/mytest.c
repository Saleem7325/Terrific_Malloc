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

// char *virt_bitmap;

// int page_directory_index(void *va){
//     long unsigned int vaddr = (long unsigned int)va;
//     return (vaddr >> (PT_BITS + OFFSET_BITS));
// }

// int page_table_index(void *va){
//     int mask = ((1 << PT_BITS) - 1);
//     return (((long unsigned int)va >> (OFFSET_BITS)) & mask);
// }

// int offset(void *va){
//     int mask = ((1 << OFFSET_BITS) - 1);
//     return ((int)va & mask);
// }

// /*
//     [ 20 bits virtual ][ 12 bits offset ]
//     0000000000000000000000000000000000000
//     0000000000000000000123123123123123123
// */
// void *virtual_address(void *pa, int pages){
//     if(!virt_bitmap){
//         return NULL;
//     }

//     int ofset = offset(pa);

//     unsigned int vbits = 0;
//     memcpy(&vbits, virt_bitmap, VBMAP_SIZE);
//     printf("Virtual bits: %d\n", vbits);

//     unsigned int vmap_cpy = vbits;
//     vmap_cpy += pages;
//     memcpy(virt_bitmap, &vmap_cpy, VBMAP_SIZE);

//     vbits = ((vbits <<  OFFSET_BITS) | ofset);
//     return (void *)vbits;
// }

int main() {
    void *ptr = t_malloc(100);
    void *ptr1 = t_malloc(100);
    // void *ptr2 = t_malloc(100);
    // void *ptr3 = t_malloc(100);
    // void *ptr4 = t_malloc(100);
    // void *ptr5 = t_malloc(100);
    // void *ptr6 = t_malloc(10000);

    t_free(ptr, 100);
    t_free(ptr1, 100);

    // virt_bitmap = (char *)malloc(VBMAP_SIZE);
    // memset(virt_bitmap, 0, VBMAP_SIZE);

    // void *a = (void *)0xFFFFFFFF;
    // printf("Physical Address: %p\n", a);
    // printf("PD INDEX: %d\n", page_directory_index(a));
    // printf("PT INDEX: %d\n", page_table_index(a));
    // printf("OFFSET: %d\n", offset(a));
    // printf("Virtual Address: %p\n\n", virtual_address(a, 1));

    // a = (void *)0xFF00FF00;
    // printf("Physical Address: %p\n", a);
    // printf("PD INDEX: %d\n", page_directory_index(a));
    // printf("PT INDEX: %d\n", page_table_index(a));
    // printf("OFFSET: %d\n", offset(a));
    // printf("Virtual Address: %p\n\n", virtual_address(a, 1));

    // a = (void *)0xF0F0F0F0;
    // printf("Physical Address: %p\n", a);
    // printf("PD INDEX: %d\n", page_directory_index(a));
    // printf("PT INDEX: %d\n", page_table_index(a));
    // printf("OFFSET: %d\n", offset(a));
    // printf("Virtual Address: %p\n\n", virtual_address(a, 1));

    return 0;
}