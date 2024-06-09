# DARRAY (Dynamic Array)
A dynamic array implementation in C.

> Note: As of now, the dynamic array is only compatible with `int` types. I will be working on making a generalised implementation which is compatible with any type.

## Features
*   Automatic resizing of array 
*   Reverse / negative indexing 
*   Array shifting
*   Array Randomization 

## Usage

To use the dynamic array, define the `DARRAY_IMPLEMENTATION_` and include `darray.h` in your C file and call the `da_init()` function to create an instance of the dynamic array.

## Example Usage

```c
#define DARRAY_IMPLEMENTATION_          // define this macro before including 'darray.h' 
#include "darray.h"

int main(void)
{
    darray *da = da_init();             // initialise the array

    da_randomize(da, 10, 10, 1000);     // randomise the array 
    da_print(da);

    // Check if da Full or Empty
    printf("Empty: %s\n", is_da_empty(da) ? "True" : "False");              
    printf("Full: %s\n", is_da_full(da) ? "True" : "False");
    da_destroy(da);
    return 0;
}
```