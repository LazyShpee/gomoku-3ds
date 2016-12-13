#include "../include/AIMiniMax.hpp"

AIMiniMax::AIMiniMax() : ref(NULL) {

}
AIMiniMax::~AIMiniMax() {}

int AIMiniMax::maxValue(int *result, int lvl) {
  int pos = 0;
  int max = -1;
  for (int i = 0; i < 19 * 19; i++) {
    if (result[i] > max) {
      max = result[i];
      pos = i;
    }
  }
  return pos;
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
        if (ref.CanPlace(player, x, y)) {
	  Board::restoreBoard(new_board, board, 19, 19);
          new_board[x][y].p = player;
	  for (int x2 = 0; x2 < 19; x2++)
	    for (int y2 = 0; y2 < 19; y2++) {
	      if (ref.CanPlace(INVP(player), x2, y2)) {
		Board::restoreBoard(new_board2, new_board, 19, 19);
		new_board2[x2][y2].p = INVP(player);
		if (depth > 0) {
		  t_vec tmp;
		  tmp = MiniMax(new_board2, score, player, depth - 1, lvl);
		  new_board2[tmp.x][tmp.y].p = player;
		  result2[y2 * 19 + x2] = EvalPos(new_board2, tmp.x, tmp.y, score);
		} else result2[y2 * 19 + x2] = 60 - EvalPos(new_board2, x2, y2, score);
	      } else result2[y2 * 19 + x2] = -1;
	    }
	  Board::destroyBoard(new_board2, 19, 19);
	  result[y * 19 + x] = result2[maxValue(result2, lvl)];
        } else result[y * 19 + x] = -1;
      }
  Board::destroyBoard(new_board, 19, 19);
  int ret = maxValue(result, lvl);
  return (t_vec){ret % 19, ret / 19};
}

int AIMiniMax::EvalPos(Board::t_tile **board, int x, int y, int *score) {
  char p = board[x][y].p;
  char e = INVP(p);
  int ret = 0;
  for (int d = 0; d < 4; d++) {
    Board::t_tile *tmp = &board[x][y];
    int size = 1;
    int extrem = 0;
    while (tmp->sides[d] && tmp->sides[d]->p == p) {
      tmp = tmp->sides[d];
      size++;
    }
    extrem = (board[x][y].sides[(d + 4) % 8] && !board[x][y].sides[(d + 4) % 8]->p) + (tmp->sides[d] && !tmp->sides[d]->p);
    tmp = &board[x][y];
    if ((ret < 10 || extrem || size == 5) &&
	(ret < size * 10 + extrem))
      ret = size * 10 + extrem;
    if (tmp->sides[d] && tmp->sides[d]->p == e &&
	tmp->sides[d]->sides[d] && tmp->sides[d]->sides[d]->p == e &&
	tmp->sides[d]->sides[d]->sides[d] && tmp->sides[d]->sides[d]->sides[d]->p == p) {
      int new_ret = (score[(p == 2)] >= 8) ? 60 : 35;
      if (new_ret > ret) ret = new_ret;
    }
  }
  return ret;
}

t_vec AIMiniMax::think(Board::t_tile **board, int *score, int player, int lvl) {
  return MiniMax(board, score, player, 1, (lvl > 10) ? 10 : ((lvl < 1) ? 1 : lvl));
}
