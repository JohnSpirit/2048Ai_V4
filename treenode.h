#pragma once
#include "board.h"
class TreeNode :public Board
{
	friend class Tree;
	friend class Agent;
public:
	TreeNode() :Board() {}
	TreeNode(const Board& origin);
	TreeNode(const TreeNode& origin, int8 dir);
	~TreeNode() {};
	static float _weight[4];

private:
	int8 _depth = 0;
	TreeNode* _root = nullptr;
	TreeNode* _child[4] = { nullptr };
	float _eval_score = 0.0F;
	float _parameter[4] = { 0.0F };

	void _eval();
	void _qsort(COOR_DATA data[], int8 start, int8 end);
	int8 _adj(COOR * const coor1, COOR * const coor2);
	int8 _abs(int8 x);
	float _abs(float x);
};
