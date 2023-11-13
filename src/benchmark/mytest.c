#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "../my_vm.h"

int main() {
    // set_physical_mem();
    void *ptr = t_malloc(100);
    printf("Virtual Address: %p\n", ptr);

    void *ptr1 = t_malloc(100);
    printf("Virtual Address: %p\n", ptr1);

    // void *ptr2 = t_malloc(100);
    // printf("Virtual Address: %p\n", ptr2);
    return 0;
}