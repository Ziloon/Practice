#include <assert.h>
#include <ctype.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "check.h"
#include "cmd.h"
#include "log.h"
#include "shell.h"
#include "type.h"

// 全局变量

static const char * const gstrPrompt = "myshell >> ";

static CMD_PROC gastCmdRegister[] = {
    // 退出命令，不区分大小写
    CMD_ENTRY("Quit", ExecExit, FALSE),
    CMD_ENTRY("Q", ExecExit, FALSE),
    CMD_ENTRY("Exit", ExecExit, FALSE),
    CMD_ENTRY("End", ExecExit, FALSE),
    CMD_ENTRY("E", ExecExit, FALSE),
    CMD_ENTRY("Bye", ExecExit, FALSE),
    CMD_ENTRY("B", ExecExit, FALSE),

    // 函数命令
    CMD_REGISTER(ShowMeInfo),
    CMD_REGISTER(SetLogCtrl),
    CMD_REGISTER(TestBatch),
    CMD_REGISTER(TestEndianOper)
};

static const int CMD_MAP_NUM = ELEMENT_NUM_OF(gastCmdRegister);

//剔除字符串首尾的空白字符(含空格)
static char *StripString(char *pstrInput)
{
    int slLen = -1;
    int slHead = 0; // 第一个非space字符位置
    int slTail = 0; // 第一个字符串结束符\0位置

    if (NULL == pstrInput)
    {
        return NULL;
    }
    else
    {
        slLen = strlen(pstrInput);
        logDbg("input len is %d\n", slLen);
    }


    // 判断输入字符串长度，空串返回NULL；非空串设定有效范围。
    if (strlen("") == slLen)
    {
        // 空字符串，非法，返回NULL
        logDbg("empty string.\n");
        return NULL;
    }
    else
    {
        slHead = 0;
        slTail = slLen;
        logDbg("set range [%d, %d]\n", slHead, slTail);
    }

    // 排除space字符，当head == tail时，表示遍历完整个字符串为space。返回NULL。
    // 当head字符为space时，前进，最差会停止在\0字符
    while(isspace(pstrInput[slHead]))
    {
        logDbg("[%d]'%c'\n",slHead, pstrInput[slHead]);
        slHead += 1;
    }
    if (slHead == slTail)
    {
        // 全space串
        return NULL;
    }

    // 由于到此满足head < tail，所以输入为非全space字符串，所以只需要排除字符串尾部的space即可，将space字符置\0。结束条件就是遇到第一个非space字符。
    while(isspace(pstrInput[slTail-1]))
    {
        logDbg("[%d]'%c' set as '\\0'\n",slTail-1, pstrInput[slTail-1]);
        pstrInput[--slTail] = '\0';
    }

    logDbg("out: \"%s\"\n", pstrInput + slHead);
    return (pstrInput + slHead);
}

//返回gastCmdRegister中的CmdStr列(必须为只读字符串)，以供CmdGenerator使用
static char *GetCmdByIndex(unsigned int ulIdx)
{
    if(ulIdx <  CMD_MAP_NUM)
    {
        return gastCmdRegister[ulIdx].pszCmd;
    }
    else
    {
        return NULL;
    }
}

//执行命令
static int ExecCmd(char *pstrCmd)
{
    unsigned int ulIdx = 0;
    int (*cmp)(const char *s1, const char *s2);

    check_pointer(pstrCmd);

    logDbg("input is \"%s\"\n", pstrCmd);

    for(ulIdx = 0; ulIdx < CMD_MAP_NUM; ulIdx++)
    {
        if (TRUE == gastCmdRegister[ulIdx].bCaseSensitive)
        {
            cmp = strcmp;
        }
        else
        {
            cmp = strcasecmp;
        }

        if(0 == cmp(pstrCmd, gastCmdRegister[ulIdx].pszCmd))
        {
            gastCmdRegister[ulIdx].fpCmd(); //调用相应的函数
            return RET_OK;
        }
    }

    disp("### 没有这个命令\n");
    return RET_EXEC_FAIL;
}

int ReadCmdLine(char **ppstrCmd)
{
    char *pstrInput = NULL;

    if (NULL != *ppstrCmd)
    {
        free(*ppstrCmd);
        *ppstrCmd = NULL;
    }

    //读取用户输入的命令行
    pstrInput = readline(gstrPrompt);
    logDbg("get input \"%s\"\n", pstrInput);

    //剔除命令行首尾的空白字符。若剔除后的命令不为空，则存入历史列表
    *ppstrCmd = StripString(pstrInput);
    logDbg("strip input \"%s\"\n", *ppstrCmd);

    if(NULL == *ppstrCmd)
    {
        return RET_EXEC_FAIL;
    }

    add_history(*ppstrCmd);
    return RET_OK;
}

static char *CmdGenerator(const char *pstrText, int slState)
{
    static int s_slIdx = 0;
    static int s_slInputLen = 0;
    const char *pstrMatchItem = NULL;
    static const char *s_pstrInput = NULL;

    if (NULL == pstrText)
    {
        return NULL;
    }

    if(!slState)
    {
        s_slIdx = 0;
        s_pstrInput = pstrText;
        s_slInputLen = strlen(s_pstrInput);
    }

    //当输入字符串与命令列表中某命令部分匹配时，返回该命令字符串
    while((pstrMatchItem = GetCmdByIndex(s_slIdx++)))
    {
        assert(pstrMatchItem != NULL);
        if(0 == strncasecmp(pstrMatchItem, s_pstrInput, s_slInputLen))
        {
            return strdup(pstrMatchItem);
        }
    }

    return NULL;
}

static char **CmdCompletion (const char *pstrText, int slStart, int slEnd)
{
    //rl_attempted_completion_over = 1;
    char **apMatcheItems = NULL;
    if(0 == slStart)
        apMatcheItems = rl_completion_matches(pstrText, CmdGenerator);

    return apMatcheItems;
}

//初始化Tab键能补齐的Command函数
static int InitReadLine()
{
    rl_attempted_completion_function = CmdCompletion;
    return RET_OK;
}

int main(void)
{
    int slRet = 0;
    char *pstrCmdLine = NULL;

    disp("=========================================\n");
    disp("欢迎使用 shell 工具\n");
    disp("-----------------------------------------\n");
    disp("若要退出，请输入：\n\t'Quit'/'Exit'/'End'/'Bye'/'Q'/'E'/'B'\n\n");
    InitReadLine();
    while(1)
    {
        slRet = ReadCmdLine(&pstrCmdLine);
        if (RET_OK != slRet)
        {
            logDbg("读取命令错误 %#8X\n", slRet);
            continue;
        }
        else
        {
            logDbg("读取命令为 \"%s\"\n", pstrCmdLine);
        }

        if (NULL == pstrCmdLine)
        {
            logDbg("没有读到命令\n");
            continue;
        }
        else
        {
            logDbg("返回命令为 \"%s\"\n", pstrCmdLine);
        }

        
        slRet = ExecCmd(pstrCmdLine);
        if (RET_OK != slRet)
        {
            logDbg("执行命令错误 %#8X\n", slRet);
        }

        free(pstrCmdLine);
        pstrCmdLine = NULL;
    }

    return RET_OK;
}
