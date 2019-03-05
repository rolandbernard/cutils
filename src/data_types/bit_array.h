// Copyright (c) 2019 Roland Bernard

#ifndef __BIT_ARRAY_H__
#define __BIT_ARRAY_H__

#define bits_to_bytes(x) ((x + 7) / 8)

typedef struct {
	unsigned char* _data;
	unsigned int _size;
} bit_array_t;

void bit_array_init(bit_array_t* array, unsigned int size);

void bit_array_set(bit_array_t array, unsigned int index, unsigned char val);

unsigned char bit_array_get(bit_array_t array, unsigned int index);

void bit_array_resize(bit_array_t* array, unsigned int new_size);

void bit_array_free(bit_array_t* array);

#endif
