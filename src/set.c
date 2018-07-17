#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "log.h"
#include "set.h"

int set_test()
{
    int max_len = 0;
    set stS;

    memset(&stS, 0, sizeof(stS));

    logInfo("please input max len of set:\t");
    
    if (1 != scanf("%d", &max_len) )
    {
        return -1;
    }

    init(&stS, max_len);
    display(stS);

    destory(&stS);
    display(stS);

    return 0;
}

int display(set s)
{
    int i = 0;
    printf("(%p): len %d, max len %d\n", &s, s.len, s.max_len);

    if (NULL != s.data)
    {
        printf("content(%p): \n", s.data);
        for (i = 0; i < s.max_len; ++i)
        {
            printf("[%2d]%-8d ", i, s.data[i]);
            if (3 == i % 4)
            {
                printf("\n");
            }
        }
        printf("\n");
    }
    else
    {
        printf("content null\n");
    }
    
    return 0;
}

int init(set *s, unsigned max_len)
{
    if (NULL != s->data)
    {
        logInfo("s data(%p)is already init, re-build.\r\n", s->data);
        destory(s);
    }

    s->data = (int *)malloc(sizeof(int) * max_len);
    if (NULL == s->data)
    {
        logErr("s malloc data space fail.\r\n");
        return -1;
    }

    memset(s->data, 0, max_len * sizeof(int));
    s->max_len = max_len;
    s->len = 0;

    return 0;
}

int destory(set *s)
{
    if (NULL != s->data)
    {
        free(s->data);
        s->data = NULL;
    }

    s->len = 0;
    s->max_len = 0;

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