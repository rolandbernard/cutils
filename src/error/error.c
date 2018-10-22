
#include "error.h"

#include <stdio.h>
#include <stdlib.h>

void assert_msg(int cond, const char* msg) {
	if(!cond) {
		fprintf(stderr, "[[assertion failed] (%s)]\n", msg);
		abort();
	}
}
