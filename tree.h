#pragma once
#include "treenode.h"
class Tree
{
	friend class Agent;
public:
	Tree(int8 depth);
	Tree(int8 depth, TreeNode* root);
	~Tree();
#ifdef MULTI_THREAD
	static void* CreateTree(void * arg);
	static void* DestroyTree(void * arg);
#else
	void CreateTree(TreeNode * root);
	void DestroyTree(TreeNode * root);
#endif

private:
	int8 _max_depth;
	TreeNode * _treeroot;
	float _findmax(TreeNode * root);//寻优函数
};
typedef struct
{
	TreeNode* root;
	int8 max_depth;//树的最大深度
}ARG;//给多线程版CreateTree函数传参所用结构体