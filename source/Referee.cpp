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

int Referee::WiningPosition(int x, int y) {
  if (!board[x][y].p)
    return 3;
  int ret = 0;
  int p = board[x][y].p;
  int e = INVP(p);
  for (int d = 0; d < 8; d++) {
    Board::t_tile *tmp = &board[x][y];
    int dx = directions[d][0], dy = directions[d][1];
    int k = 1;
    while (tmp->sides[(d + 4) % 8] && tmp->sides[(d + 4) % 8]->p == p) tmp = tmp->sides[(d + 4) % 8];
    while (tmp->sides[d] && tmp->sides[d]->p == p) {
      tmp = tmp->sides[d];
      k++;
    }
    if (k > 4) {
      ret = 2;
      k = 10 - k;
      if (k < 1) return 2;
      for (int _ = 5 - k; _; _--) tmp = tmp->sides[(d + 4) % 8];
      while (k--) {
	for (int d2 = 0; d2 < 8; d2++) {
	  if (d == d2 || d == (d2 + 4) % 8)
	    continue;
	  if (tmp->sides[d2] && tmp->sides[d2]->p == p &&
	      tmp->sides[d2]->sides[d2] && tmp->sides[d2]->sides[d2]->p != p &&
	      tmp->sides[(d2 + 4) % 8] && tmp->sides[(d2 + 4) % 8]->p != p) {
	    ret = 1;
	    break;
	  }
	}
	tmp = tmp->sides[(d + 4) % 8];
      }
    }
  }
  return ret;
}

bool Referee::Three(char player, int x, int y, int dir) {
  int p = player;
  int e = INVP(p);
  for (int _ = 0; _ < 4; _++) {
    if (board[x][y].p == p)
      for (int d = 0; d < 8; d++) {
	if (d == dir || d == (dir + 4) % 8)
	  continue;
	int dx = directions[d][0], dy = directions[d][1];
	int count_p;
	for (int i = 0; i < 2; i++)
	  if (board[x][y].dist[d] > 3 - i && board[x][y].dist[(d + 4) % 8] > 0 + i &&
	      !board[x - dx * (i + 1)][y - dy * (i + 1)].p &&
	      !board[x + dx * (4 - i)][y + dy * (4 - i)].p) {
	    count_p = 0;
	    for (int d_b = 0 - i; d_b < 4 - i; d_b++) {
	      if (board[x + dx * d_b][y + dy * d_b].p == p) count_p++;
	      if (board[x + dx * d_b][y + dy * d_b].p == e) {
		count_p = 0;
		break;
	      }
	    }
	    if (count_p == 3)
	      return true;
	  }
      }
    x += directions[dir][0];
    y += directions[dir][1];
  }
  return false;
}

bool Referee::DoubleThree(char player, int x, int y) {
  int p = player;
  int e = INVP(p);
  for (int d = 0; d < 8; d++) {
    int dx = directions[d][0], dy = directions[d][1];
    int count_p;
    for (int i = 0; i < 2; i++)
      if (board[x][y].dist[d] > 3 - i && board[x][y].dist[(d + 4) % 8] > 0 + i &&
	  !board[x - dx * (i + 1)][y - dy * (i + 1)].p &&
	  !board[x + dx * (4 - i)][y + dy * (4 - i)].p) {
	count_p = 0;
	for (int d_b = 0 - i; d_b < 4 - i; d_b++) {
	  if (board[x + dx * d_b][y + dy * d_b].p == p) count_p++;
	  if (board[x + dx * d_b][y + dy * d_b].p == e) {
	    count_p = 0;
	    break;
	  }
	}
	if (count_p == 2)
	  if (Three(player, x - i, y - i, d)) return true;
      }
  }
  return false;
}

bool Referee::CanPlace(char player, int x, int y) {
  if (board[x][y].p || DoubleThree(player, x, y)) return false;
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
