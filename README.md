# DARRAY (Dynamic Array)

A dynamic array implementation in C, providing a flexible and efficient way to handle arrays that automatically resize as needed.

## Features

- Automatic resizing when the array is full
- Support for negative indexing
- Array shifting (left and right)
- Array randomization
- Various utility functions (sorting, reversing, indexing, finding min/max)

## Installation

1. Download `darray.h` and `darray.c`.
2. Include `darray.h` in your project.

## Usage

To use the dynamic array, define `DARRAY_IMPLEMENTATION_` before including `darray.h` in your C file. Initialize the array using the `da_init()` function.

> [!NOTE] 
> This dynamic array implementation is currently only compatible with `int` types. A generalized implementation supporting other data types is in progress.

### Example

```c
#define DARRAY_IMPLEMENTATION_ // Define this macro before including 'darray.h'
#include "darray.h"

int main(void)
{
    darray *da = da_init(); // Initialize the array

    da_randomize(da, 10, 10, 1000); // Randomize the array
    da_print(da);

    // Check if the array is full or empty
    printf("Empty: %s\n", is_da_empty(da) ? "True" : "False");
    printf("Full: %s\n", is_da_full(da) ? "True" : "False");

    da_destroy(da);
    return 0;
}
```

## API Reference

### Initialization and Destruction

- `darray* da_create(size_t cap);` 
    Creates a dynamic array with the specified initial capacity.
  
- `void da_destroy(darray *da);`
    Frees the memory allocated for the dynamic array.

### Array Properties

- `bool is_da_full(const darray *da);`
  - Returns `true` if the array is full.

- `bool is_da_empty(const darray *da);`
  - Returns `true` if the array is empty.

### Array Operations

- `void da_append(darray *da, int el);`
  - Appends an element to the array.
  
- `void da_pop(darray *da);`
  - Removes the last element of the array.

- `void da_insert(darray *da, int idx, int el);`
  - Inserts an element at the specified index.

- `void da_shift_right(darray *da, size_t shiftBy);`
  - Shifts the array elements to the right by the specified amount.

- `void da_shift_left(darray *da, size_t shiftBy);`
  - Shifts the array elements to the left by the specified amount.

- `void da_randomize(darray *da, size_t len, const int MIN, const int MAX);`
  - Fills the array with random elements between `MIN` and `MAX`.

- `void da_remove(darray *da, int idx);`
  - Removes an element at the specified index.

### Array Access

- `int da_get(const darray *da, int idx);`
  - Retrieves an element at the specified index. Supports reverse indexing.

- `int da_get_max(const darray *da);`
  - Returns the maximum element in the array.

- `int da_get_min(const darray *da);`
  - Returns the minimum element in the array.

### Array Utilities

- `void da_copy(darray *dest, const darray *src);`
  - Copies the contents of the source array into the destination array.

- `void da_print(const darray *da);`
  - Prints the elements of the array.

- `void da_print_entire(const darray *da);`
  - Prints the entire allocated array, including unused capacity.

- `darray* da_sort(const darray *da, int mode);`
  - Returns a sorted copy of the array. `mode` can be `ASC` (ascending) or `DSC` (descending).

- `void da_reverse(darray *da);`
  - Reverses the elements of the array.

## Contributing

Contributions are welcome! Please feel free to submit a pull request or open an issue if you have any suggestions or bug reports.

## License

This project is licensed under the MIT License.