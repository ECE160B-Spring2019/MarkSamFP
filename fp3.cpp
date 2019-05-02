#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#define RESET "\033[0m"
#define BLUE "\033[1;34m"
#define GREEN "\033[1;32m"
#define RED "\033[1;31m"
#define PINK "\033[1;35m"
#define DARKRED "\033[0;31m"
#define CYAN "\033[1;36m"
#define PURPLE "\033[0;35"
#define YELLOW "\033[0;33m"
#define GAMELOST "\033[0;33m|\033[0m \033[1;31m*\033[0;0m  "

using namespace std;

int rowl;
int coll;
char difficulty;

class Tile {
        public:
        Tile() {flag = 0, bomb = 0, show = 0, num = 0;}
        int flag;
        int bomb;
        int show;
        int num;
};

class Board {
        public:
        int tilesShown = 0;
        Tile t[30][30];
        int bombs;
        void initboard();
        void revealtile(int r, int c);
        void flagtile(int r, int c);
        void unflagtile(int r, int c);
        void drawboard();
        void drawtile(int r, int c);
        void placebombs(int r, int c);
        void check_empty(int r, int c);
        int check_win();
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

bool freesquare(int r1, int r2, int r, int c) {
        return abs(r1 - r) <= 1 && abs(r2 - c) <= 1;
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
                if(rand1 >= 1) {
                    t[rand1 - 1][rand2].num++;
                }
                if(rand2 >= 1) {
                    t[rand1][rand2 - 1].num++;
                }
                if(rand1 < rowl - 1) {
                    t[rand1 + 1][rand2].num++;
                }
                if(rand2 < coll - 1) {
                    t[rand1][rand2 + 1].num++;
                }
                if(rand1 >= 1 && rand2 >= 1) {
                    t[rand1 - 1][rand2 - 1].num++;
                }
                if(rand1 >= 1 && rand2 < coll - 1) {
                    t[rand1 - 1][rand2 + 1].num++;
                }
                if(rand1 < rowl - 1 && rand2 < coll - 1) {
                    t[rand1 + 1][rand2 + 1].num++;
                }
                if(rand1 < rowl - 1 && rand2 >= 1) {
                    t[rand1 + 1][rand2 - 1].num++;
                }
        }

}

void Board::revealtile(int r, int c) {
        t[r][c].show = 1;
        tilesShown++;
}

void Board::flagtile(int r, int c) {
        t[r][c].flag = 1;
}

void Board::unflagtile(int r, int c) {
        t[r][c].flag = 0;
}

    // ---------------------------------------------//

void Board::drawtile(int r, int c) {
        if(c > 0) {
            cout << YELLOW << "|" << RESET;
        }
        if(t[r][c].flag == 1) {
            cout << "  F ";
            return;
        }
        if(t[r][c].show == 0) {
            cout << "||||";
            return;
        }
        if(t[r][c].bomb == 1) {
            cout << RED << "  * " << RESET;
            return;
        }

        switch(t[r][c].num) {
                case 1: cout << "  " << BLUE << "1 " << RESET;
                        break;
                case 2: cout << "  " << GREEN << "2 " << RESET;
                        break;
                case 3: cout << "  " << RED << "3 " << RESET;
                        break;
                case 4: cout << "  " << PINK << "4 " << RESET;
                        break;
                case 5: cout << "  " << DARKRED << "5 " << RESET;
                        break;
                case 6: cout << "  " << CYAN << "6 " << RESET;
                        break;
                case 7: cout << "  " << PURPLE << "7 " << RESET;
                        break;
                case 8: cout << "  " << BLUE << "8 " << RESET;
                        break;
                default: cout << "    ";
                        break;
        }
        return;
}

        // ---------------------------------------------//

void Board::drawboard() {
        int row;
        int col;
        cout << endl << "    ";
        for(col = 0; col < coll; col++) {
                if(col < 9) {
                        cout << "  " << col + 1 << "  ";
                }
                else {
                        cout << " " << col + 1 << "  ";
                }
        }
        cout << endl;
        for (row = 0; row < rowl; row++) {
                if (row < 9) {
                        cout << " " << row + 1 << ": ";
                }
                else {
                        cout << row + 1 << ": ";
                }
                for (col = 0; col < coll; col++) {
                        drawtile(row, col);
                }
                cout << endl;
                if (row != (rowl - 1)) {
                        cout << "    " << YELLOW;
                        for (col = 0; col < coll; col++) {
                            cout << "-----";
                        }
                        cout << RESET << endl;
                }
        }
        cout << endl;
        return;
}

int Board::check_win() {
    return (tilesShown + bombs == rowl * coll);
}

void check_boardsize() {
        do {
                cout << "Enter a board height: (10-30) " << endl;
                cin >> rowl;
        } while (rowl < 10 || rowl > 30);
        do {
                cout << "Enter a board width: (10-30) " << endl;
                cin >> coll;
        } while (coll < 10 || coll > 30);
}

void check_difficulty() {
        do {
                cout << "Easy (E or e): ~12% Bombs" << endl;
                cout << "Medium (M or m): ~16% Bombs" << endl;
                cout << "Hard (H or h): ~18% Bombs" << endl;
                cout << "Enter a difficulty: " << endl;
                cin >> difficulty;
        } while (difficulty != 'E' && difficulty != 'e' && difficulty != 'M' && difficulty != 'm' && difficulty != 'H' && difficulty != 'h');
}

int play_again() {
        char response;
        do {
                cout << "Do you want to play again? (y/n) " << endl;
                cin >> response;
        } while (response != 'Y' && response != 'y' && response != 'N' && response != 'n');
        if (response == 'Y' || response == 'y') {
                return 1;
        }
        else {
                return 0;
        }
}

int checktile(Board& b, int r, int c, char i) {
        if ((i == 'u' || i == 'U') && b.t[r-1][c-1].flag == 1) {
                return 1;
        }
        if ((i == 'p' || i == 'P') && b.t[r-1][c-1].show == 1) {
                return 1;
        }
        if ((i == 'u' || i == 'U') && b.t[r-1][c-1].show == 1) {
                return 1;
        }
        if ((i == 'p' || i == 'P') && b.t[r-1][c-1].flag == 1) {
                return 1;
        }
        if ((i == 'r' || i == 'R') && b.t[r-1][c-1].flag == 0) {
                return 1;
        }
        else {
                return 0;
        }
}

void asktile(Board& b, int* r, int* c, char* i) {
        do {
                do {
                        cout << "Would you like to place a flag, remove a flag, or uncover a tile: (p/r/u) " << endl;
                        cin >> *i;
                } while (*i != 'U' && *i != 'u' && *i != 'P' && *i != 'p' && *i != 'R' && *i != 'r');
                do {
                        cout << "What row: " << endl;
                        cin >> *r;
                } while (*r < 1 || *r > rowl);
                do {
                        cout << "What column: " << endl;
                        cin >> *c;
                } while (*c < 1 || *c > coll);
        } while (checktile(b, *r, *c, *i));
        return;
}


void Board::check_empty(int r, int c) {
        if(t[r][c].num == 0) {
                if(r-1 >= 0 && c-1 >= 0) {
                        if(t[r-1][c-1].show == 1) {
                                ;
                        }
                        else{
                                revealtile(r-1, c-1);
                                check_empty(r-1, c-1);
                        }
                }
                if(r-1 >= 0) {
                        if(t[r-1][c].show == 1) {
                                ;
                        }
                        else {
                                revealtile(r-1, c);
                                check_empty(r-1, c);
                        }
                }
                if(r-1 >= 0 && c+1 < coll) {
                        if(t[r-1][c+1].show == 1) {
                                ;
                        }
                        else {
                                revealtile(r-1, c+1);
                                check_empty(r-1, c+1);
                        }
                }
                if(c+1 < coll) {
                        if(t[r][c+1].show == 1) {
                                ;
                        }
                        else {
                                revealtile(r, c+1);
                                check_empty(r, c+1);
                        }
                }
                if(r+1 < rowl && c+1 < coll) {
                        if(t[r+1][c+1].show == 1) {
                                ;
                        }
                        else {
                                revealtile(r+1, c+1);
                                check_empty(r+1, c+1);
                        }
                }
                if(r+1 < rowl) {
                        if(t[r+1][c].show == 1) {
                                ;
                        }
                        else {
                                revealtile(r+1, c);
                                check_empty(r+1, c);
                        }
                }
                if(r+1 < rowl && c-1 >= 0) {
                        if(t[r+1][c-1].show == 1) {
                                ;
                        }
                        else {
                                revealtile(r+1, c-1);
                                check_empty(r+1, c-1);
                        }
                }
                if(c-1 >= 0) {
                        if(t[r][c-1].show == 1) {
                                ;
                        }
                        else {
                                revealtile(r, c-1);
                                check_empty(r, c-1);
                        }
                }
        }
        return;
}

void firstbox(Board *b, int *row, int *col, char *item) {
                do {
                        b->drawboard();
                        asktile(*b, row, col, item);
                        if(*item == 'p' || *item == 'P') {
                                b->flagtile((*row)-1, (*col)-1);
                        }
                        if(*item == 'r' || *item == 'R') {
                                b->unflagtile((*row)-1, (*col)-1);
                        }
                        if(*item == 'u' || *item == 'U') {
                                b->revealtile((*row)-1, (*col)-1);
                        }
                } while (*item != 'U' && *item != 'u');

}

void play_game() {
        int row, col, n;
        char item;
        Board b;
        b.initboard();
        firstbox(&b, &row, &col, &item);
        b.placebombs(row, col);
        b.check_empty(row-1, col -1);
        while(1) {
                b.drawboard();
                asktile(b, &row, &col, &item);
                if(item == 'p' || item == 'P') {
                        b.flagtile(row-1, col-1);
                }
                if(item == 'r' || item == 'R') {
                        b.unflagtile(row-1, col-1);
                }
                if(item == 'u' || item == 'U') {
                        if(b.t[row-1][col-1].bomb == 1) {
                                for (int r = 0; r < rowl; r++) {
                                        for (int c = 0; c < coll; c++) {
                                                b.t[r][c].flag = 0;
                                                b.t[r][c].show = 1;
                                        }
                                }
                                b.drawboard();
                                cout << "You Lost!" << endl;
                                return;
                        }
                        else {
                                b.revealtile(row-1, col-1);
                                b.check_empty(row-1, col-1);
                        }
                }
                if(b.check_win()) {
                        cout << "You Won!" << endl;
                        return;
                }
        }
}

int main() {
        while(1) {
                check_boardsize();
                check_difficulty();
                play_game();
                if (!play_again()) {
                        break;
                }
        }
        return 0;
}
