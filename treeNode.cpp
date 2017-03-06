#include "treeNode.h"
#include <stdlib.h>
#include <time.h>

TreeNode::TreeNode(TreeNode* p, int n){
	float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	TreeNode* current  = this;
	id = r * (rand() % 100000);
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

void TreeNode::safeDelete(){
	TreeNode* parentRight = getParent()->getRight();
	TreeNode* current = this;
	
	if(parentRight == NULL){
		getParent()->setLeft(NULL);
	}else if(parentRight->getID() == current->getID()){
		getParent()->setRight(NULL);
	}
	
	delete this;
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

float TreeNode::getID(){
	return id;
}

void TreeNode::setRight(TreeNode* r){
	right = r;
}

int TreeNode::getCurrentDepth(){
	bool running = true;
	int depth = 0;
	TreeNode* current = this;
	
	while(running){
		if(current->getParent() == NULL){
			return depth;
		}else{
			current = current->getParent();
			depth++;
		}
	}
	return -1;
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