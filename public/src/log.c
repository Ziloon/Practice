#include "log.h"

LOG_NODE_STRU gastLogLevelDespStr[LOG_LEV_LAST] = 
{
	{"NULL", LOG_LEV_NULL},
	{"DISP", LOG_LEV_DISP},
	{"ERROR", LOG_LEV_ERROR},
	{"INFO", LOG_LEV_INFO},
	{"DEBUG", LOG_LEV_DEBUG},
	{"ALWAYS", LOG_LEV_ALWAYS},
};