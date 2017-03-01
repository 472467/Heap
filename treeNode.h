#pragma warning
#ifndef TREENODE_H
#define TREENODE_H

#include <string.h>
#include <iostream>

class TreeNode
{
	private:
		TreeNode* parent;
		TreeNode* left;
		TreeNode* right;
		int num;
	
	public:
		TreeNode(TreeNode*, int);
		TreeNode(TreeNode*, TreeNode*, int);
		TreeNode(TreeNode*, TreeNode*, TreeNode*, int);
		int getNum();
		void setNum(int);
		
		TreeNode* getParent();
		void setParent(TreeNode*);
		
		TreeNode* getLeft();
		void setLeft(TreeNode*);
		
		TreeNode* getRight();
		void setRight(TreeNode*);
		
		int swapWithParent();
		int getCurrentDepth(int);
};

#endif