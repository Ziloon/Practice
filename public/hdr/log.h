#ifndef __LOG_H__
#define __LOG_H__

#define LOG_MODULE_MAX_NUM (100)

typedef enum
{
	LOG_LEV_NULL,
	LOG_LEV_DISP,
	LOG_LEV_ERROR,
	LOG_LEV_INFO,
	LOG_LEV_DEBUG,
	LOG_LEV_ALWAYS,
	LOG_LEV_LAST
} LOG_LEV_ENUM;

typedef struct
{
	char *pstrDesp;
	LOG_LEV_ENUM eLevel;
} LOG_NODE_STRU;

extern LOG_NODE_STRU gastLogLevelDespStr[LOG_LEV_LAST];

#define LOG_IMPORT(name, lev)            \
	static LOG_NODE_STRU _s_geLogCfg = { \
		.pstrDesp = name,                \
		.eLevel = lev};

#define LOG_SETLEV(lev)           \
	do                            \
	{                             \
		_s_geLogCfg.eLevel = lev; \
	} while (0)

#define disp(fmt, arg...)   \
	do                      \
	{                       \
		printf(fmt, ##arg); \
	} while (0)

#define log(lev, fmt, arg...)                                                                        \
	do                                                                                               \
	{                                                                                                \
		if (lev < _s_geLogCfg.eLevel)                                                                \
		{                                                                                            \
			printf("[%s][%s:%d]" fmt, gastLogLevelDespStr[lev].pstrDesp, __func__, __LINE__, ##arg); \
			fflush(NULL);                                                                            \
		}                                                                                            \
	} while (0)

#define logErr(fmt, arg...)             \
	do                                  \
	{                                   \
		log(LOG_LEV_ERROR, fmt, ##arg); \
	} while (0)

#define logInfo(fmt, arg...)           \
	do                                 \
	{                                  \
		log(LOG_LEV_INFO, fmt, ##arg); \
	} while (0)

#define logDbg(fmt, arg...)             \
	do                                  \
	{                                   \
		log(LOG_LEV_DEBUG, fmt, ##arg); \
	} while (0)

#endif