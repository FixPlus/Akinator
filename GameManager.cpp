#include "GameManager.h"


//CONSTRUCTORS

GameManager::GameManager(): alternatives(){
	dataBase = new Tree();
	current = dataBase->getHead();
	current->setData("real");
	current->setLeft(new Node(current, NULL, NULL, "Wizard"));
	current->setRight(new Node(current, NULL, NULL, "Cat"));
}

GameManager::~GameManager(){
	delete dataBase;
}


//FUNCTIONS


void GameManager::returnToHead(){
	current = dataBase->getHead();
}

int GameManager::stepBack(){
	if(current->getParent()){
		current = current->getParent();
		return 1;
	}
	return 0;
}

void GameManager::resetGame(){
	returnToHead();
	printf("\n\n      ****GAME STARTED****\n\ny for YES, n for NO,d if DOUBT,\nb for BACK, q to QUIT, s to SAVE,\nl to LOAD, e to DELETE A BRANCH\n\n");	
}

int GameManager::doGameLoop(){
	int status = GM_NEXT;
	int counter = 1;
	while(status == GM_NEXT){
		std::cout << "Question #" << counter <<": Is your character "<< current->getData() << "?" << std::endl;
		char answer = 0;
		std::cin >> answer;
		
		switch(answer){
			case 'y':{
				status = stepForward(GM_YES);
				counter++;
				break;
			}
			case 'n':{
				status = stepForward(GM_NO);
				counter++;
				break;
			}
			case 'd':{
				status = stepForward(GM_IDK);
				counter++;
				break;
			}
			case 'b':{
				if(stepBack())
					counter--;
				break;
			}
			case 'e':{
				dataBase->clearBranch(current);
				printf("Cleared! Game has been restarted\n\n");
				returnToHead();
				counter = 1;
				break;
			}
			case 's':{
				saveToFile("aki.txt");
				printf("Akinator saved!\n\n");
				break;
			}
			case 'l':{
				switch(loadFromFile("aki.txt")){
					case T_FILEOPEN_FAILED: {
						printf("Fileopen failed!\n");
						return GM_RESTART;
					}
					case T_INVALID_FILE: {
						printf("Invalid file!\n");
						return GM_RESTART;
					}
					case T_UNDEFINED_EXCEPTION: {
						printf("Undefined exception occured!\n");
						return GM_RESTART;
					}
				}					
				returnToHead();
				counter = 1;
				printf("Akinator loaded!\n\n");
				break;
			}
			case 'q':{
				return GM_EXIT;
			}
			default:{
				continue;
			}
		}
	}
	return status;
}

int GameManager::askForRepeat(){
	std::cout << "Play again? y/n" << std::endl;
	char ans(0);
	std::cin >> ans;
	
	if(ans == 'y')
		return GM_YES;
	else
		return GM_NO;	
}

void GameManager::cleanStdin(){   //fflush(stdin)
	int c;
	do {
		c = getchar();
	} while (c != '\n' && c != EOF);
}

int GameManager::makeGuess(){
	resetGame();
	
	
	int status = doGameLoop();
	
	
	if(status == GM_EXIT)
		return GM_NO;
	else
		if(status == GM_RESTART)
			return GM_YES;
	
	
	std::string finalSpeech;
	
	if(status == GM_GUESSED)
		finalSpeech = "****I guessed!";    //if it guessed
	else
		finalSpeech = "****Now i know!";	//if we added a new character

	std::cout << std::endl << finalSpeech <<" It is " << current->getData() << ":"<< getDescription(current)<<"!****" << std::endl << std::endl;
	return askForRepeat();
}

int GameManager::getSide(Node* extender){
	if(!extender || !extender->getParent())
		return GM_NO_ONE;
	
	if(extender->getParent()->getLeft() == extender)
		return GM_LEFT;
	if(extender->getParent()->getRight() == extender)
		return GM_RIGHT;
	
	return GM_NO_ONE;
}


void GameManager::saveToFile(const char* filename){
	dataBase->saveToFile(filename);
}

int GameManager::loadFromFile(const char* filename){
	return dataBase->loadFromFile(filename);
}

std::string GameManager::getDescription(Node* node){
	std::string ret = "";
	if(!node)
		return ret;
	
	do{
		if(!ret.empty())ret = "," + ret;
		ret = node->getParent()->getData() + ret;
		if(getSide(node) == GM_LEFT)
			ret = "not " + ret;
		
		ret = " " + ret;
		node = node->getParent();
	}while(node->getParent());
	return ret;
}


int GameManager::stepForward(int ans){
	if(current->getRight())
		if(ans == GM_YES)
			current = current->getRight();
		else
			if(ans == GM_NO)
				current = current->getLeft();
			else{
				alternatives.push(current->getLeft());   //if T_IDK occurs, choose left and adding an alternative branch for the right
				current = current->getRight();
			}
		
	if(current->getRight() == NULL){             //checking are we on the leaf of the tree
		std::cout << "Is it " << current->getData() << "?" << std::endl;    //if we are - checking if we've found the right character
		char vote = 0;
		std::cin >> vote;
		if(vote == 'y')
			return GM_GUESSED;                   //sending an information of succesful guess to dtop gameLoop
		else
		{
			if(!alternatives.empty()){
				current = alternatives.top();    // Looking for alternative branshes first
				alternatives.pop();
				
				if(!current->getRight())		//If the alternative is another character we skip up to next "stepForward"
					return stepForward(GM_YES);
					
				return GM_NEXT;      			//In other case we return to gameLoop
			}
			
			//if failed, asking about the character
			
			std::cout << "Type in a distinctive feature of your character:" << std::endl;    
			std::string feature; 
			cleanStdin();
			std::getline(std::cin, feature);
			
			std::cout << "Type in your character name:" << std::endl;
			std::string name;
			std::getline(std::cin, name);
			
			
			current->setLeft(new Node(current, NULL, NULL, current->getData()));
			current->setRight(new Node(current, NULL, NULL, name));
			current->setData(feature);
			current = current->getRight();
			
			return GM_NEW_CHARACTER;     		//sending information about new character to stop gameLoop
		}
	}
	else
		return GM_NEXT;							//standard returning to GameLoop 
}
