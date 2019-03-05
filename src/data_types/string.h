#ifndef __STRING_H__
#define __STRING_H__

typedef struct {
	char* _data;
	unsigned int _length;
} string_t;

void string_init(string_t* str);

void string_create(string_t* str, const char* c_str);

void string_create_n(string_t* str, const char* data, unsigned int n);

unsigned int string_length(string_t str);

const char* string_get_c_str(string_t str);

string_t string_concat(string_t str1, string_t str2);

string_t string_substr(string_t str, unsigned int i, unsigned int n);

string_t string_mult(string_t str, unsigned int n);

string_t string_invert(string_t str);

char string_char_at(string_t str, unsigned int i);

unsigned int string_find(string_t str, string_t pat);

unsigned int string_find_in(string_t str, string_t pat, unsigned int i, unsigned int n);

string_t string_copy(string_t str);

int string_cmp(string_t str1, string_t str2);

void string_free(string_t* str);

#endif
