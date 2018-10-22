#ifndef __ERROR_H__
#define __ERROR_H__

typedef struct {
	const char* msg;
} error_t;

#define assert(COND) (assert_msg( COND, #COND ))
#define assert_w_msg(COND,MSG) (assert_msg( COND, #COND " -> " #MSG ))

void assert_msg(int cond, const char* msg);

#endif
