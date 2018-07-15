#ifndef __LOG_H__
#define __LOG_H__

#define log(lev, fmt, arg ...)\
do {\
	printf("[%s][%s:%d]"fmt, lev, __func__, __LINE__, ##arg);\
	fflush(NULL);\
} while (0)

#define logErr(fmt, arg ...)\
do {\
	log("ERROR", fmt, ##arg);\
} while (0)

#define logInfo(fmt, arg ...)\
do {\
	log("INFO", fmt, ##arg);\
} while (0)

#define logDbg(fmt, arg ...)\
do {\
	log("DEBUG", fmt, ##arg);\
} while (0)

#endif