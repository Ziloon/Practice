#include <assert.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

#include "log.h"
#include "shell.h"
#include "type.h"

// 全局变量
static char *gpstrInput = NULL; //终端输入字符串

static char *gpstrStrip = NULL; //剔除前端空格的输入字符串

static const char * const gstrPrompt = "myshell >> ";

static CMD_PROC gastCmdRegister[] = {
    // 退出命令，不区分大小写
    CMD_ENTRY("Quit", ExecExit),
    CMD_ENTRY("Q", ExecExit),
    CMD_ENTRY("Exit", ExecExit),
    CMD_ENTRY("End", ExecExit),
    CMD_ENTRY("E", ExecExit),
    CMD_ENTRY("Bye", ExecExit),
    CMD_ENTRY("B", ExecExit),

    // 函数命令
    CMD_REGISTER(ShowMeInfo),
    CMD_REGISTER(SetLogCtrl),
    CMD_REGISTER(TestBatch),
    CMD_REGISTER(TestEndianOper),

    // 命令结束
    CMD_ENTRY_END
};

static const int CMD_MAP_NUM = ELEMENT_NUM_OF(gastCmdRegister);

// 函数定义
EXEC_FUNC_DEFINE(ShowMeInfo);
EXEC_FUNC_DEFINE(SetLogCtrl);
EXEC_FUNC_DEFINE(TestBatch);
EXEC_FUNC_DEFINE(TestEndianOper);

int ExecExit(void)
{
    logInfo("命令行退出 ^_^\n");
    exit(0);
}

//返回gastCmdRegister中的CmdStr列(必须为只读字符串)，以供CmdGenerator使用
static char *GetCmdByIndex(unsigned int dwCmdIndex)
{
    if(dwCmdIndex >=  CMD_MAP_NUM)
        return NULL;
    return gastCmdRegister[dwCmdIndex].pszCmd;
}

//执行命令
static int ExecCmd(char *pszCmdLine)
{
    if(NULL == pszCmdLine)
        return -1;

    unsigned int dwCmdIndex = 0;
    for(; dwCmdIndex < CMD_MAP_NUM; dwCmdIndex++)
    {
        if(!strcmp(pszCmdLine, gastCmdRegister[dwCmdIndex].pszCmd))
            break;
    }
    if(CMD_MAP_NUM == dwCmdIndex)
        return -1;
    gastCmdRegister[dwCmdIndex].fpCmd(); //调用相应的函数

    return 0;
}

//剔除字符串首尾的空白字符(含空格)
static char *StripWhite(char *pszOrig)
{
    if(NULL == pszOrig)
        return "NUL";

    char *pszStripHead = pszOrig;
    while(isspace(*pszStripHead))
        pszStripHead++;

    if('\0' == *pszStripHead)
        return pszStripHead;

    char *pszStripTail = pszStripHead + strlen(pszStripHead) - 1;
    while(pszStripTail > pszStripHead && isspace(*pszStripTail))
        pszStripTail--;
    *(++pszStripTail) = '\0';

    return pszStripHead;
}

char *ReadCmdLine()
{
     //若已分配命令行缓冲区，则将其释放
    if(gpstrInput)
    {
        free(gpstrInput);
        gpstrInput = NULL;
    }
    //读取用户输入的命令行
    gpstrInput = readline(gstrPrompt);

    //剔除命令行首尾的空白字符。若剔除后的命令不为空，则存入历史列表
    gpstrStrip = StripWhite(gpstrInput);
    if(NULL != gpstrStrip 
        && NULL != *gpstrStrip)
    {
        add_history(gpstrStrip);
    }

    return gpstrStrip;
}

static char *CmdGenerator(const char *pszText, int dwState)
{
    static int dwListIdx = 0, dwTextLen = 0;
    if(!dwState)
    {
        dwListIdx = 0;
        dwTextLen = strlen(pszText);
    }

    //当输入字符串与命令列表中某命令部分匹配时，返回该命令字符串
    const char *pszName = NULL;
    while((pszName = GetCmdByIndex(dwListIdx)))
    {
        dwListIdx++;
        assert(pszName != NULL);
        if(!strncasecmp (pszName, pszText, dwTextLen))
            return strdup(pszName);
    }

    return NULL;
}

static char **CmdCompletion (const char *pszText, int dwStart, int dwEnd)
{
    //rl_attempted_completion_over = 1;
    char **pMatches = NULL;
    if(0 == dwStart)
        pMatches = rl_completion_matches(pszText, CmdGenerator);

    return pMatches;
}

//初始化Tab键能补齐的Command函数
static void InitReadLine(void)
{
    rl_attempted_completion_function = CmdCompletion;
}

int main(void)
{
    printf("Note: Welcome to Interactive Command!\n");
    printf("      Press 'Quit'/'Exit'/'End'/'Bye'/'Q'/'E'/'B' to quit!\n\n");
    InitReadLine();
    while(1)
    {//也可加入超时机制以免忘记退出
        char *pszCmdLine = ReadCmdLine();
        if (NULL == pszCmdLine)
        {
            continue;
        }
        ExecCmd(pszCmdLine);
    }

    return 0;
}
