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
	float _findmax(TreeNode * root);
};
typedef struct
{
	TreeNode* root;
	int8 max_depth;
}ARG;