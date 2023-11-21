#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "../my_vm.h"

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

    t_free(ptr, 4096 * 10);
    print_TLB_missrate();

    return 0;
}