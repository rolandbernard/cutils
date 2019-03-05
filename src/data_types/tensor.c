
#include "tensor.h"

#include <stdlib.h>

static unsigned int tensor_get_memory_location(tensor_t tensor, const unsigned int* pos) {
	unsigned int ret = 0;
	unsigned int multiplier = 1;
	for(unsigned int i = 0; i < tensor._num_dim; i++) {
		ret += pos[i] * multiplier;
		multiplier *= tensor._size[i];
	}
	return ret;
}

static int tensor_inc_pos(tensor_t tensor, unsigned int* pos) {
	int ret = 0;
	pos[0]++;
	for(unsigned int i = 0; i < tensor._num_dim; i++) {
		if(pos[i] >= tensor._size[i]) {
			pos[i] = 0;
			if(i < tensor._num_dim-1)
				pos[i+1]++;
			else
				ret = 1;
		} else
			break;
	}
	return ret;
}

void tensor_init(tensor_t* tensor, unsigned int num_dim, const unsigned int* size) {
	tensor->_num_dim = num_dim;
	tensor->_size = (unsigned int*)malloc(num_dim * sizeof(unsigned int));
	unsigned int data_size = 1;
	for(unsigned int i = 0; i < num_dim; i++) {
		tensor->_size[i] = size[i];
		data_size *= size[i];
	}
	tensor->_data = (tensor_type_t*)malloc(data_size * sizeof(tensor_type_t));
}

void tensor_init_zero(tensor_t* tensor, unsigned int num_dim, const unsigned int* size) {
	tensor_init(tensor, num_dim, size);
	tensor_zero(*tensor);
}

void tensor_zero(tensor_t tensor) {
	unsigned int cur_pos[tensor._num_dim];
	for(unsigned int i = 0; i < tensor._num_dim; i++)
		cur_pos[i] = 0;
	unsigned int cur_data_pos = 0;
	do {
		tensor._data[cur_data_pos++] = 0;
	} while(!tensor_inc_pos(tensor, cur_pos));
}

void tensot_set(tensor_t tensor, const unsigned int* pos, tensor_type_t val) {
	unsigned int data_pos = tensor_get_memory_location(tensor, pos);
	tensor._data[data_pos] = val;
}

tensor_type_t tensor_get(tensor_t tensor, const unsigned int* pos) {
	unsigned int data_pos = tensor_get_memory_location(tensor, pos);
	return tensor._data[data_pos];
}

void tensor_element_function(tensor_t tensor, void (*func)(tensor_type_t, const unsigned int*, void*), void* user_data) {
	unsigned int cur_pos[tensor._num_dim];
	for(unsigned int i = 0; i < tensor._num_dim; i++)
		cur_pos[i] = 0;
	unsigned int cur_data_pos = 0;
	do {
		func(tensor._data[cur_data_pos], cur_pos, user_data);
		cur_data_pos++;
	} while(!tensor_inc_pos(tensor, cur_pos));
}

tensor_t tensor_element_to_element_function(tensor_t tensor, tensor_type_t (*func)(tensor_type_t, const unsigned int*, void*), void* user_data) {
	tensor_t ret;
	tensor_init(&ret, tensor._num_dim, tensor._size);
	unsigned int cur_pos[ret._num_dim];
	for(unsigned int i = 0; i < ret._num_dim; i++)
		cur_pos[i] = 0;
	unsigned int cur_data_pos = 0;
	do {
		ret._data[cur_data_pos] = func(tensor._data[cur_data_pos], cur_pos, user_data);
		cur_data_pos++;
	} while(!tensor_inc_pos(ret, cur_pos));
	return ret;
}

tensor_t tensor_tensor_to_element_function(tensor_t tensor, tensor_type_t (*func)(tensor_t, const unsigned int*, void*), unsigned int num_dest_dim, const unsigned int* dest_size, void* user_data) {
	tensor_t ret;
	tensor_init(&ret, num_dest_dim, dest_size);
	unsigned int cur_pos[ret._num_dim];
	for(unsigned int i = 0; i < ret._num_dim; i++)
		cur_pos[i] = 0;
	unsigned int cur_data_pos = 0;
	do {
		ret._data[cur_data_pos] = func(tensor, cur_pos, user_data);
		cur_data_pos++;
	} while(!tensor_inc_pos(ret, cur_pos));
	return ret;
}

void tensor_free(tensor_t* tensor) {
	if(tensor->_data != NULL)
		free(tensor->_data);
	tensor->_data = NULL;
	if(tensor->_size != NULL)
		free(tensor->_size);
	tensor->_size = NULL;
	tensor->_num_dim = 0;
}
