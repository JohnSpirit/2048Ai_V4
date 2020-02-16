#pragma once
#include "board.h"
class TreeNode :public Board
{
	friend class Tree;
	friend class Agent;
public:
	TreeNode() :Board() {}
	TreeNode(const Board& origin);
	TreeNode(const TreeNode& origin, int8 dir);//�ɸ��ڵ���ƶ��������ӽڵ�
	~TreeNode() {};
	static float _weight[4];//Ȩ��ֵ

private:
	int8 _depth = 0;//��ǰ�ڵ����
	TreeNode* _root = nullptr;//��ǰ�ڵ�ĸ��ڵ�
	TreeNode* _child[4] = { nullptr };//��ǰ�ڵ���ĸ��ӽڵ�
	float _eval_score = 0.0F;//��ǰ�ڵ���ۺ�����ֵ
	float _parameter[4] = { 0.0F };//��ǰ�ڵ�ķ�������ֵ

	void _eval();//��������
	void _qsort(COOR_DATA data[], int8 start, int8 end);//���ţ�δʹ�ã�
	int8 _adj(COOR * const coor1, COOR * const coor2);//�Ƿ�����
	int8 _abs(int8 x);//����ֵ
	float _abs(float x);//����ֵ
};
