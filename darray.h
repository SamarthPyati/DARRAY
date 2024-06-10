#ifndef DARRAY_H_
#define DARRAY_H_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define INITIAL_DARRAY_CAP 1
#define DARRAY_GROWTH_FACTOR 2

typedef struct
{
    int *items;         
    size_t cap;         
    size_t len;         
} darray;

#define HANDLE_ERR(desc, msg) {                                             \
    do {                                                                    \
        fprintf(stderr, "%s:%s:%d:", __FILE__, __FUNCTION__, __LINE__);     \
        fprintf(stderr, "%s:%s\n", desc, msg);                              \
        exit(EXIT_FAILURE);                                                 \
    } while (0);                                                            \
}                                                                           \

darray *_da_create(size_t cap);
void da_destroy(darray *da);
bool is_da_full(const darray *da);
bool is_da_empty(const darray *da);
void da_append(darray *da, int el);
void da_pop(darray *da);
void da_insert(darray *da, int idx, int el);
void da_shift_right(darray *da, size_t shiftBy);
void da_shift_left(darray *da, size_t shiftBy);
void da_randomize(darray *da, size_t len, const int MIN, const int MAX);
void da_remove(darray *da, int idx);
void da_copy(darray *dest, const darray *src);
void da_print(const darray *da);
void da_print_entire(const darray *da);
int da_get(const darray *da, int idx);
int da_get_max(const darray *da);
int da_get_min(const darray *da);
darray *da_sort(const darray *da, int mode);

#define da_init() _da_create(INITIAL_DARRAY_CAP)
#define ARRAY_LEN(arr) (sizeof(arr) / sizeof(arr[0]))

#endif // DARRAY_H_

#ifdef DARRAY_IMPLEMENTATION_

darray *_da_create(size_t cap)
{
    darray *da = (darray *) malloc(sizeof(darray));
    if (!da)
    {
        HANDLE_ERR("DA_MEM_ALLOC_ERR", "could not allocate memory for array.");
    }
    da->items = (int *) malloc(cap * sizeof(int));
    if(!da->items)
    {
        HANDLE_ERR("DA_ITEM_MEM_ALLOC_ERR", "could not allocate memory for items of array.");
    }
    da->cap= cap;
    da->len = 0;
    return da;
}

void da_destroy(darray *da)
{
    if (da)
    {
        free(da->items);
        free(da);
    }
}

bool is_da_full(const darray *da)
{   
    return da->cap == da->len;
}

bool is_da_empty(const darray *da)
{
    return da->len == 0;
}

void da_append(darray *da, int el)
{
    if (is_da_full(da))
    {
        da->cap *= DARRAY_GROWTH_FACTOR;
        da->items = (int *) realloc(da->items, da->cap * sizeof(int));
        if (!da->items)
            HANDLE_ERR("DA_ITEM_REALLOC_ERR", "could not reallocate memory for items of array.");
    }
    da->items[da->len++] = el;
}

void da_pop(darray *da)
{   
    if (is_da_empty(da))
    {
        return;
    } 
    da->items[--da->len] = 0;
}

void da_shift_left(darray *da, size_t shiftBy)
{   
    if (da->len == 0) return;
    shiftBy %= da->len;
    for (size_t i = 0; i < shiftBy; ++i)
    {
        int temp = da->items[0];
        for (size_t j = 0; j < da->len - 1; ++j)
        {
            da->items[j] = da->items[j + 1];
        }
        da->items[da->len - 1] = temp;
    }
}

void da_shift_right(darray *da, size_t shiftBy)
{   
    if (da->len == 0) return;
    shiftBy %= da->len;
    for (size_t i = 0; i < shiftBy; ++i)
    {
        int temp = da->items[da->len - 1];
        for (size_t j = da->len - 1; j > 0; --j)
        {
            da->items[j] = da->items[j - 1];
        }
        da->items[0] = temp;
    }
}

void da_randomize(darray *da, size_t len, const int MIN, const int MAX)
{
    for (size_t i = 0; i < len; ++i)
    {   
        int el = rand() % (MAX - MIN + 1) + MIN;
        da_append(da, el);
    }
}

int da_get(const darray *da, int idx)
{
    if (idx < 0) idx = da->len + idx;                
    if (idx < 0 || idx >= da->len)
    {
        HANDLE_ERR("DA_IDX_OUT_OF_BOUNDS", "index given exceeds or preceeds the lenght of the array.");
    }
    return da->items[idx];
}

void da_remove(darray *da, int idx)
{   
    if (idx < -da->len || idx >= da->len)
    {
        HANDLE_ERR("DA_IDX_OUT_OF_BOUNDS", "index given exceeds or preceeds the lenght of the array.");
    }
    if (idx < 0) idx = da->len + idx;            
    for (size_t i = idx; i < da->len - 1; ++i)
    {
        da->items[i] = da->items[i + 1];
    }
    da->items[--da->len] = 0;
}

void da_copy(darray *dest, const darray *src)
{   
    dest->len = src->len;
    dest->cap = src->cap;
    dest->items = (int *) realloc(dest->items, src->cap * sizeof(int));
    if (!dest->items)
    {
        HANDLE_ERR("DA_ITEM_REALLOC_ERR", "could not reallocate memory for items of array.");
    }
    memcpy(dest->items, src->items, src->len * sizeof(int));
}

void da_print(const darray *da)
{   
    printf("[");
    for (size_t i = 0; i < da->len; i++)
    {
        printf("%d", da->items[i]);
        if (i < da->len - 1)
            printf(", ");
    }
    printf("]\n");
}

void da_print_entire(const darray *da)
{
    printf("[");
    for (size_t i = 0; i < da->cap; i++)
    {
        printf("%d", da->items[i]);
        if (i < da->cap - 1)
            printf(", ");
    }
    printf("]\n");
}

void da_insert(darray *da, int idx, int el)
{
    if (idx < 0 || idx > da->len)
    {
        HANDLE_ERR("DA_IDX_OUT_OF_BOUNDS", "index given exceeds or preceeds the lenght of the array.");
    }
    if (is_da_full(da))
    {
        da->cap *= DARRAY_GROWTH_FACTOR;
        da->items = (int *) realloc(da->items, da->cap * sizeof(int));
        if (da->items == NULL)
            HANDLE_ERR("DA_ITEM_REALLOC_ERR", "could not reallocate memory for items of array.");
    }
    for (size_t i = da->len; i > idx; i--)
    {
        da->items[i] = da->items[i - 1];
    }
    da->items[idx] = el;
    da->len++;
}

typedef enum
{
    ASC, 
    DSC, 
} sort_modes;

int ascending(const void *a, const void *b)
{
    return *(const int *)a - *(const int *)b;
}

int descending(const void *a, const void *b)
{
    return *(const int *)b - *(const int *)a;
}

darray *da_sort(const darray *da, int mode)
{       
    darray *sorted = da_init();
    da_copy(sorted, da);
    qsort(sorted->items, sorted->len, sizeof(*sorted->items), mode == ASC ? ascending : descending);
    return sorted;  
}

void da_reverse(darray *da)
{
    for (size_t i = 0; i < da->len / 2; ++i)
    {
        int temp = da->items[i];
        da->items[i] = da->items[da->len - i - 1];
        da->items[da->len - i - 1] = temp;
    }
}

int da_get_max(const darray *da)
{
    darray *sorted = da_sort(da, ASC);  
    int max = da_get(sorted, -1);
    da_destroy(sorted);
    return max;
}

int da_get_min(const darray *da)
{
    darray *sorted = da_sort(da, ASC);
    int min = da_get(sorted, 0);
    da_destroy(sorted);
    return min;
}

#endif // DARRAY_IMPLEMENTATION_
