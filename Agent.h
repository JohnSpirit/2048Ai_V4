#pragma once
#include "tree.h"
class Agent
{
public:
	Agent(int8 depth, int16 simu_time) :_max_depth(depth), _simu_time(simu_time)
	{
		//srand(time(0) + clock());
		srand(0);//初始化种子，取0是为了检测运行效果
		_treeroot = new TreeNode();//建立树根
	}
	~Agent()
	{
		delete _treeroot;//删除树根
	}
	void Play(int play_time);
private:
	int8 _decide();//选择最佳方向

	int8 _max_depth;//最大深度
	int16 _simu_time;//模拟次数
	TreeNode * _treeroot;//树根
};