#pragma once

#include "defines.h"
#include <stdlib.h>
#include <string.h>

typedef size_t usize;

struct Array_List{

  size_t len;
  size_t capacity;
  size_t item_size;
  void * items;

};

static Array_List array_context = {0};

Array_List *array_list_create(usize item_size, usize initial_capacity) {
    Array_List *list = (Array_List*)malloc(sizeof(Array_List));

    if (!list)
	    ERROR_RETURN(NULL, "Could not allocate memory for Array_List\n");

    list->item_size = item_size;
    list->capacity = initial_capacity;
    list->len = 0;
    list->items = malloc(item_size * initial_capacity);

    if (!list->items)
	    ERROR_RETURN(NULL, "Could not allocate memory for Array_List\n");

    return list;
}

usize array_list_append(Array_List *list, void *item) {
	if (list->len == list->capacity) {
		list->capacity = list->capacity > 0 ? list->capacity * 2 : 1;
		void *items = realloc(list->items, list->item_size * list->capacity);

		if (!items)
			ERROR_RETURN(-1, "Could not allocate memory for Array_List\n");

		list->items = items;
	}

	usize index = list->len++;

	memcpy((u8*)list->items + index * list->item_size, item, list->item_size);

	return index;
}

void *array_list_get(Array_List *list, usize index) {
	if (index >= list->len)
		ERROR_RETURN(NULL, "Index out of bounds\n");

	return (u8*)list->items + index * list->item_size;
}

u8 array_list_remove(Array_List *list, usize index) {
	if (list->len == 0)
		ERROR_RETURN(1, "List is empty\n");
	if (index >= list->len)
		ERROR_RETURN(1, "Index out of bounds\n");

	if (list->len == 1) {
		list->len = 0;
		return 0;
	}

	--list->len;

	u8 *item_ptr = (u8*)list->items + index * list->item_size;
	u8 *end_ptr = (u8*)list->items + list->len * list->item_size;
	memcpy(item_ptr, end_ptr, list->item_size);

	return 0;
}
