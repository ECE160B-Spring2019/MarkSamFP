#include "fp.h"

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

class tBoard : public Board {
    public:
        tBoard() : Board() {}
        void revealtile(int r, int c);
        void flagtile(int r, int c);
        void unflagtile(int r, int c);
        void drawboard();
        void drawtile(int r, int c);
        void placebombs(int r, int c); //the arguments are the user's first coordinates
        void check_empty(int r, int c);
        int check_win();
        bool freesquare(int r1, int r2, int r, int c);
        void revealBoard();
        void reset();
};

class tGame : public Game {
    public:
        tGame() : Game() {
            b = new tBoard;
        }
        ~tGame() {
            delete b;
        }
        void check_boardsize();
        void check_difficulty();
        int play_again();
        int checktile(int r, int c, char i);
        void asktile(int& r, int& c, char& i);
        void firstbox(int& row, int& col, char& item);
        void play_game();
        bool playermove(int row, int col, char item);
        //void print_Records();
        //void check_Record();
};

// class tRecord : public Record {
//     public:
//         tRecord(int r, int c, time_t& begin, time_t& end, diffs di)
//             rows = r;
//             cols = c;
//             d = di;
//             time = difftime(begin, end);
//         }
//         bool operator>(Record& r) {
//             int size = rows * cols;
//             int size2 = r.rows * r.cols;
//             if(size != size2) {
//                 return size > size2;
//             }
//             else if(d != r.d) {
//                 return d > r.d;
//             }
//             else {
//                 return time <= r.time;
//             }
//         }
//         void printRecord();
// };
//


bool tBoard::freesquare(int r1, int r2, int r, int c) {
        return abs(r1 - r) <= 1 && abs(r2 - c) <= 1;
}

void tBoard::placebombs(int row, int col) {
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

void tBoard::revealtile(int r, int c) {
        t[r][c].show = 1;
        tilesShown++;
}

void tBoard::flagtile(int r, int c) {
        t[r][c].flag = 1;
}

void tBoard::unflagtile(int r, int c) {
        t[r][c].flag = 0;
}

void tBoard::drawtile(int r, int c) {
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


void tBoard::drawboard() {
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

int tBoard::check_win() {
    return (tilesShown + bombs == rowl * coll);
}

void tBoard::check_empty(int r, int c) {
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

void tGame::check_boardsize() {
        int rows, cols;
        do {
                cout << "Enter a board height: (10-30) " << endl;
                cin >> rows;
        } while (rows < 10 || rows > 30);
        do {
                cout << "Enter a board width: (10-30) " << endl;
                cin >> cols;
        } while (cols < 10 || cols > 30);

        b->t.resize(rows);
        for(int ii = 0; ii < rows; ii++) {
            b->t[ii].resize(cols);
        }

        b->rowl = rows;
        b->coll = cols;
}

void tGame::check_difficulty() {
        char difficulty;
        do {
                cout << "Easy (E or e): ~12% Bombs" << endl;
                cout << "Medium (M or m): ~16% Bombs" << endl;
                cout << "Hard (H or h): ~18% Bombs" << endl;
                cout << "Enter a difficulty: " << endl;
                cin >> difficulty;
        } while (difficulty != 'E' && difficulty != 'e' && difficulty != 'M' && difficulty != 'm' && difficulty != 'H' && difficulty != 'h');

        if(difficulty == 'e' || difficulty == 'E') {
                b->bombs = (b->rowl * b->coll) * .12;
                d = easy;
        }
        else if(difficulty == 'm' || difficulty == 'M') {
                b->bombs = (b->rowl * b->coll) * .16;
                d = medium;
        }
        else {
                b->bombs = (b->rowl * b->coll) * .18;
                d = hard;
        }
}

int tGame::play_again() {
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

int tGame::checktile(int r, int c, char i) {
        if ((i == 'u' || i == 'U') && b->t[r-1][c-1].flag == 1) {
                return 1;
        }
        if ((i == 'p' || i == 'P') && b->t[r-1][c-1].show == 1) {
                return 1;
        }
        if ((i == 'u' || i == 'U') && b->t[r-1][c-1].show == 1) {
                return 1;
        }
        if ((i == 'p' || i == 'P') && b->t[r-1][c-1].flag == 1) {
                return 1;
        }
        if ((i == 'r' || i == 'R') && b->t[r-1][c-1].flag == 0) {
                return 1;
        }
        else {
                return 0;
        }
}

void tGame::asktile(int& r, int& c, char& i) {
        do {
                do {
                        cout << "Would you like to place a flag, remove a flag, or uncover a tile: (p/r/u) " << endl;
                        cin >> i;
                } while (i != 'U' && i != 'u' && i != 'P' && i != 'p' && i != 'R' && i != 'r');
                do {
                        cout << "What row: " << endl;
                        cin >> r;
                } while (r < 1 || r > b->rowl);
                do {
                        cout << "What column: " << endl;
                        cin >> c;
                } while (c < 1 || c > b->coll);
        } while (checktile(r, c, i));
        return;
}

void tGame::firstbox(int& row, int& col, char& item) {
                do {
                        b->drawboard();
                        asktile(row, col, item);
                        if(item == 'p' || item == 'P') {
                                b->flagtile(row-1, col-1);
                        }
                        if(item == 'r' || item == 'R') {
                                b->unflagtile(row-1, col-1);
                        }
                        if(item == 'u' || item == 'U') {
                                b->revealtile(row-1, col-1);
                        }
                } while (item != 'U' && item != 'u');
}

bool tGame::playermove(int row, int col, char item) {
        if(item == 'p' || item == 'P') {
                b->flagtile(row-1, col-1);
        }
        if(item == 'r' || item == 'R') {
                b->unflagtile(row-1, col-1);
        }
        if(item == 'u' || item == 'U') {
                if(b->t[row-1][col-1].bomb == 1) {
                        b->revealBoard();
                        return 1;
                }
                else {
                        b->revealtile(row-1, col-1);
                        b->check_empty(row-1, col-1);
                }
        }
        return 0;
}

void tBoard::revealBoard() {
    for (int r = 0; r < rowl; r++) {
            for (int c = 0; c < coll; c++) {
                    t[r][c].flag = 0;
                    t[r][c].show = 1;
            }
    }
    drawboard();
}

void tGame::play_game() {
        int row, col, n;
        char item;
        firstbox(row, col, item);
        //begin = time(0);
        b->placebombs(row, col);
        b->check_empty(row-1, col -1);
        while(1) {
                b->drawboard();
                asktile(row, col, item);
                if(playermove(row, col, item)) {
                    cout << "You Lost!" << endl;
                    return;
                }
                if(b->check_win()) {
                        cout << "You Won!" << endl;
                        //end = time(0);
                        //check_Record();
                        return;
                }
        }
}

// void tRecord::printRecord() {
//     cout << "Time: " << time << "\t";
//     cout << "Difficulty: " << d << "\t";
//     cout << "Board size" << rows << "x" << cols << endl;
// }
//
// void tGame::print_Records() {
//     cout << "NEW RECORD!" << endl;
//     for(int ii = 0; ii < records.size(); ii++) {
//         cout << ii + 1 << "." << "\t";
//         records[ii]->printRecord();
//     }
// }
//
// void tGame::check_Record() {
//     tRecord* thisGame = new tRecord(b->rowl, b->coll, begin, end, d);
//     int n = records.size();
//     if(*thisGame > *(records[n - 1])) {
//         records.push_back(thisGame);
//         print_Records();
//         }
//     else {
//         delete thisGame;
//     }
// }

void tBoard::reset() {
        t.erase(t.begin(), t.end());
        rowl = 0;
        coll = 0;
        bombs = 0;
        tilesShown = 0;
}

int main() {
        tGame game;
        while(1) {
                game.check_boardsize();
                game.check_difficulty();
                game.play_game();
                if (!game.play_again()) {
                        break;
                }
                game.b->reset();
        }
        return 0;
}

