#include "log.h"
#include "type.h"

#ifndef __CHECK_H__
#define __CHECK_H__

#define check_pointer(p)\
do\
{\
	if (NULL == p)\
	{\
		logErr("%s is null", #p);\
		return RET_NULL_POINTER;\
	}\
} while (0)

#endif