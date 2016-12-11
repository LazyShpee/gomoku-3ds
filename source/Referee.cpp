#include "../include/Referee.hpp"

static int directions[8][2] = {
    {-1, -1},
    {0, -1},
    {1, -1},
    {1, 0},
    {1, 1},
    {0, 1},
    {-1, 1},
    {-1, 0}
  };

Referee::Referee(Board::t_tile **board) : board(board) {

}

Referee::~Referee() {

}

char Referee::vision(char *v, int x, int y, int d, bool lookBack) {
  int dir[2] = {directions[d][0], directions[d][1]};
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

bool Referee::UpdateBoard(int x, int y, int *scores) {
  for (int d = 0; d < 8; d++) {
    int dx = directions[d][0], dy = directions[d][1];
    int p = board[x][y].p;
    int e = INVP(p);
    if (board[x][y].dist[d] >= 3) {
      if (board[x + dx][y + dy].p == e && board[x + dx * 2][y + dy * 2].p == e &&
        board[x + dx * 3][y + dy * 3].p == p) {
          board[x + dx][y + dy].p = 0;
          board[x + dx * 2][y + dy * 2].p = 0;
          scores[p - 1] += 2;
        }
    }
  }
  return false;
}
