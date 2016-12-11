#include "../include/Referee.hpp"


static int s_direction[8][2] = { {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0} };

Referee::Referee(Board::t_tile **board) : board(board) {

}

Referee::~Referee() {

}

char Referee::vision(char *v, int x, int y, int direction, bool lookBack) {
  int dir[2] = {s_direction[direction][0], s_direction[direction][1]};
  int pos = 0;
  int t_x = x, t_y = y;

  if (lookBack) {
    while (t_y && t_x && t_y < 18 && t_x < 18) {
      t_y -= dir[1];
      t_x -= dir[0];
    }
    while (t_y != y && t_x != x) {
      *v = (char)board[t_x][t_y].p + 48;
      v++;
      pos++;
      t_y += dir[1];
      t_x += dir[0];
    }
  }
  while (t_y >=0 && t_x >=0 && t_y < 19 && t_x < 19) {
    *v = (char)board[t_x][t_y].p + 48;
    v++;
    t_y += dir[1];
    t_x += dir[0];
  }
  *v = 0;
  return pos;
}

bool Referee::CanPlace(char player, int x, int y) {
  if (board[x][y].p) return false;
  return true;
}

bool Referee::UpdateBoard(int x, int y) {
  //char v[20];

  //vision(v, x, y, true);
  return false;
}
