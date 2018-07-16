#ifndef __SET_H__
#define __SET_H__

typedef struct
{
	unsigned int len;
	unsigned int max_len;
	int *data;
} set;

int init(set s, unsigned max_len);
int destory(set s);
int add(set s, int e);
int find(set s, int e);
int del(set s, int e);

#endif