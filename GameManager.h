#pragma once
#include <stdio.h>
#include "tree.h"
#include <iostream>
#include <stack>

const int GM_IDK = 2;
const int GM_YES = 1;
const int GM_NO = 0;
const int GM_EXIT = 3;
const int GM_RESTART = 4;
const int GM_GUESSED = 0;
const int GM_NEW_CHARACTER  = 2;
const int GM_NEXT = 1;
const int GM_LEFT = 0;
const int GM_RIGHT = 1;
const int GM_NO_ONE = 2;


class GameManager{
	private:
	
	Tree* dataBase;
	Node* current;
	std::stack <Node*> alternatives; 
	
	void returnToHead();
	int stepBack();
	int stepForward(int ans);
	void resetGame();
	int askForRepeat();
	int doGameLoop();
	std::string getDescription(Node* node);
	int getSide(Node* extender);
	
	public:

	GameManager();
	~GameManager();
	
	int makeGuess();
	void saveToFile(const char* filename);
	int loadFromFile(const char* filename);
	void cleanStdin();
	
	//getters
	
	Tree* getDataBase();
	Node* getCurrent();
	
	//setters
	
	void setDataBase(Tree* tree);
	void setCurrent(Node* node);
	
};