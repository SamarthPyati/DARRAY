#define DARRAY_IMPLEMENTATION_
#include "darray.h"

int main(void)
{
    darray *da = da_init();

    da_randomize(da, 10, 10, 1000);
    da_print(da);

    // printf("Empty: %s\n", is_da_empty(da) ? "True" : "False");
    // printf("Full: %s\n", is_da_full(da) ? "True" : "False");
    da_destroy(da);
    return 0;
}
