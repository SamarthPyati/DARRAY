#ifndef DARRAY_H_
#define DARRAY_H_

#define HANDLE_ERR(desc, msg) {                                             \
    do {                                                                    \
        fprintf(stderr, "%s:%s:%d:", __FILE__, __FUNCTION__, __LINE__);     \
        fprintf(stderr, "%s:%s\n", desc, msg);                              \
        exit(EXIT_FAILURE);                                                 \
    } while (0);                                                            \
}                                                                           \

/*  
    TERMS:
        - da  :  dynamic array
        - cap :  capacity
*/

/* Dependencies */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

/* Constants */
#define INITIAL_DARRAY_CAP 1                                    /* Default capacity of array */
#define DARRAY_GROWTH_FACTOR 2                                  /* Array grows by twice every time it gets full */

typedef struct
{
    int *items;         
    size_t cap;         /* array capacity */
    size_t len;         /* array lenght */
} darray;


/* Functions */
darray *_da_create(size_t cap);
void da_destroy(darray *da);
bool is_da_full(darray *da);
bool is_da_empty(darray *da);
void da_append(darray *da, int el);
void da_pop(darray *da);
void da_insert(darray *da, int idx, int el);
void da_shift_right(darray *da, size_t shiftBy);
void da_shift_left(darray *da, size_t shiftBy);
void da_randomize(darray *da, size_t len, const int MIN, const int MAX);
void da_remove(darray *da, int idx);
void da_copy(darray *dest, const darray *src);
void da_print(darray *da);
void da_print_entire(darray *da);

#define da_init() _da_create(INITIAL_DARRAY_CAP)                /* Create the array with default capacity */
#define ARRAY_LEN(arr) (sizeof(arr) / sizeof(arr[0]))           /* Get the length of any C array */

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

bool is_da_full(darray *da)
{   
    return da->cap == da->len;
}

bool is_da_empty(darray *da)
{
    return da->len == 0;
}

void da_append(darray *da, int el)
{
    if (is_da_full(da))
    {
        da->cap *= (size_t)(DARRAY_GROWTH_FACTOR);
        da->items = (int *) realloc(da->items, da->cap * sizeof(int));
        if (!da->items)
            HANDLE_ERR("DA_ITEM_REALLOC_ERR", "could not reallocate memory for items of array.");
    }
    da->items[da->len++] = el;
}

void da_pop(darray *da)
{   
    if (!is_da_empty(da))
    {
        return;
    } 
    else 
    {
        da->items[da->len--] = 0;
    }
}

void da_shift_left(darray *da, size_t shiftBy)
{   
    if (da->len == 0) return;
    shiftBy %= da->len;
    for (size_t i = 0; i < shiftBy; ++i)
    {
        int temp = da->items[0];
        for (size_t i = 0; i < da->len; ++i)
        {
            da->items[i] = da->items[i + 1];
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
        int temp = da->items[0];
        for (size_t j = 0; j < da->len - 1; j++)
        {
            da->items[j] = da->items[j + 1];
        }
        da->items[da->len - 1] = temp;
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

int da_get(darray *da, int idx)
{
    if (idx < 0) idx = da->len + idx;                // support for reverse indexing
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
    else 
    {   
        if (idx < 0) idx = da->len - idx;             // support for reverse indexing
        int temp = da->items[idx];
        for (size_t i = idx; i < da->len; ++i)
        {
            da->items[i] = da->items[i + 1];
        }
        da->items[da->len - 1] = 0;
        da->len--;
    }
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

void da_print(darray *da)
{   
    printf("[");
    for (size_t i = 0; i < da->len; i++)
    {
        printf("%d",da->items[i]);
        if (i < da->len - 1)
            printf(", ");
    }
    printf("]\n");
}

void da_print_entire(darray *da)
{
    printf("[");
    for (size_t i = 0; i < da->cap; i++)
    {
        printf("%d",da->items[i]);
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
        da->cap *= (size_t) DARRAY_GROWTH_FACTOR;
        da->items = (int *)realloc(da->items, da->cap * sizeof(int));
        if (da->items == NULL)
            HANDLE_ERR("DA_ITEM_REALLOC_ERR", "could not reallocate memory for items of array.");
    }
    else
    {   
        // shift the all the elements towards the right
        for (size_t i = da->len; i > idx; i--)
        {
            da->items[i] = da->items[i - 1];
        }
        da->items[idx] = el;
        da->len++;
    }
}

typedef enum
{
    ASC, 
    DSC, 
} sort_modes;

int ascending(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

int descending(const void *a, const void *b)
{
    return *(int *)b - *(int *)a;
}

darray *da_sort(darray *da, sort_modes mode)
{       
    darray *sorted = da_init();
    da_copy(sorted, da);
    qsort(sorted->items, sorted->len, sizeof(*sorted->items), mode == ASC ? ascending : descending );
    return sorted;  
}

void da_reverse(darray *da, void (*swap)(const void *, const void *))
{
    for (int i = 0; i < da->len / 2; ++i)
    {
        swap(&da->items[i], &da->items[da->len - i - 1]);
    }
}

void da_min_max(darray *da, int *min, int *max)
{
    darray *sorted = da_sort(da, ASC);
}

#endif // DARRAY_IMPLEMENTATION_