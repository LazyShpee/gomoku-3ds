#include "../include/Referee.hpp"

Referee::Referee(char (& board)[19][19]) : board(board) {

}

Referee::~Referee() {

}

char Referee::vision(char *v, char x, char y, char direction, bool lookBack) {
  char vec[1][1];


  return 0;
}

bool Referee::CanPlace(char player, char x, char y) {
  return !board[x][y];
}

bool Referee::UpdateBoard(char x, char y) {

  return false;
}
