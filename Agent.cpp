#include "Agent.h"
#define TIMER
#ifdef TIMER
#include <ctime>
#endif

void Agent::Play(int play_time)
{
#ifdef TIMER
	long steps = 0;
	clock_t start = clock();
#endif
	for (loop_control i = 0; i < play_time; i++)
	{
		_treeroot->Clear();
		_treeroot->Initialize();
		while (!_treeroot->GameOver())
		{
#ifndef TIMER
			system("cls");
			_treeroot->Print();
#endif
			if (_treeroot->Move(_decide()))_treeroot->AddNum();
		}
#ifdef TIMER
		steps += _treeroot->GetSteps();
		_treeroot->ShortPrint(i + 1); //_treeroot->SaveToFile();
#endif
	}
#ifdef TIMER
	clock_t end = clock();
	printf("%d steps\n%.2f s\n%.0f sps\n", steps, (float)(end - start) / CLK_TCK, (float)steps*CLK_TCK / (end - start));
	system("pause");
#endif
}

int8 Agent::_decide()
{
	//寻找所有终端节点的最大值，并返回该节点的根方向。
	loop_control i = 0, j = 0;

	float evaltotalscore[4] = { -1.0F,-1.0F,-1.0F,-1.0F }, maxevalscore;/*V4.2.0.1M*/
	int16 evaltimes[4] = { 1,1,1,1 };/*V4.2.0.1M*/

	for (int16 k = 0; k < _simu_time; k++)
	{
		Tree tree(_max_depth, _treeroot);
		for (i = 0; i < 4; i++)
			if (_treeroot->_child[i] != nullptr)
			{
				evaltotalscore[i] += tree._findmax(_treeroot->_child[i]);
				evaltimes[i]++;
			}
	}
	for (i = 0; i < 4; i++)evaltotalscore[i] /= evaltimes[i];

	for (i = 1, j = 0, maxevalscore = evaltotalscore[0]; i < 4; i++)
		if (evaltotalscore[i] > maxevalscore)
		{
			maxevalscore = evaltotalscore[i];
			j = i;
		}

	return j + 1;
}