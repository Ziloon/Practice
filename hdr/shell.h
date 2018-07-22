#ifndef __SHELL_H__
#define __SHELL_H__

//命令结构体
typedef int (*CmdProcFunc)(void);

typedef struct{
    char         *pszCmd;
    CmdProcFunc  fpCmd;
}CMD_PROC;

//命令表
#define CMD_ENTRY(cmdStr, func)     {cmdStr, func}
#define CMD_ENTRY_END               {NULL,   NULL}

#define EXEC_FUNC_DECLARATION(funcName)\
int funcName(void)

#define EXEC_FUNC_DEFINE(funcName) \
int funcName(void)\
{\
    printf("Enter "#funcName"!\n");\
    return 0;\
}

#endif