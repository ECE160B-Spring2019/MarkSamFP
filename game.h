#pragma once

#include "ofxGui.h"
#include "ofMain.h"
#include "ofxButton.h"
#include "board.h"

class game {
	int numBombs;
	string gameState;
	ofImage * bomb;
	ofImage * flag;
	ofImage * grid;
		//a seperate class containing a button and a label might be needed for each of these
	buttonPic * easy; 
	buttonPic * intermediate;
	buttonPic * hard;
	buttonPic * playAgain;
	buttonPic * menuButton;
public:
	game(string difficulty, ofImage** images);
	~game();
	friend class board;
};

