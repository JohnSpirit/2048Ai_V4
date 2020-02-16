#include "treenode.h"
#include "tree.h"

Tree::Tree(int8 depth) :_max_depth(0) ,_treeroot(nullptr){}

#ifdef MULTI_THREAD
Tree::Tree(int8 depth, TreeNode * root) : _max_depth(depth), _treeroot(root)
{
	ARG arg = { root,_max_depth };
	CreateTree(&arg);
}

Tree::~Tree()
{
	DestroyTree(_treeroot);
}

void* Tree::CreateTree(void* arg)
{
	ARG* ptr = (ARG*)arg;
	pthread_t dir[4];
	ARG newarg;
	if (ptr->root == nullptr || ptr->root->_depth == ptr->max_depth)return NULL;

	newarg.max_depth = ptr->max_depth;

	for (loop_control i = 0; i < 4; i++)
	{
		ptr->root->_child[i] = new TreeNode(*ptr->root, i + 1);
		if (ptr->root->_child[i]->_depth == -1) { delete ptr->root->_child[i]; ptr->root->_child[i] = nullptr; }
		else
		{
			newarg.root = ptr->root->_child[i];
			/*if (ptr->root->_depth == 0)pthread_create(dir + i, NULL, Tree::CreateTree, &newarg);
			else */CreateTree(&newarg);

		}
	}
	//if (ptr->root->_depth == 0)
	//	for (loop_control i = 0; i < 4; i++)
	//		if (ptr->root->_child[i] != nullptr)
	//			pthread_join(dir[i], NULL);
	return NULL;
}

void* Tree::DestroyTree(void* arg)
{
	TreeNode* root = (TreeNode*)arg;
	pthread_t dir[4];
	//注意：初始节点root不会被销毁。
	if (root == nullptr)return NULL;

	for (loop_control i = 0; i < 4; i++)
	{
		/*if (root->_depth == 0)
			pthread_create(dir + i, NULL, Tree::DestroyTree, root->_child[i]);
		else  */
		{
			DestroyTree(root->_child[i]); 
			delete root->_child[i];
		}
	}
	//if (root->_depth == 0)
	//	for (loop_control i = 0; i < 4; i++)
	//	{
	//		pthread_join(dir[i], NULL);
	//		delete root->_child[i];
	//	}
	return NULL;
}
#else
Tree::Tree(int8 depth, TreeNode * root) : _max_depth(depth), _treeroot(root)
{
	CreateTree(_treeroot);
}

Tree::~Tree()
{
	DestroyTree(_treeroot);
}
void Tree::CreateTree(TreeNode* root)
{
	if (root == nullptr || root->_depth == this->_max_depth)return;

	for (loop_control i = 0; i < 4; i++)
	{
		root->_child[i] = new TreeNode(*root, i + 1);
		if (root->_child[i]->_depth == -1) { delete root->_child[i]; root->_child[i] = nullptr; }
		else CreateTree(root->_child[i]);
	}
}
void Tree::DestroyTree(TreeNode* root)
{
	//注意：初始节点root不会被销毁。
	if (root == nullptr)return;

	for (loop_control i = 0; i < 4; i++)
	{
		DestroyTree(root->_child[i]);
		delete root->_child[i];
	}
}
#endif

float Tree::_findmax(TreeNode* root)
{
	loop_control i = 0;
	float result = 0.0F;
	if (root->_depth == _max_depth - 1)
	{
		for (i = 0; i < 4; i++)
			if (root->_child[i] != nullptr)
			{
				//printf("node score=%.3f\n", root->_child[i]->_eval_score);
				if (result < root->_child[i]->_eval_score)result = root->_child[i]->_eval_score;
			}
				
		return result;
	}
	else
	{
		float a;
		for (i = 0; i < 4; i++)
			if (root->_child[i] != nullptr)
				if (result < (a = _findmax(root->_child[i])))result = a;
		return result;
	}
}
