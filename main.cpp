/*
2048 SuperRun V4.x
Copyright @JSY 2019-2020, All Rights Reserved.
----V4.2.0.2 2020.2.15

���뻷����VS2017 x86
Ԥ��������
CRT_SECURE_NO_WARNINGS;
MULTI_THREAD;�����߳�ʱʹ�ã�
HAVE_STRUCT_TIMESPEC;
%(PreprocessorDefinitions)

*/

#include "Agent.h"

int main(void)
{
	Agent v4_2(4, 32);//ʵ����Agent���趨�������=4��ģ�����=4
	v4_2.Play(1);//����1��
	return 0;
}