#include "../include/Referee.hpp"

Referee::Referee(char (& board)[19][19]) : board(board) {

}

Referee::~Referee() {

}

char Referee::vision(char *v, char x, char y, char direction, bool lookBack) {
  char a;

  switch (direction) {

  case 0:
    ;
    break;

  case 1:
    ;
    break;

  case 2:
    ;
    break;

  case 3:
    ;
    break;

  case 4:
    ;
    break;

  case 5:
    ;
    break;

  case 6:
    ;
    break;

  case 7:
    ;
    break;

  }

  return 0;
}

bool Referee::CanPlace(char player, char x, char y) {
  return !board[x][y];
}

bool Referee::UpdateBoard(char x, char y) {

  return false;
}
