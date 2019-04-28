#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int rowl;
int coll;
char difficulty;

class Tile {
        public:
        int flag;
        int bomb;
        int show;
        int num;
};

class Board {
        public:
        Tile t[30][30];
        int bombs;
        void initboard();
        void revealtile(int r, int c);
        void flagtile(int r, int c);
        void unflagtile(int r, int c);
        void drawboard();
        void placebombs(int row, int col);
};

void Board::initboard() {
        int row, col, n;

        if(difficulty == 'e' || difficulty == 'E') {
                bombs = (rowl * coll) * .12;
        }
        else if(difficulty == 'm' || difficulty == 'M') {
                bombs = (rowl * coll) * .16;
        }
        else {
                bombs = (rowl * coll) * .18;
        }

        for(row = 0; row < 30; row++) {
                for (col = 0; col < 30; col++) {
                        n = 0;
                        t[row][col].flag = 0;
                        t[row][col].bomb = 0;
                        t[row][col].show = 0;
                }
        }

}

int freesquare(int r1, int r2, int r, int c) {
        if (r1 == r && r2 == c) {
                return 1;
        }
        if (r1 == r-1 && r2 == c-1) {
                return 1;
        }
        if (r1 == r-1 && r2 == c) {
                return 1;
        }
        if (r1 == r-1 && r2 == c+1) {
                return 1;
        }
        if (r1 == r && r2 == c+1) {
                return 1;
        }
        if (r1 == r+1 && r2 == c+1) {
                return 1;
        }
        if (r1 == r+1 && r2 == c) {
                return 1;
        }
        if (r1 == r+1 && r2 == c-1) {
                return 1;
        }
        if (r1 == r && r2 == c-1) {
                return 1;
        }
        return 0;
}

void Board::placebombs(int row, int col) {
        int i;
        int rand1, rand2, n;
        srand(time(0));
        for(i = 0; i < bombs; i++) {
                do {
                        rand1 = rand() % rowl;
                        rand2 = rand() % coll;
                } while (freesquare(rand1, rand2, row-1, col-1) || t[rand1][rand2].bomb == 1);
                t[rand1][rand2].bomb = 1;
        }
        for(row = 0; row < rowl; row++) {
                for (col = 0; col < rowl; col++) {
                        n = 0;
                        if(row - 1 >= 0 && col - 1 >= 0 && t[row-1][col-1].bomb == 1) {
                                n += 1;
                        }
                        if(row - 1 >= 0 && t[row-1][col].bomb == 1) {
                                n += 1;
                        }
                        if(row - 1 >= 0 && col + 1 < coll && t[row-1][col+1].bomb == 1) {
                                n += 1;
                        }
                        if(col + 1 < coll && t[row][col+1].bomb == 1) {
                                n += 1;
                        }
                        if(col + 1 < coll && row + 1 < rowl && t[row+1][col+1].bomb == 1) {
                                n += 1;
                        }
                        if(row + 1 < rowl && t[row+1][col].bomb == 1) {
                                n += 1;
                        }
                        if(row + 1 < rowl && col - 1 >= 0 && t[row+1][col-1].bomb == 1) {
                                n += 1;
                        }
                        if(col - 1 >= 0 && t[row][col-1].bomb == 1) {
                                n += 1;
                        }
                        t[row][col].num = n;
                }
        }

}

void Board::revealtile(int r, int c) {
        t[r][c].show = 1;
}

void Board::flagtile(int r, int c) {
        t[r][c].flag = 1;
}

void Board::unflagtile(int r, int c) {
        t[r][c].flag = 0;
}
