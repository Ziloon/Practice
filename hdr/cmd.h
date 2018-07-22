#ifndef __CMD_H__
#define __CMD_H__

#define EXEC_FUNC_DECLARATION(funcName)\
int funcName(void)

#define EXEC_FUNC_DEFINE(funcName) \
int funcName(void)\
{\
    disp("==============\n");\
    disp("进入函数 %s 运行\n", #funcName);\
    disp("…… …… ……\n");\
    disp("==============\n");\
    return 0;\
}

// 函数声明
EXEC_FUNC_DECLARATION(ShowMeInfo);
EXEC_FUNC_DECLARATION(SetLogCtrl);
EXEC_FUNC_DECLARATION(TestBatch);
EXEC_FUNC_DECLARATION(TestEndianOper);
EXEC_FUNC_DECLARATION(ExecExit);


#endif