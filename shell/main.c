#include <readline/readline.h>
#include <readline/history.h>
#include <assert.h>

#include "type.h"
#include "shell.h"

static char *pszLineRead = NULL;  //终端输入字符串
static char *pszStripLine = NULL; //剔除前端空格的输入字符串
static const char * const pszCmdPrompt = "myshell >> ";

#define MOCK_FUNC_DECLARATION(funcName)\
int funcName(void)

#define MOCK_FUNC_DEFINE(funcName) \
int funcName(void)\
{\
    printf("Enter "#funcName"!\n");\
    return 0;\
}

MOCK_FUNC_DECLARATION(ShowMeInfo);
MOCK_FUNC_DECLARATION(SetLogCtrl);
MOCK_FUNC_DECLARATION(TestBatch);
MOCK_FUNC_DECLARATION(TestEndianOper);

//命令表
#define CMD_ENTRY(cmdStr, func)     {cmdStr, func}
#define CMD_ENTRY_END               {NULL,   NULL}

static CMD_PROC gCmdMap[] = {
    CMD_ENTRY("ShowMeInfo",       ShowMeInfo),
    CMD_ENTRY("SetLogCtrl",       SetLogCtrl),
    CMD_ENTRY("TestBatch",        TestBatch),
    CMD_ENTRY("TestEndian",       TestEndianOper),
    CMD_ENTRY_END
};

static const char *pszQuitCmd[] = {
    "Quit", 
    "Exit", 
    "End", 
    "Bye", 
    "Q", 
    "E", 
    "B"
};

static const int CMD_MAP_NUM = ELEMENT_NUM_OF(gCmdMap);
static const int QUIT_CMD_NUM = ELEMENT_NUM_OF(pszQuitCmd);

MOCK_FUNC_DEFINE(ShowMeInfo);
MOCK_FUNC_DEFINE(SetLogCtrl);
MOCK_FUNC_DEFINE(TestBatch);
MOCK_FUNC_DEFINE(TestEndianOper);

//返回gCmdMap中的CmdStr列(必须为只读字符串)，以供CmdGenerator使用
static char *GetCmdByIndex(unsigned int dwCmdIndex)
{
    if(dwCmdIndex >=  CMD_MAP_NUM)
        return NULL;
    return gCmdMap[dwCmdIndex].pszCmd;
}

//执行命令
static int ExecCmd(char *pszCmdLine)
{
    if(NULL == pszCmdLine)
        return -1;

    unsigned int dwCmdIndex = 0;
    for(; dwCmdIndex < CMD_MAP_NUM; dwCmdIndex++)
    {
        if(!strcmp(pszCmdLine, gCmdMap[dwCmdIndex].pszCmd))
            break;
    }
    if(CMD_MAP_NUM == dwCmdIndex)
        return -1;
    gCmdMap[dwCmdIndex].fpCmd(); //调用相应的函数

    return 0;
}

//退出交互式调测器的命令(不区分大小写)
static BOOL IsUserQuitCmd(char *pszCmd)
{
    int idx = 0;
    for(idx = 0; idx < QUIT_CMD_NUM; idx++)
    {
        if(!strcasecmp(pszCmd, pszQuitCmd[idx]))
            return TRUE;
    }

    return FALSE;
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
    if(pszLineRead)
    {
        free(pszLineRead);
        pszLineRead = NULL;
    }
    //读取用户输入的命令行
    pszLineRead = readline(pszCmdPrompt);

    //剔除命令行首尾的空白字符。若剔除后的命令不为空，则存入历史列表
    pszStripLine = StripWhite(pszLineRead);
    if(NULL != pszStripLine 
        && NULL != *pszStripLine)
    {
        add_history(pszStripLine);
    }

    return pszStripLine;
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
        if(!strncmp (pszName, pszText, dwTextLen))
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
        if(IsUserQuitCmd(pszCmdLine))
        {
            free(pszLineRead);
            break;
        }

        ExecCmd(pszCmdLine);
    }

    return 0;
}
