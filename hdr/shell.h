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
#define CMD_REGISTER(func)          CMD_ENTRY(#func, func)

#endif