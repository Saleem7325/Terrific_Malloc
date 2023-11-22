#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "../my_vm.h"

#define SIZE 5
#define ARRAY_SIZE 400

int main() {
    void *ptr = t_malloc(4096 * 10);

    int arr[10];
    for(int i = 0; i < 10; i++){
        arr[i] = i;
    }

    void *page = ptr;
    for(int i = 0; i < 10; i++){
        put_value(page, &arr[i], sizeof(int));
        page = ((char *)page + 4096);
    }

    print_TLB_missrate();

    int recv[10];
    page = ptr;
    for(int i = 0; i < 10; i++){
        get_value(page, &recv[i], sizeof(int));
        page = ((char *)page + 4096);
    }

    print_TLB_missrate();

    t_free(ptr, 4096 * 10);
    print_TLB_missrate();

    printf("\n______________________MATRIX TEST___________________\n\n");

    void *a = t_malloc(ARRAY_SIZE);
    int old_a = (int)a;
    void *b = t_malloc(ARRAY_SIZE);
    void *c = t_malloc(ARRAY_SIZE);
    int x = 1;
    int y, z;
    int i =0, j=0;
    int address_a = 0, address_b = 0;
    int address_c = 0;

    printf("Addresses of the allocations: %x, %x, %x\n", (int)a, (int)b, (int)c);

    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            address_a = (unsigned int)a + ((i * SIZE * sizeof(int))) + (j * sizeof(int));
            address_b = (unsigned int)b + ((i * SIZE * sizeof(int))) + (j * sizeof(int));

            int p = 20;
            put_value((void *)address_a, &p, sizeof(int));
            put_value((void *)address_b, &x, sizeof(int));
        }
    }

    printf("\n");
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            address_a = (unsigned int)a + ((i * SIZE * sizeof(int))) + (j * sizeof(int));
            get_value((void *)address_a, &y, sizeof(int));
            printf("%d ", y);
        }
        printf("\n");
    }

        printf("\n");
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            address_b = (unsigned int)b + ((i * SIZE * sizeof(int))) + (j * sizeof(int));
            get_value( (void *)address_b, &y, sizeof(int));
            printf("%d ", y);
        }
        printf("\n");
    }  

    printf("\n");
    mat_mult(a, b, SIZE, c);
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            address_c = (unsigned int)c + ((i * SIZE * sizeof(int))) + (j * sizeof(int));
            get_value((void *)address_c, &y, sizeof(int));
            printf("%d ", y);
        }
        printf("\n");
    }

    t_free(a, ARRAY_SIZE);
    t_free(b, ARRAY_SIZE);
    t_free(c, ARRAY_SIZE);

    return 0;
}