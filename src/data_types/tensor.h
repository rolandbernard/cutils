// Copyright (c) 2019 Roland Bernard

#ifndef __TENSOR_H__
#define __TENSOR_H__

#define TENSOR_TYPE double
typedef TENSOR_TYPE tensor_type_t;

typedef struct {
	unsigned int _num_dim;
	unsigned int* _size;
	tensor_type_t* _data;
} tensor_t;

void tensor_init(tensor_t* tensor, unsigned int num_dim, const unsigned int* size);

void tensor_init_zero(tensor_t* tensor, unsigned int num_dim, const unsigned int* size);

void tensor_zero(tensor_t tensor);

void tensot_set(tensor_t tensor, const unsigned int* pos, tensor_type_t val);

tensor_type_t tensor_get(tensor_t tensor, const unsigned int* pos);

void tensor_element_function(tensor_t tensor, void (*func)(tensor_type_t, const unsigned int*, void*), void* user_data);

tensor_t tensor_element_to_element_function(tensor_t tensor, tensor_type_t (*func)(tensor_type_t, const unsigned int*, void*), void* user_data);

tensor_t tensor_tensor_to_element_function(tensor_t tensor, tensor_type_t (*func)(tensor_t, const unsigned int*, void*), unsigned int num_dest_dim, const unsigned int* dest_size, void* user_data);

void tensor_free(tensor_t* tensor);

#endif
