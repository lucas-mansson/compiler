#include "value.h"
#include "memory.h"
#include <stdio.h>

void init_value_array(value_array* array)
{
    array->values = NULL;
    array->capacity = 0;
    array->count = 0;
}

void write_value_array(value_array* array, value val)
{
    if (array->capacity < array->count + 1) {
        int old_capacity = array->capacity;
        array->capacity = GROW_CAPACITY(old_capacity);
        array->values =
            GROW_ARRAY(value, array->values, old_capacity, array->capacity);
    }

    array->values[array->count] = val;
    array->count++;
}

void free_value_array(value_array* array)
{
    FREE_ARRAY(value, array->values, array->capacity);
}

void print_value(value value) { printf("%g", value); }
