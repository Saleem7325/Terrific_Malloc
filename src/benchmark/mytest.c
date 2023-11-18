#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "../my_vm.h"

#define BYTES 8192
#define NUMS 2048
#define PTRS 10

#define SIZE 5
#define ARRAY_SIZE 400


void print_matrix(void *matrix){
    int address_a = 0; 
    int address_b = 0;
    int address_c = 0;
    int y;

    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            address_a = (unsigned int)matrix + ((i * SIZE * sizeof(int))) + (j * sizeof(int));
            get_value((void *)address_a, &y, sizeof(int));
            printf("%d ", y);
        }
        printf("\n");
    }
    printf("\n"); 
}
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
        memset(recv, '\0', sizeof(int) * NUMS);
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

    printf("\n__________________________Matrix Test 1_____________________________\n");
    void *a = t_malloc(ARRAY_SIZE);
    void *b = t_malloc(ARRAY_SIZE);
    
    void *c = t_malloc(ARRAY_SIZE);
    int x = 1; int s = 2; int y, z; int i =0, j=0;
    int address_a = 0, address_b = 0;
    int address_c = 0;

    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            address_a = (unsigned int)a + ((i * SIZE * sizeof(int))) + (j * sizeof(int));
            address_b = (unsigned int)b + ((i * SIZE * sizeof(int))) + (j * sizeof(int));
            
            s += 2;
            put_value((void *)address_a, &s, sizeof(int));
            put_value((void *)address_b, &x, sizeof(int));
        }
    }

    print_matrix(a);
    print_matrix(b); 
    mat_mult(a, b, SIZE, c);
    print_matrix(c);


    t_free(a, ARRAY_SIZE);
    t_free(b, ARRAY_SIZE);
    t_free(c, ARRAY_SIZE);

    return 0;
}