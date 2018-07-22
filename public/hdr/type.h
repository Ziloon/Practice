#ifndef __TYPE_H__
#define __TYPE_H__

typedef enum
{
	FALSE,
	TRUE
} BOOL;

typedef enum
{
	RET_OK = 0,
	RET_NULL_POINTER,
	RET_INVALID_PARA,
	RET_EXEC_FAIL
} ENUM_RET_VAL;

#define ELEMENT_NUM_OF(array) (sizeof(array) / sizeof(array[0]))

#endif