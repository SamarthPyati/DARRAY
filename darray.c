#define DARRAY_IMPLEMENTATION_
#include "darray.h"

int main(void)
{
    darray *da = da_init();

    for (int i = 0; i < 10; ++i) da_append(da, i);
    da_print(da);   
    for (int i = 0; i < 10; ++i) da_remove(da, 0);
    da_print(da);
    
    printf("%zu\n",da->cap);
    printf("%s\n", IsDaFull(da) ? "True" : "False");
    printf("%s\n", IsDaEmpty(da) ? "True" : "False");
    da_destroy(da);
    return 0;
}
