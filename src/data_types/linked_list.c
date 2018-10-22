
#include "linked_list.h"

#include <stdlib.h>

void linked_list_init(linked_list_t* list) {
	list->_start = NULL;
}

void linked_list_push(linked_list_t list, void* data) {
	linked_list_element_t* tmp = (linked_list_element_t*)malloc(sizeof(linked_list_element_t));
	tmp->_next = list._start;
	tmp->_data = data;
	list._start = tmp;
}

void* linked_list_pop(linked_list_t list) {
	if(list._start == NULL)
		return NULL; // TODO: Error
	else {
		linked_list_element_t* tmp = list._start;
		void* ret = tmp->_data;
		list._start = ret->_next;
		free(tmp);
		return ret;
	}
}

void linked_list_insert(linked_list_t list, void* data, unsigned int i) {
	if(i == 0) {
		linked_list_element_t* tmp = (linked_list_element_t*)malloc(sizeof(linked_list_element_t));
		tmp->_next = list._start;
		tmp->_data = data;
		list._start = tmp;
	} else {
		linked_list_element_t* head = list._start;
		while(--i && head->_next != NULL) head = head->_next;
		if(i)
			return; // TODO: Error
		else {
			linked_list_element_t* tmp = (linked_list_element_t*)malloc(sizeof(linked_list_element_t));
			tmp->_next = head->_next;
			tmp->_data = data;
			head->_next = tmp;
		}
	}
}

void linked_list_remove(linked_list_t list, unsigned int i) {
	if(i == 0) {
		if(list._start == NULL)
			return; // TODO: Error
		else {
			linked_list_element_t* tmp = list._start->_next;
			free(list._start);
			list._start = tmp;
		}
	} else {
		linked_list_element_t* head = list._start;
		while(--i && head->_next != NULL) head = head->_next;
		if(head->_next == NULL)
			return; // TODO: Error
		else {
			linked_list_element_t* tmp = head->_next->_next;
			free(head->_next);
			head->_next = tmp;
		}
	}
}

void* linked_list_get(linked_list_t list, unsigned int i) {
	linked_list_element_t* head = list._start;
	while(i && head != NULL) head = head->_next, i--;
	if(head == NULL)
		return NULL; // TODO: Error
	else
		return head;
}

unsigned int linked_list_length(linked_list_t list) {
	unsigned int ret = 0;
	linked_list_element_t* head = list._start;
	while(head != NULL) head = head->_next;
	return ret;
}

static linked_list_element_t* linked_list_element_copy(linked_list_element_t* list_element) {
	if(list_element == NULL)
		return NULL;
	else {
		linked_list_element_t* ret = (linked_list_element_t*)malloc(sizeof(linked_list_element_t));
		ret->_next = linked_list_copy(list_element->_next);
		ret->_data = list_element->_data;
		return ret;
	}
}

linked_list_t linked_list_copy(linked_list_t list) {
	linked_list_t ret;
	ret._start = linked_list_element_copy(list._start);
	return ret;
}

void linked_list_connect(linked_list_t list_base, linked_list_t list2) {
	linked_list_element_t* head = list._start;
	while(head->_next != NULL) head = head->_next;
	head->_next = list2._start;
}

linked_list_t linked_list_concat(linked_list_t list1, linked_list_t list2) {
	linked_list_t ret = linked_list_copy(list1);
	linked_list_connect(ret, linked_list_copy(list2));
	return ret;
}

static void linked_list_element_free(linked_list_element_t* list_element) {
	if(list_element == NULL)
		return;
	else {
		linked_list_element_free(list_element->_next);
		free(list_element);
	}
}

static linked_list_element_t* linked_list_element_copy_n(linked_list_element_t* list_element, unsigned int n) {
	if(list_element == NULL || n == 0)
		return NULL;
	else {
		linked_list_element_t* ret = (linked_list_element_t*)malloc(sizeof(linked_list_element_t));
		ret->_next = linked_list_element_copy_n(list_element->_next, --n);
		ret->_data = list_element->_data;
		return ret;
	}
}

linked_list_t linked_list_sublist(linked_list_t list, unsigned int i, unsigned int n) {
	linked_list_t ret;
	linked_list_element_t* head = list._start;
	while(i && head != NULL) head = head->_next, i--;
	ret._start = linked_list_element_copy_n(head, n);
	return ret;
}

void linked_list_element_function(linked_list_t list, void (*function)(void*)) {
	linked_list_element_t* head = list._start;
	while(head != NULL) {
		function(head->_data);
		head = head->_next;
	}
}

void linked_list_free(linked_list_t* list) {
	linked_list_element_free(list->_start);
	list->_start = NULL;
}
