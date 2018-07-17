#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "type.h"
#include "log.h"
#include "set.h"

int set_test()
{
    int i = 0;
    int e = 0;
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

    for(i = max_len; i > 0; i--)
    {
        append(&stS, i);
    }
    display(stS);

    logInfo("input delete element:\t");
    if (1 != scanf("%d", &e) )
    {
        return -1;
    }

    delete(&stS, e);
    display(stS);

    logInfo("input delete element:\t");
    if (1 != scanf("%d", &e) )
    {
        return -1;
    }

    append(&stS, e);
    display(stS);

    logDbg("stS %s full\n", is_full(stS) ? "is" : "isn't");
    logDbg("stS %s empty\n", is_empty(stS) ? "is" : "isn't");

    destory(&stS);
    display(stS);

    logDbg("stS %s full\n", is_full(stS) ? "is" : "isn't");
    logDbg("stS %s empty\n", is_empty(stS) ? "is" : "isn't");

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
            if (FALSE == s._flag[i])
            {
                printf("[%2d]%-8s ", i, "");
            }
            else
            {
                printf("[%2d]%-8d ", i, s.data[i]);
            }
        
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
    s->_flag = (BOOL *)malloc(sizeof(BOOL) * max_len);
    if (NULL == s->data)
    {
        logErr("s malloc data space fail.\r\n");
        return -1;
    }

    memset(s->data, 0, max_len * sizeof(int));
    memset(s->_flag, FALSE, max_len * sizeof(BOOL));
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

BOOL is_full(set s)
{
    if (s.len == s.max_len)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

BOOL is_empty(set s)
{
    if (0 == s.len)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

int find(set s, int e)
{
    for (int i = 0; i < s.max_len; ++i)
    {
        if (e == s.data[i])
        {
            return i;
        }
    }
    return -1;
}

int append(set *s, int e)
{
    int i = 0;

    if (TRUE == is_full(*s))
    {
        logErr("full set\n");
        return -1;
    }

    for (i = 0; i < s->max_len; ++i)
    {
        if (FALSE == s->_flag[i])
        {
            s->data[i] = e;
            s->_flag[i] = TRUE;
            s->len += 1;
            return i;
        }
    }

    return -1;
}

int delete(set *s, int e)
{
    int i = -1;

    if (TRUE == is_empty(*s))
    {
        return i;
    }

    i = find(*s, e);
    if (i >= 0)
    {
        s->data[i] = 0;
        s->_flag[i] = FALSE;
        s->len -= 1;
    }

    return i;
}