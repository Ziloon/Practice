#ifndef __TYPE_H__
#define __TYPE_H__

typedef enum
{
	FALSE,
	TRUE
} BOOL;

#define ELEMENT_NUM_OF(array) (sizeof(array) / sizeof(array[0]))

#endif