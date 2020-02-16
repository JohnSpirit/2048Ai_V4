/*
2048 SuperRun V4.x
Copyright @JSY 2019-2020, All Rights Reserved.
----V4.2.0.2 2020.2.15

编译环境：VS2017 x86
预处理器：
CRT_SECURE_NO_WARNINGS;
MULTI_THREAD;（多线程时使用）
HAVE_STRUCT_TIMESPEC;
%(PreprocessorDefinitions)

*/

#include "Agent.h"

int main(void)
{
	Agent v4_2(4, 32);//实例化Agent，设定搜索深度=4，模拟次数=4
	v4_2.Play(1);//运行1局
	return 0;
}