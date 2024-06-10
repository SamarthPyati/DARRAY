#define DARRAY_IMPLEMENTATION_
#include "darray.h"

int main(void)
{
    srand(time(NULL));
    darray *da = da_init();

    /* Randomizing Array */
    da_randomize(da, 10, 0, 10);    
    da_print(da);

    /* Getting an element via indexing */
    printf("Elements in the array: \n");
    for (int i = 0; i < da->len; ++i) printf("da->items[%d]: %d\n", i, da_get(da, i));
    printf("\n");
    printf("Elements in the array (Reverse Order): \n");
    for (int i = da->len - 1; i >= 0; --i) printf("da->items[%d]: %d\n", i, da_get(da, i));
    
    /* Copying array */
    darray *copy = da_init();
    da_copy(copy, da);
    da_print(copy);

    /* Sorting array */ 
    darray *asc = da_sort(da, ASC);
    darray *dsc = da_sort(da, DSC);
    da_print(asc);
    da_print(dsc);
        
    /* Reversing array */
    da_reverse(da);
    da_print(da);

    /* Get Min & Max Elements */
    printf("MAX: %d\n", da_get_max(da));
    printf("MIN: %d\n", da_get_min(da));

    // printf("Empty: %s\n", is_da_empty(da) ? "True" : "False");
    // printf("Full: %s\n", is_da_full(da) ? "True" : "False");
    da_destroy(da);
    return 0;
}
