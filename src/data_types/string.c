// Copyright (c) 2019 Roland Bernard

#include "string.h"

#include <stdlib.h>

void string_init(string_t* str) {
	str->_data = NULL;
	str->_length = 0;
}

void string_create(string_t* str, const char* c_str) {
	if(str->_data != NULL)
		free(str->_data);
	str->_length = 0;
	while(c_str[str->_length] != '\0') str->_length++;
	str->_data = (char*)malloc((str->_length + 1) * sizeof(char));
	str->_data[str->_length] = '\0';
	for(unsigned int i = 0; i < str->_length; i++)
		str->_data[i] = c_str[i];
}

void string_create_n(string_t* str, const char* data, unsigned int n) {
	if(str->_data != NULL)
		free(str->_data);
	str->_length = n;
	str->_data = (char*)malloc((n + 1) * sizeof(char));
	str->_data[n] = '\0';
	for(unsigned int i = 0; i < n; i++)
		str->_data[i] = data[i];
}

unsigned int string_length(string_t str) {
	return str._length;
}

const char* string_get_c_str(string_t str) {
	return str._data;
}

string_t string_concat(string_t str1, string_t str2) {
	string_t ret;
	ret._length = str1._length + str2._length;
	ret._data = (char*)malloc((ret._length + 1) * sizeof(char));
	ret._data[ret._length] = '\0';
	for(unsigned int i = 0; i < str1._length; i++)
		ret._data[i] = str1._data[i];
	for(unsigned int i = 0; i < str2._length; i++)
		ret._data[str1._length + i] = str2._data[i];
	return ret;
}

string_t string_substr(string_t str, unsigned int i, unsigned int n) {
	string_t ret;
	if(str._length < i + n) {
		ret._data = NULL;
		ret._length = 0;
	} else {
		ret._length = n;
		ret._data = (char*)malloc((n + 1) * sizeof(char));
		ret._data[n] = '\0';
		for(unsigned int j = 0; j < n; j++)
			ret._data[j] = str._data[i + j];
	}
	return ret;
}

string_t string_mult(string_t str, unsigned int n) {
	string_t ret;
	ret._length = str._length * n;
	ret._data = (char*)malloc((ret._length + 1) * sizeof(char));
	ret._data[ret._length] = '\0';
	for(unsigned int i = 0; i < n; i++)
		for(unsigned int j = 0; j < str._length; j++)
			ret._data[i * str._length + j] = str._data[j];
	return ret;
}

string_t string_invert(string_t str) {
	string_t ret;
	ret._length = str._length;
	ret._data = (char*)malloc((str._length + 1) * sizeof(char));
	ret._data[ret._length] = '\0';
	for(unsigned int i = 0; i < ret._length; i++)
		ret._data[i] = str._data[ret._length - 1 - i];
	return ret;
}

char string_char_at(string_t str, unsigned int i) {
	return str._data[i];
}

unsigned int string_find(string_t str, string_t pat) {
	for(unsigned int i = 0; i <= str._length - pat._length; i++) {
		int temp = 1;
		for(unsigned int j = 0; temp && j < pat._length; j++)
			if(str._data[i + j] != pat._data[j])
				temp = 0;
		if(temp)
			return i;
	}
	return ~0;
}

unsigned int string_find_in(string_t str, string_t pat, unsigned int ii, unsigned int n) {
	if(str._length < ii + n || pat._length > n)
		return ~0;
	else {
		for(unsigned int i = ii; i <= ii + n - pat._length; i++) {
			int temp = 1;
			for(unsigned int j = 0; temp && j < pat._length; j++)
				if(str._data[i + j] != pat._data[j])
					temp = 0;
			if(temp)
				return i;
		}
		return ~0;
	}
}

string_t string_copy(string_t str) {
	string_t ret;
	ret._length = str._length;
	ret._data = (char*)malloc((ret._length + 1) * sizeof(char));
	ret._data[ret._length] = '\0';
	for(unsigned int i = 0; i < ret._length; i++)
		ret._data[i] = str._data[i];
	return ret;
}

int string_cmp(string_t str1, string_t str2) {
	for(unsigned int i = 0; i <= str1._length && i <= str2._length; i++)
		if(str1._data[i] < str2._data[i])
			return -1;
		else if(str1._data[i] > str2._data[i])
			return 1;
	return 0;
}

void string_free(string_t* str) {
	if(str->_data != NULL)
		free(str->_data);
	str->_data = NULL;
	str->_length = 0;
}
