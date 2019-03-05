
#include "data_types/string.h"
#include "data_types/linked_list.h"
#include "data_types/tensor.h"

#include <stdio.h>

void print_string(void* data, void* usr_data) {
	fprintf(stderr, "%s\n", string_get_c_str(*(string_t*)data));
}

int cmp_string(void* data, void* cmp) {
	return string_cmp(*(string_t*)data, *(string_t*)cmp) == 0;
}

void print(tensor_type_t v, const unsigned int* pos, void* ud) {
	for(int i = 0; i < 4; i++)
		fprintf(stdout, "%u ", pos[i]);
	fprintf(stdout, "  %g\n", v);
}

tensor_type_t sqr(tensor_type_t v, const unsigned int* pos, void* ud) {
	return v*v;
}

int main(int argc, char** argv) {

	linked_list_t list;
	linked_list_init(&list);

	string_t test;
	string_init(&test);
	string_create(&test, "Test");
	string_t hallo;
	string_init(&hallo);
	string_create(&hallo, "Hallo");

	linked_list_push(&list, (void*)&test);
	linked_list_push(&list, (void*)&hallo);

	fprintf(stderr, "%s\n", string_get_c_str(*(string_t*)linked_list_get(list, 0)));
	fprintf(stderr, "%s\n", string_get_c_str(*(string_t*)linked_list_get(list, 1)));

	linked_list_t list2 = linked_list_concat(list, list);

	for(unsigned int i = 0; i < linked_list_length(list2); i++)
		fprintf(stderr, "%s\n", string_get_c_str(*(string_t*)linked_list_get(list2, i)));

	linked_list_t list3 = linked_list_sublist(list2, 1, 2);

	linked_list_element_function(list3, print_string, NULL);

	unsigned int test_find = linked_list_find_first(list3, cmp_string, (void*)&test);

	fprintf(stderr, "%s\n", string_get_c_str(*(string_t*)linked_list_get(list3, test_find)));

	string_t concat = string_concat(test, hallo);

	fprintf(stderr, "%s\n", string_get_c_str(concat));

	string_t substr = string_substr(concat, 1, 5);

	fprintf(stderr, "%s\n", string_get_c_str(substr));

	unsigned int find = string_find(concat, hallo);

	fprintf(stderr, "%u\n", find);

	string_t invert = string_invert(substr);

	fprintf(stderr, "%s\n", string_get_c_str(invert));

	int cmp = string_cmp(test, invert);

	fprintf(stderr, "%i\n", cmp);

	string_free(&test);
	string_free(&hallo);
	string_free(&concat);
	string_free(&substr);
	string_free(&invert);

	tensor_t tens;
	unsigned int size[] = {1, 2, 3, 4};
	tensor_init_zero(&tens, 4, size);
	
	unsigned int pos[] = {0, 0, 0, 0};
	tensot_set(tens, pos, 1);
	pos[1] = 1;
	tensot_set(tens, pos, 2);
	pos[2] = 2;
	tensot_set(tens, pos, 3);
	pos[3] = 3;
	tensot_set(tens, pos, 4);

	tensor_t tens2 = tensor_element_to_element_function(tens, sqr, NULL);
	tensor_element_function(tens2, print, NULL);

	return 0;
}
