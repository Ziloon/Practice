#ifndef __SHELL_H__
#define __SHELL_H__

//命令结构体
typedef int (*CmdProcFunc)(void);

typedef struct{
    char         *pszCmd;
    CmdProcFunc  fpCmd;
}CMD_PROC;

#endif