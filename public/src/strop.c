#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "check.h"
#include "log.h"
#include "type.h"

LOG_IMPORT("String", LOG_LEV_INFO);

int StringSplit(char *pstrIn, char sign, char *astrOut, int slStrlenMax, int slStrCntMax, int *pslCnt)
{
	int slIdx = 0;
	int slStrIdx = 0;

	check_pointer(pstrIn);
	check_pointer(pslCnt);
	memset(astrOut, '\0', sizeof(astrOut[0]) * slStrlenMax * slStrCntMax);

	if (0 == strcmp("", pstrIn))
	{
		(*pslCnt) = 1;
		return RET_OK;
	}

	slIdx = 0;
	slStrIdx = 0;
	*pslCnt = 0;
	do
	{
		assert(*pslCnt < slStrCntMax);
		assert(slStrlenMax < slStrlenMax);
		if (sign == pstrIn[slIdx])
		{
			slStrIdx = 0;
			*pslCnt += 1;
		}
		else
		{
			*(astrOut + (*pslCnt) * slStrlenMax + slStrIdx) = pstrIn[slIdx];
			slStrIdx += 1;
		}

		slIdx += 1;
	} while(pstrIn[slIdx] != '\0');

	return RET_OK;
}