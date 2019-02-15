#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sys/stat.h>

const int T_FILEOPEN_FAILED = 1; 
const int T_INVALID_FILE = 2;
const int T_UNDEFINED_EXCEPTION = 3;
const int T_SUCCESS = 0;
const int T_BUF_LENGTH = 100;

class Node{
	
	private:
	
	std::string data;
	Node* left;
	Node* right;
	Node* parent;
	
	public:
	
	Node(Node* _parent, Node* _left, Node* _right,std::string _data);
	
	Node();
	
	~Node();
	
	void disconnect(Node* node);
	
	//getters
	
	Node* getLeft();
	
	Node* getRight();
	
	Node* getParent();
	
	std::string getData();	
	
	//setters
	
	void setLeft(Node* node);
	
	void setRight(Node* node);
	
	void setParent(Node* node);
	
	void setData(std::string string);
};

class Tree{
	private:
	
	Node* head;
	
	void saveNodeData(FILE* file, Node* node);
	int isBrace(char c);
	
	public:
	Tree();
	
	~Tree();
	
	
	void print();
	
	void clearBranch(Node* root);
	int saveToFile(const char* filename);
	int loadFromFile(const char* filename);
	
	
	//getters
	
	Node* getHead();
	//setters
	
	void setHead(Node* node);
	
};
