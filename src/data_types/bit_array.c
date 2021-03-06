// Copyright (c) 2019 Roland Bernard

#include "bit_array.h"

#include <stdlib.h>

void bit_array_init(bit_array_t* array, unsigned int size) {
	unsigned int size_bytes = bits_to_bytes(size);

	array->_size = size;
	array->_data = (unsigned char*)malloc(size_bytes);
}

void bit_array_init_zero(bit_array_t* array, unsigned int size) {
	unsigned int size_bytes = bits_to_bytes(size);

	array->_size = size;
	array->_data = (unsigned char*)malloc(size_bytes);

	for(int i = 0; i < size_bytes; i++)
		array->_data[i] = 0x00;
}

void bit_array_set(bit_array_t array, unsigned int index, unsigned char val) {
	if(val)
		array._data[index / 8] |= 1 << (index%8);
	else
		array._data[index / 8] &= ~(1 << (index%8));

}

unsigned char bit_array_get(bit_array_t array, unsigned int index) {
	return (array._data[index / 8] >> (index%8)) & 0x01;
}

void bit_array_resize(bit_array_t* array, unsigned int new_size) {
	unsigned int new_size_bytes = bits_to_bytes(new_size);
	unsigned int size_bytes = bits_to_bytes(array->_size);

	if(new_size_bytes != size_bytes) {
		array->_size = new_size;
		array->_data = (unsigned char*)realloc(array->_data, new_size_bytes);
	}
}

void bit_array_resize_zero(bit_array_t* array, unsigned int new_size) {
	unsigned int new_size_bytes = bits_to_bytes(new_size);
	unsigned int size_bytes = bits_to_bytes(array->_size);

	if(new_size_bytes != size_bytes) {
		array->_data = (unsigned char*)realloc(array->_data, new_size_bytes);

		for(int i = array->_size; i < size_bytes*8; i++)
			bit_array_set(*array, i, 0);
		for(int i = size_bytes; i < new_size_bytes; i++)
			array->_data[i] = 0x00;
		
		array->_size = new_size;
	}
}

void bit_array_free(bit_array_t* array) {
	if(array->_data != NULL) {
		free(array->_data);
		array->_data = NULL;
		array->_size = 0;
	}
}
