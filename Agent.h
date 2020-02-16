#pragma once
#include "tree.h"
class Agent
{
public:
	Agent(int8 depth, int16 simu_time) :_max_depth(depth), _simu_time(simu_time)
	{
		//srand(time(0) + clock());
		srand(0);
		_treeroot = new TreeNode();
	}
	~Agent()
	{
		delete _treeroot;
	}
	void Play(int play_time);
private:
	int8 _decide();

	int8 _max_depth;
	int16 _simu_time;
	TreeNode * _treeroot;
};