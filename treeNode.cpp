#include "treeNode.h"


TreeNode::TreeNode(TreeNode* p, int n){
	num = n;
	parent = p;
	left = NULL;
	right = NULL;
}

TreeNode::TreeNode(TreeNode* p, TreeNode* l, int n){
	num = n;
	parent = p;
	left = l;
	right = NULL;
}

TreeNode::TreeNode(TreeNode* p, TreeNode* l, TreeNode* r, int n){
	num = n;
	parent = p;
	left = l;
	right = r;
}

int TreeNode::getNum(){
	return num;
}
void TreeNode::setNum(int n){
	num = n;
}

TreeNode* TreeNode::getParent(){
	return parent;
}
void TreeNode::setParent(TreeNode* p){
	parent = p;
}

TreeNode* TreeNode::getLeft(){
	return left;
}
void TreeNode::setLeft(TreeNode* l){
	left = l;
}

TreeNode* TreeNode::getRight(){
	return right;
}
void TreeNode::setRight(TreeNode* r){
	right = r;
}

int TreeNode::getCurrentDepth(int depth, TreeNode* current){
	if(getParent() != NULL){
		std::cout << depth << std::endl;
		current = getParent();
		depth++;
		depth = getCurrentDepth(depth, current);
	}else{
		return depth;
	}
}

int TreeNode::swapWithParent(){//swaps number with the parents, effectively swapping their spots in the tree
	int tNum = getNum();
	if(getParent() != NULL){
		num = getParent()->getNum();
		getParent()->setNum(tNum);
	}else{
		std::cout << "ERROR: Parent is NULL" << std::endl;
	}
	
}