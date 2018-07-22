#include <stdio.h>
#include <stdlib.h>

#include "cmd.h"
#include "log.h"


// 函数定义
EXEC_FUNC_DEFINE(ShowMeInfo);
EXEC_FUNC_DEFINE(SetLogCtrl);
EXEC_FUNC_DEFINE(TestBatch);
EXEC_FUNC_DEFINE(TestEndianOper);

int ExecExit(void)
{
    disp("==============\n");
    disp("命令行退出 ^_^\n");
    disp("==============\n");
    exit(0);
}