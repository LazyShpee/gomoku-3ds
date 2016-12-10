#include "../include/Referee.hpp"

Referee::Referee(char board[19][19]) : board((char **)board) {

}

Referee::~Referee() {

}

char Referee::vision(char *v, char x, char y, char direction, bool lookBack) {

    return 0;
}

bool Referee::CanPlace(char player, char x, char y) {
    if (board[x][y]) return false;
    return true;
}

bool Referee::UpdateBoard(char x, char y) {

    return false;
}
