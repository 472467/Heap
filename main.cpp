#include <iostream>
#include <fstream> 
#include <ctype.h>
#include <cstdlib>
#include <stdio.h>
#include <math.h>
#include "treeNode.h"

using namespace std;

void convertTextToHeap(TreeNode*&, char*);
int convertCharToInt(char c);
void convertIntArrayToHeap(int*, TreeNode*&);
void addValueToTree(int, TreeNode*&, TreeNode*&, int, int);
void printDeleteHeap(TreeNode*, int, int);
char* directionsToBalancedNode(int, int, char*&);
void siftDown(TreeNode*);
void visualizeTree(TreeNode*);
void convertInputToHeap(TreeNode*&, char*);

int main(){
	TreeNode* head = new TreeNode(NULL, -1);
	cout << "Type 1 to input through file || Type 2 to input through typing" << endl;
	char* input = new char[2];
	cin.getline(input, 2);
	
	char* file =  new char[1000];
	if(input[0] == '1'){
		cout << "input file name" << endl;
		cin.getline(file, 100);
		convertTextToHeap(head, file);
	}else{
		cout << "type a bunch of numbers no greater than 1000 and spaced with a space" << endl;
		cin.getline(file, 100);
		convertInputToHeap(head, file);
	}
	
}

void convertInputToHeap(TreeNode*& head, char* in){
	int* nArray = new int[10000];
	for(int x = 0; x < 10000; x++){//SETS UNSET INTS TO NEGATIVE, ALL INPUTS ARE POSITIVE IF -1 END ARRAY
		nArray[x] = -1;
	}
	bool inNum = false;
	char* currentNum = new char[9];
	int numLength= 0;
	int numCount = 0;
	int count = 0;
	
	while(in[count] != '\0'){
		char c = in[count];

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
		
		count++;
	}
	
	TreeNode* current = head;
	convertIntArrayToHeap(nArray, head);
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
					//cout << nArray[numCount] << endl;
					
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
	int currentDepth = 0;
	int depthProgression = 1;
	

	while(iArray[count] != -1){
		TreeNode* current = head;
		addValueToTree(iArray[count], head, current, depthProgression, currentDepth);
		
		depthProgression++;
		if(depthProgression > pow(2, currentDepth)){//designates where the most balanced spot on the tree to add next
			depthProgression = 1;
			currentDepth++;
		}
		
		count++;
	}
	
	visualizeTree(head);
	printDeleteHeap(head, depthProgression, currentDepth);
	
}

void visualizeTree(TreeNode* head){
	int currentDepth = 0;
	int depthProgression = 1;
	TreeNode* tCurrent = head;

	while(tCurrent != NULL){
		
		if(currentDepth == 0){
			cout << "0: " ;
			cout << tCurrent->getNum() << " || ";
		}else{
			char* directions;
			directionsToBalancedNode(currentDepth, depthProgression, directions);//sets direction
			int count = 0;
			while(directions[count] != '\0'){//adds newNode to the most balanced spot by following the directions provided
				if(directions[count] == 'L'){
					if(tCurrent->getLeft() != NULL){
						tCurrent = tCurrent->getLeft();
					}else{
						tCurrent = NULL;
						break;
					}
					
				}else{
					if(tCurrent->getRight() != NULL){
						tCurrent = tCurrent->getRight();
					}else{
						tCurrent = NULL;
						break;
					}
				}

				count++;
			}
			
			if(tCurrent == NULL){
				break;
			}else{
				if(depthProgression == 1){
					cout << currentDepth << ": ";
				}
				
				cout << tCurrent->getNum() << " || ";
			}
			
		}
		
		depthProgression++;
		if(depthProgression > pow(2, currentDepth)){//designates where the most balanced spot on the tree to add next
			depthProgression = 1;
			currentDepth++;
			cout << "\n";
		}
		if(tCurrent != NULL){
			tCurrent = head;
		}
	}
	
	cout << "\n\n";
}

void printDeleteHeap(TreeNode* head, int depthProgression, int currentDepth){//deletes highest values first
	TreeNode* tCurrent = head;

	depthProgression--;//depthProgression in the convertIntArrayToHeap function is set to the next Value(NULL), not the last set value
	if(depthProgression < 1){
		currentDepth--;
		depthProgression = pow(2, currentDepth);
	}
	
	int it = 0;
	while(currentDepth != 0){
		char* directions;
		directionsToBalancedNode(currentDepth, depthProgression, directions);//sets direction
		int count = 0;
		while(directions[count] != '\0'){//adds newNode to the most balanced spot by following the directions provided
			if(directions[count] == 'L'){
				tCurrent = tCurrent->getLeft();
			}else{
				tCurrent = tCurrent->getRight();
			}

			count++;
		}
		
		int tNum = tCurrent->getNum();
		tCurrent->safeDelete();
		cout << head->getNum() << endl;
		head->setNum(tNum);//effectevely deletes the head and replaces it with bottomMost value
		tCurrent = head;
		
		siftDown(tCurrent);
		
		
		depthProgression--;
		if(depthProgression < 1){
			currentDepth--;
			depthProgression = pow(2, currentDepth);
			
		}
		
		tCurrent = head;
	}
}

void siftDown(TreeNode* current){//sifts number down heap
	if(current == NULL){
		
	}else if(current->getLeft() != NULL && current->getRight() == NULL){
		if((current->getLeft())->getNum() > current->getNum()){//swaps with left
			int tNum = current->getNum();
			current->setNum((current->getLeft())->getNum());
			(current->getLeft())->setNum(tNum);
			
			current = current->getLeft();
			siftDown(current);//calls again to sift smaller number
		}
	}else if(current->getLeft() != NULL && current->getRight() != NULL){//swaps with left or right, whichever one is BIGGER
		if((current->getLeft())->getNum() > current->getNum() || (current->getRight())->getNum() > current->getNum()){
			
			if((current->getLeft())->getNum() >= (current->getRight())->getNum()){
				int tNum = current->getNum();
				current->setNum((current->getLeft())->getNum());
				(current->getLeft())->setNum(tNum);
				
				current = current->getLeft();
				siftDown(current);//calls again to sift smaller number
			}else{
				int tNum = current->getNum();
				current->setNum((current->getRight())->getNum());
				(current->getRight())->setNum(tNum);
				
				current = current->getRight();
				siftDown(current);//calls again to sift smaller number
			}
		}
	}
}

void addValueToTree(int value, TreeNode*& head, TreeNode*& current, int depthProgression, int currentDepth){
	char* directions;
	directionsToBalancedNode(currentDepth, depthProgression, directions);//sets direction
	
	int count = 0;
	TreeNode* tCurrent = head;
	if(currentDepth == 0){//makes sure their is a head node
		head = new TreeNode(NULL, value);
	}else{
		while(directions[count] != '\0'){//adds newNode to the most balanced spot by following the directions provided
			if(directions[count + 1] == '\0'){
				
				current = new TreeNode(tCurrent, value);
				
				if(directions[count] == 'L'){
					tCurrent->setLeft(current);
				}else{
					tCurrent->setRight(current);
				}
				tCurrent = current;
				
			}else if(directions[count] == 'L'){
				tCurrent = tCurrent->getLeft();
			}else{
				tCurrent = tCurrent->getRight();
			}

			count++;
		}
		bool running = true;
		
		while(running){
			if(tCurrent->getParent() == NULL){
				running = false;
			}else if(tCurrent->getNum() > (tCurrent->getParent())->getNum()){//if current num is bigger than the parents
				int tNum = (tCurrent->getParent())->getNum();
				(tCurrent->getParent())->setNum(tCurrent->getNum());
				tCurrent->setNum(tNum);
				tCurrent = tCurrent->getParent();
			}else{//value is smaller or equal
				running = false;
			}
		}
		current = tCurrent;
	}
}

char* directionsToBalancedNode(int currentDepth, int depthProgression, char*& directions){//this gives directions to next balanced node in the heap
	directions = new char[currentDepth + 1];
	
	for(int x  = currentDepth; x > 0; x--){//builds upwards from the designated location
		if(depthProgression % 2 ==  0){
			directions[x - 1] = 'R';
		}else{
			directions[x - 1] = 'L';
		}
		int newProgression = 1;
		int tProgression =  depthProgression;// 2
		bool running = true;
		
		while(running){
			tProgression =  tProgression -2;
			if(tProgression > 0){
				//cout << tProgression << "TProg"<< endl;
				newProgression++;
			}else{
				//cout << newProgression << endl;
				running = false;
			}
		}
		depthProgression = newProgression;
	}
	directions[currentDepth] = '\0';
	
	return directions;
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