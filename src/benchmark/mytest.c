#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "../my_vm.h"

int main() {
    // Initialize the virtual memory system
    set_physical_mem();

    // Allocate a small block of memory
    void *va = t_malloc(PGSIZE);
    if (!va) {
        fprintf(stderr, "Failed to allocate memory\n");
        return -1;
    }

    printf("Allocated virtual address: %p\n", va);

    // Perform a translation (should result in a TLB miss initially)
    pte_t *pte = translate(page_directory, va);
    if (!pte) {
        fprintf(stderr, "Translation failed\n");
        return -1;
    }
    printf("Initial translation: VA %p -> PA %p\n", va, (void*)(*pte));

    // Modify the memory (to trigger TLB update)
    int value = 42;
    if (put_value(va, &value, sizeof(value)) != 0) {
        fprintf(stderr, "Failed to write to memory\n");
        return -1;
    }
    printf("Wrote %d to VA %p\n", value, va);

    // Perform another translation (should ideally result in a TLB hit)
    pte = translate(page_directory, va);
    if (!pte) {
        fprintf(stderr, "Translation failed\n");
        return -1;
    }
    printf("Second translation: VA %p -> PA %p\n", va, (void*)(*pte));

    // Free the allocated memory
    t_free(va, PGSIZE);

    // Optionally, you can print the TLB miss rate here
    print_TLB_missrate();

    return 0;
}





// int main() {
//     // Initialize the physical memory and TLB
//     set_physical_mem();

//     // Allocate some memory
//     void *addr1 = t_malloc(2500);
//     if (!addr1) {
//         fprintf(stderr, "Memory allocation failed\n");
//         return -1;
//     }

//     // Write a value to the allocated memory
//     int value = 12345;
//     if (put_value(addr1, &value, sizeof(value)) != 0) {
//         fprintf(stderr, "Failed to write to allocated memory\n");
//         return -1;
//     }

//     // Read the value back from the allocated memory
//     int read_value = 0;
//     get_value(addr1, &read_value, sizeof(read_value));
//     if (read_value != value) {
//         fprintf(stderr, "Incorrect value read from memory. Expected %d, got %d\n", value, read_value);
//         return -1;
//     }

//     // Print TLB miss rate
//     print_TLB_missrate();

//     // Free the allocated memory
//     t_free(addr1, PGSIZE);

//     // Optionally perform more operations to test the TLB under different scenarios

//     return 0;
// }