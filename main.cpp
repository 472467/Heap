#include <iostream>
#include <fstream> 
#include <ctype.h>
#include <cstdlib>
#include <stdio.h>
#include "treeNode.h"

using namespace std;

void convertTextToHeap(TreeNode*&, char*);
int convertCharToInt(char c);
void convertIntArrayToHeap(int*, TreeNode*&);
void addValueToTree(int, TreeNode*&, TreeNode*&);

int main(){
	TreeNode* head = new TreeNode(NULL, -1);
	TreeNode* child1 = new TreeNode(head, 1);
	TreeNode* child2 = new TreeNode(child2, 1);
	cout << child2->getCurrentDepth(0);
	char* file =  "numbers.txt";// new char[100];
	//cin.getline(file, 100);
	
	convertTextToHeap(head, file);
	
	
}

void convertTextToHeap(TreeNode*& head, char* f){
	int* nArray = new int[10000];
	for(int x = 0; x < 10000; x++){//SETS UNSET INTS TO NEGATIVE, ALL INPUTS ARE POSITIVE IF -1 END ARRAY
		nArray[x] = -1;
	}
	bool inNum = false;
	char* currentNum = new char[9];
	int numLength= 0;
	int numCount = 0;
  
	ifstream fin(f);
	if(fin.is_open()){//THIS CONVERTS INPUT TO A LONG ASS INT ARRAY

		cout << "File Opened successfully!!!. Reading data from file into array" << endl;
		
		while(!fin.eof()){
			char c;
			fin.get(c);
			
			if(inNum){
				if(isdigit(c)){
					currentNum[numLength] = c;
					numLength++;
				}else{
					currentNum[numLength] = '\0';
					nArray[numCount] = 0;
					
					int loop = 0;
					int tNum = 0;
					while(currentNum[loop] != '\0'){
						//cout << convertCharToInt(c) << endl;
						tNum = (tNum * 10) + convertCharToInt(currentNum[loop]);
						loop++;
					}
					//cout << tNum << endl;
					nArray[numCount] = tNum;
					cout << nArray[numCount] << endl;
					
					inNum = false;
					numLength = 0;
					numCount++;
				}
			}else{
				if(isdigit(c)){
					inNum = true;
					currentNum[0] = c;
					numLength++;
					
				}else{
					numLength = 0;
					
				}
			}
			
			
			
		}
		TreeNode* current = head;
		convertIntArrayToHeap(nArray, head);
		
	}
	else //file could not be opened
	{
		cout << "File could not be opened." << endl;
	}
	
	
}

void convertIntArrayToHeap(int* iArray, TreeNode*& head){
	int count = 0;
	head->setNum(iArray[count]);
	count++;
	
	TreeNode* current = head;
	
	while(iArray[count] != -1){
		addValueToTree(iArray[count], head, current);
		count++;
	}
}

void addValueToTree(int value, TreeNode*& head, TreeNode*& current){
	
	
	
	if(value <= current->getNum()){
		if(current->getLeft() == NULL && current->getRight() == NULL){//if both null
			
			TreeNode* n = new TreeNode(current, value);
			current->setLeft(n);

		}else if(current->getLeft() != NULL && current->getRight() == NULL){//right is null
			
			TreeNode* n = new TreeNode(current, value);
			current->setRight(n);
			
		}else if(current->getLeft() != NULL && current->getRight() != NULL){//neither are null
			
			TreeNode* n = new TreeNode(current, value);
			
			if(value > (current->getLeft())->getNum()){//bigger than left kid
				
				int tNum = (current->getLeft())->getNum();//saves heads value before swapping it with bigger value
				(current->getLeft())->setNum(value); //swaps
				addValueToTree(tNum, head, current);//runs it again with lesser value
				
			}else if (value > (current->getLeft())->getNum()){//bigger than right kid
				
			}else if(true){
				
			}else{
				
			}
			
		}else{
			cout << "ERROR" << endl;
		}
			
	}else{//value > head->getNum()
		int tNum = current->getNum();//saves heads value before swapping it with bigger value
		current->setNum(value); //swaps
		addValueToTree(tNum, head, current);//runs it again with lesser value
	}
}


int convertCharToInt(char c){
	//cout << c;
	if(c == '0'){
		return 0;
	}else if(c == '1'){
		return 1;
	}else if(c == '2'){
		return 2;
	}else if(c == '3'){
		return 3;
	}else if(c == '4'){
		return 4;
	}else if(c == '5'){
		return 5;
	}else if(c == '6'){
		return 6;
	}else if(c == '7'){
		return 7;
	}else if(c == '8'){
		return 8;
	}else if(c == '9'){
		return 9;
	}
	
	//cout << "error";
	return NULL;
}