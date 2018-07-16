#include <stdio.h>
#include <stdlib.h>
#include "log.h"
#include "set.h"

int init(set s, unsigned max_len)
{
    if (NULL != s.data)
    {
        logInfo("s is already init, re-build.\r\n");
        destory(s);
    }

    s.data = (int *)malloc(sizeof(int) * max_len);
    if (NULL == s.data)
    {
        logErr("s malloc data space fail.\r\n");
        return -1;
    }

    s.max_len = max_len;
    s.len = 0;

    return 0;
}

int destory(set s)
{
    if (NULL != s.data)
    {
        free(s.data);
        s.data = NULL;
    }

    s.len = 0;
    s.max_len = 0;

    return 0;
}

int add(set s, int e)
{
    return 0;
}

int find(set s, int e)
{
    return 0;
}

int del(set s, int e)
{
    return 0;
}