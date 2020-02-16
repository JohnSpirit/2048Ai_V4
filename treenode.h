#pragma once
#include "board.h"
class TreeNode :public Board
{
	friend class Tree;
	friend class Agent;
public:
	TreeNode() :Board() {}
	TreeNode(const Board& origin);
	TreeNode(const TreeNode& origin, int8 dir);//由父节点和移动方向建立子节点
	~TreeNode() {};
	static float _weight[4];//权重值

private:
	int8 _depth = 0;//当前节点深度
	TreeNode* _root = nullptr;//当前节点的根节点
	TreeNode* _child[4] = { nullptr };//当前节点的四个子节点
	float _eval_score = 0.0F;//当前节点的综合评估值
	float _parameter[4] = { 0.0F };//当前节点的分立评估值

	void _eval();//评估函数
	void _qsort(COOR_DATA data[], int8 start, int8 end);//快排（未使用）
	int8 _adj(COOR * const coor1, COOR * const coor2);//是否相邻
	int8 _abs(int8 x);//绝对值
	float _abs(float x);//绝对值
};
