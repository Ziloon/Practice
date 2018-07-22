#include "type.h"

#ifndef __SET_H__
#define __SET_H__

#define SET_NAN	(0x8FFFFFFF)
typedef struct
{
	unsigned int len;
	unsigned int max_len;
	int *data;
	BOOL *_flag;
} set;

int init(set *s, unsigned max_len);
int destory(set *s);
int append(set *s, int e);
int delete(set *s, int e);
int find(set s, int e);
BOOL is_full(set s);
BOOL is_empty(set s);
int set_test();
int display(set s);

#endif