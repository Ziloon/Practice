#ifndef __SHELL_H__
#define __SHELL_H__

//命令结构体
typedef int (*CmdProcFunc)(void);

typedef struct{
    char         *pszCmd;
    CmdProcFunc  fpCmd;
    BOOL bCaseSensitive;
}CMD_PROC;

//命令表
#define CMD_ENTRY(cmdStr, func, caseSensitive)     {cmdStr, func, caseSensitive}
#define CMD_REGISTER(func)          CMD_ENTRY(#func, func, TRUE)

#endif