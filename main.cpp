#include <iostream>
#include <fstream> 
#include <ctype.h>
#include <cstdlib>
#include <stdio.h>
#include "treeNode.h"

using namespace std;

void convertTextToHeap(TreeNode*, char*);
int convertCharToInt(char c);

int main(){
	TreeNode* head = new TreeNode(NULL, -1);
	char* file =  "numbers.txt";// new char[100];
	//cin.getline(file, 100);
	
	convertTextToHeap(head, file);
	
	
}

void convertTextToHeap(TreeNode* head, char* f){
	int nArray [10000];
	
	bool inNum = false;
	char* currentNum = new char[4];
	int numLength= 0;
	int numCount = 0;
  
	ifstream fin(f);
	if(fin.is_open()){

		cout << "File Opened successfully!!!. Reading data from file into array" << endl;
		
		while(!fin.eof()){
			char c;
			fin.get(c);
			//cout << c << endl;
			
			if(inNum){
				if(isdigit(c)){
					currentNum[numLength] = c;
					numLength++;
				}else{
					currentNum[numLength+1] = '\0';
					int loop = 0;
					while(currentNum[loop] != '\0'){
						//cout << convertCharToInt(c) << endl;
						nArray[numCount] += convertCharToInt(c);
						loop++;
					}
					
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
		//array[position-1] = '\0'; //placing character array terminating character
		
	}
	else //file could not be opened
	{
		cout << "File could not be opened." << endl;
	}
	
	
	
}

int convertCharToInt(char c){
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
	
	cout << "error";
	return NULL;
}