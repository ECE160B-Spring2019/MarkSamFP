#pragma once

#include "ofxGui.h"
#include "ofMain.h"
#include "ofxButton.h"


class buttonPic {
	ofxButton button;
	ofImage * image;
	ofPoint pos;
public: 
	buttonPic(&ofxButton, &ofImage, &ofPoint); 
	void draw();
	int getx();
	int gety();
	void setImage(ofImage *z newImage);
};

class tile {
	buttonPic tileButton;
	bool isBomb, isRevealed;
	int numBombs;
public:
	tile(bool, ofPoint);
	~tile();
	tile(const tile&);
	tile& operator= (const tile&);
	void reveal();
		//display actual tileImage instead of a blank tile, and toggle isRevealed
	int getNum();
	void changeNum();
	bool isitBomb();
	bool isitRevealed();
};

class board {
	tile** grid; //might be a vector of vectors instead
	int length;
	int width;
public:
	board(int boardLength, int boardWidth, int numMines); 
		//first generate array of correct size using new
		//for each tile user rand() + mod to decide whether to put a bomb or not
		//if a bomb is placed, use changeNum() to increment num of all surrounding tiles
	reveal(int x, int y);
		//reveal all surrounding tiles recursively
};


