#include "my_vm.h"

/*
 * Number of entries we can fit in a Page Table/Directory
*/
#define NUM_ENTRIES (PGSIZE / sizeof(pde_t))

/*
 * Number of bits in address that specify index into page
*/
#define OFFSET_BITS ((unsigned long)log2f(PGSIZE))

/*
 * Number of bits in address that specify index into page table
*/
#define PT_BITS  (((sizeof(pde_t) * 8) - OFFSET_BITS) / 2)

/*
 * Number of bits in address that specify index into page directory
*/
#define PD_BITS (((sizeof(pde_t) * 8) - OFFSET_BITS) % 2) + PT_BITS

/*
 * Number of virtual address bits
*/
#define VIRT_BITS (PT_BITS + PD_BITS)

/*
 * Number of chars to store in virtual bitmap
*/
#define VBMAP_SIZE (VIRT_BITS % 8) == 0 ? (VIRT_BITS / 8) : ((VIRT_BITS / 8) + 1)

/*
 * Number of chars to store in physical bitmap
*/
#define PBMAP_SIZE ((MEMSIZE / PGSIZE) / 8)

/*
 * Physical memory
*/
char *phys_mem;

/*
 * Bitmap representing all pages in phys_mem
 * 1 = allocated, 0 = free
*/
char page_bitmap[PBMAP_SIZE];

/*
 * Bitmap representing all possible virtual addresses
*/
char *virt_bitmap;

/*
 * Pointer to Page Directory in phys_mem (points to start of phys_mem).
 * First page in memory is allocated to page directory.
*/
pde_t *page_directory;

/*
 * For validating/checking page_bitmap
*/
int get_bit_at_index(char *bitmap, int index){
    int byte_index = index / 8;
    int bit_index = index % 8;

    char byte = bitmap[byte_index];
    if(byte & (1 << bit_index)){
        return 1;
    }else{
        return 0;
    }
}

/*
 * Function responsible for allocating and setting your physical memory 
*/
void set_physical_mem() {
    //Allocate physical memory using mmap or malloc; this is the total size of
    //your memory you are simulating
    //HINT: Also calculate the number of physical and virtual pages and allocate
    //virtual and physical bitmaps and initialize them

    // Create physical memory 
    // Initialize page bitmap 
    phys_mem = (char *)malloc(MEMSIZE);
    memset(page_bitmap, 0, PBMAP_SIZE);

    // Assign Page directory first page in memory and initialize
    page_directory = (pde_t *)phys_mem;
    memset(page_directory, 0, PGSIZE);

    // Create and initialize virtual bitmap
    virt_bitmap = (char *)malloc(VBMAP_SIZE);
    memset(virt_bitmap, 0, VBMAP_SIZE);

    // Set first bit in bitmap since that is where page directory is being stored 
    char *byte = &page_bitmap[0];
    *byte = *byte | 1;

    // Print config macros for debugging
    printf("Number of entries: %d\n", NUM_ENTRIES);
    printf("Offset bits: %ld\n", OFFSET_BITS);
    printf("Page table bits: %ld\n", PT_BITS);
    printf("Page directory bits: %ld\n", PD_BITS);
    printf("Virtual bits: %ld\n", VIRT_BITS);
    printf("Virtual bitmap size: %ld\n", VBMAP_SIZE);
    printf("Page bitmap size: %d\n", PBMAP_SIZE);
}


/*
 * Part 2: Add a virtual to physical page translation to the TLB.
 * Feel free to extend the function arguments or return type.
 */
int add_TLB(void *va, void *pa) {

    /*Part 2 HINT: Add a virtual to physical page translation to the TLB */

    return -1;
}


/*
 * Part 2: Check TLB for a valid translation.
 * Returns the physical page address.
 * Feel free to extend this function and change the return type.
 */
pte_t *check_TLB(void *va) {

    /* Part 2: TLB lookup code here */



   /*This function should return a pte_t pointer*/
}


/*
 * Part 2: Print TLB miss rate.
 * Feel free to extend the function arguments or return type.
 */
void print_TLB_missrate() {
    double miss_rate = 0;	

    /*Part 2 Code here to calculate and print the TLB miss rate*/




    fprintf(stderr, "TLB miss rate %lf \n", miss_rate);
}



/*
The function takes a virtual address and page directories starting address and
performs translation to return the physical address
*/
pte_t *translate(pde_t *pgdir, void *va) {
    /* Part 1 HINT: Get the Page directory index (1st level) Then get the
    * 2nd-level-page table index using the virtual address.  Using the page
    * directory index and page table index get the physical address.
    *
    * Part 2 HINT: Check the TLB before performing the translation. If
    * translation exists, then you can return physical address from the TLB.
    */


    //If translation not successful, then return NULL
    return NULL; 
}


/*
The function takes a page directory address, virtual address, physical address
as an argument, and sets a page table entry. This function will walk the page
directory to see if there is an existing mapping for a virtual address. If the
virtual address is not present, then a new entry will be added
*/
int page_map(pde_t *pgdir, void *va, void *pa) {

    /*HINT: Similar to translate(), find the page directory (1st level)
    and page table (2nd-level) indices. If no mapping exists, set the
    virtual to physical mapping */

    return -1;
}


/*Function that gets the next available page
*/
void *get_next_avail(int num_pages) {
 
    //Use virtual address bitmap to find the next free page
}


/* Function responsible for allocating pages
and used by the benchmark
*/
void *t_malloc(unsigned int num_bytes) {

    /* 
     * HINT: If the physical memory is not yet initialized, then allocate and initialize.
     */

   /* 
    * HINT: If the page directory is not initialized, then initialize the
    * page directory. Next, using get_next_avail(), check if there are free pages. If
    * free pages are available, set the bitmaps and map a new page. Note, you will 
    * have to mark which physical pages are used. 
    */

    return NULL;
}

/* Responsible for releasing one or more memory pages using virtual address (va)
*/
void t_free(void *va, int size) {

    /* Part 1: Free the page table entries starting from this virtual address
     * (va). Also mark the pages free in the bitmap. Perform free only if the 
     * memory from "va" to va+size is valid.
     *
     * Part 2: Also, remove the translation from the TLB
     */
    
}


/* The function copies data pointed by "val" to physical
 * memory pages using virtual address (va)
 * The function returns 0 if the put is successfull and -1 otherwise.
*/
int put_value(void *va, void *val, int size) {

    /* HINT: Using the virtual address and translate(), find the physical page. Copy
     * the contents of "val" to a physical page. NOTE: The "size" value can be larger 
     * than one page. Therefore, you may have to find multiple pages using translate()
     * function.
     */


    /*return -1 if put_value failed and 0 if put is successfull*/

}


/*Given a virtual address, this function copies the contents of the page to val*/
void get_value(void *va, void *val, int size) {

    /* HINT: put the values pointed to by "va" inside the physical memory at given
    * "val" address. Assume you can access "val" directly by derefencing them.
    */


}



/*
This function receives two matrices mat1 and mat2 as an argument with size
argument representing the number of rows and columns. After performing matrix
multiplication, copy the result to answer.
*/
void mat_mult(void *mat1, void *mat2, int size, void *answer) {

    /* Hint: You will index as [i * size + j] where  "i, j" are the indices of the
     * matrix accessed. Similar to the code in test.c, you will use get_value() to
     * load each element and perform multiplication. Take a look at test.c! In addition to 
     * getting the values from two matrices, you will perform multiplication and 
     * store the result to the "answer array"
     */
    int x, y, val_size = sizeof(int);
    int i, j, k;
    for (i = 0; i < size; i++) {
        for(j = 0; j < size; j++) {
            unsigned int a, b, c = 0;
            for (k = 0; k < size; k++) {
                int address_a = (unsigned int)mat1 + ((i * size * sizeof(int))) + (k * sizeof(int));
                int address_b = (unsigned int)mat2 + ((k * size * sizeof(int))) + (j * sizeof(int));
                get_value( (void *)address_a, &a, sizeof(int));
                get_value( (void *)address_b, &b, sizeof(int));
                // printf("Values at the index: %d, %d, %d, %d, %d\n", 
                //     a, b, size, (i * size + k), (k * size + j));
                c += (a * b);
            }
            int address_c = (unsigned int)answer + ((i * size * sizeof(int))) + (j * sizeof(int));
            // printf("This is the c: %d, address: %x!\n", c, address_c);
            put_value((void *)address_c, (void *)&c, sizeof(int));
        }
    }
}