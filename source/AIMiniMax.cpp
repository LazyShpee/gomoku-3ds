#include "../include/AIMiniMax.hpp"

AIMiniMax::AIMiniMax() : ref(NULL) {

}
AIMiniMax::~AIMiniMax() {}

int AIMiniMax::maxValue(int *result, int lvl) {
  int pos = 0;
  int max = -31;
  for (int i = 0; i < 19 * 19; i++) {
    if (result[i] > max) {
      max = result[i];
      pos = i;
    }
  }
  return pos;
}

bool AIMiniMax::somethingAround(Board::t_tile **board, int x, int y) {
  Board::t_tile *tmp = &board[x][y];
  for (int i = 0; i < 8; i++)
    if (tmp->sides[i] && tmp->sides[i]->p) return true;
  return false;
}

t_vec AIMiniMax::MiniMax(Board::t_tile **board, int *score, int player, int depth, int lvl)
{
  int result[19 * 19];
  int result2[19 * 19];
  Board::t_tile **new_board = Board::makeNewBoard(19, 19);
  Board::t_tile **new_board2 = Board::makeNewBoard(19, 19);
  ref.setBoard(new_board);
  for (int x = 0; x < 19; x++)
    for (int y = 0; y < 19; y++) {
      Board::restoreBoard(new_board, board, 19, 19);
      if (somethingAround(board, x, y) && ref.CanPlace(player, x, y)) {
	new_board[x][y].p = player;
	ref.setBoard(new_board2);
	for (int x2 = 0; x2 < 19; x2++)
	  for (int y2 = 0; y2 < 19; y2++) {
	    Board::restoreBoard(new_board2, new_board, 19, 19);
	    if (somethingAround(new_board, x, y) && ref.CanPlace(INVP(player), x2, y2)) {
	      new_board2[x2][y2].p = INVP(player);
	      if (depth > 0) {
		t_vec tmp;
		tmp = MiniMax(new_board2, score, player, depth - 1, lvl);
		new_board2[tmp.x][tmp.y].p = player;
		result2[y2 * 19 + x2] = EvalPos(new_board2, tmp.x, tmp.y, score);
	      } else result2[y2 * 19 + x2] = EvalPos(new_board2, x2, y2, score);
	    } else result2[y2 * 19 + x2] = -1;
	  }
	ref.setBoard(new_board);
	result[y * 19 + x] = result2[maxValue(result2, lvl)];
      } else result[y * 19 + x] = -1;
    }
  Board::destroyBoard(new_board2, 19, 19);
  Board::destroyBoard(new_board, 19, 19);
  int ret = maxValue(result, lvl);
  return (t_vec){ret % 19, (ret / 19) % 19};
}

#define INV(d) ((d + 4) % 8)

#define MAX(a, b) a = ((a) > (b) ? (a) : (b))

#define S_CAPTURE 30
#define S_CAPTURE_WIN 100

#define S_PROTECT 20
#define S_FUTURE_PROTECT 0
#define S_PROTECT_WIN 60

#define S_BLOCK_2 20
#define S_BLOCK_BLANK_3 50
#define S_BLOCK_FULL_3 (S_BLOCK_BLANK_3 + 1)

#define S_SELFCHAIN_BONUS 12

#define S_WIN 1000
#define S_CAN_WIN 45

int AIMiniMax::EvalPos(Board::t_tile **board, int x, int y, int *score) {
    int ret = 0, value = 0;
    int p = board[x][y].p;
    int e = INVP(p);
    bool ABORT = false;

    for (int d = 0; d < 8; d++) {
        value = 0;
        if ((board[x][y].sides[d] && board[x][y].sides[d]->p) ||
            (board[x][y].sides[INV(d)] && board[x][y].sides[INV(d)]->p)) {
            char v[20] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
            int c = 0;
            value = 1;
            Board::t_tile *tmp = &board[x][y];
            int dd = tmp->dist[INV(d)];
            int da = 18 - dd;
            while (tmp && tmp->sides[INV(d)]) tmp = tmp->sides[INV(d)];
            while (tmp) {
                v[c++] = tmp->p;
                tmp = tmp->sides[d];
            }
            if (da >= 4 && v[dd + 1] == e && v[dd + 2] == e && v[dd + 3] == p) MAX(value, (score[p - 1] >= 6 ? S_CAPTURE_WIN : S_CAPTURE));
            if (da >= 3 && v[dd + 1] == p && v[dd + 2] == p && v[dd + 3] == e) MAX(value, (score[e - 1] >= 6 ? S_PROTECT_WIN : S_PROTECT));
            if (dd >= 1 && da >= 2  && v[dd + 1] == e && v[dd + 2] == e && v[dd - 1] == e) MAX(value, S_BLOCK_BLANK_3);
            if (da >= 4 && v[dd + 1] == e && v[dd + 2] == e && v[dd + 3] == e && v[dd + 4] != p) MAX(value, S_BLOCK_FULL_3);

            if (da >= 2 && v[dd + 1] == e && v[dd + 2] == e) MAX(value, S_BLOCK_2);

            if (da >= 2 && v[dd + 1] == p && v[dd + 2] == p) MAX(value, S_SELFCHAIN_BONUS * 1);
            if (da >= 3 && v[dd + 1] == p && v[dd + 2] == p && v[dd + 3] == p) MAX(value, S_SELFCHAIN_BONUS * 2);
            if (da >= 4 && v[dd + 1] == p && v[dd + 2] == p && v[dd + 3] == p && v[dd + 4] == p) MAX(value, ref._WinningPosition(x, y) == 2 ? S_WIN : S_CAN_WIN);
            if (dd >= 1 && da >= 2  && v[dd + 1] == p && v[dd + 2] == p && v[dd - 1] == p) MAX(value, ref._WinningPosition(x, y) == 2 ? S_WIN : S_CAN_WIN);

            if (value < 100 && dd >= 1 && !v[dd - 1] && da >= 2 && v[dd + 1] == p && v[dd + 2] == e) ABORT = true;
        }
        if (value > ret) ret = value;
    }
    return ABORT ? -1000 : ret;
}

t_vec AIMiniMax::think(Board::t_tile **board, int *score, int player, int lvl) {
  return MiniMax(board, score, player, 0, (lvl > 10) ? 10 : ((lvl < 1) ? 1 : lvl));
}
