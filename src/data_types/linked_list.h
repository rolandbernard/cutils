#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

typedef struct linked_list_element_s {
	void* _data;
	struct linked_list_element_s* _next;
} linked_list_element_t;

typedef struct {
	linked_list_element_t* _start;
} linked_list_t;

void linked_list_init(linked_list_t* list);

void linked_list_push(linked_list_t list, void* data);

void* linked_list_pop(linked_list_t list);

void linked_list_insert(linked_list_t list, void* data, unsigned int i);

void linked_list_remove(linked_list_t list, unsigned int i);

void* linked_list_get(linked_list_t list, unsigned int i);

unsigned int linked_list_length(linked_list_t list);

linked_list_t linked_list_copy(linked_list_t list);

void linked_list_connect(linked_list_t list_base, linked_list_t list2);

linked_list_t linked_list_concat(linked_list_t list1, linked_list_t list2);

linked_list_t linked_list_sublist(linked_list_t list, unsigned int i, unsigned int n);

void linked_list_element_function(linked_list_t list, void (*function)(void*));

void linked_list_free(linked_list_t* list);

#endif
