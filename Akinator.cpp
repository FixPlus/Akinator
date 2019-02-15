#include "GameManager.h"


/*
	Coded by 
		Bushev Dmitry
		
		MIPT 2019  
*/

int main(){
	GameManager* gm = new GameManager();
	
	if(!gm)
		return 1;
	
	while(gm->makeGuess() == GM_YES);

	delete gm;
	
	return 0;
}