#include "../include/AIMiniMax.hpp"

AIMiniMax::AIMiniMax() : ref(NULL) {
  
}
AIMiniMax::~AIMiniMax() {}

t_vec AIMiniMax::maxValue(int *result, int lvl) {
  int pos = -1;
  int max = -1;
  for (int i = 0; i < 19 * 19; i++) {
    if (result[i] > max) {
      max = result[i];
      pos = i;
    }
  }
  return (t_vec){pos % 19, pos / 19};
}

t_vec AIMiniMax::MiniMax(Board::t_tile **board, int *score, int player, int depth, int lvl)
{
  int result[19 * 19];
  if (player == 2) { // max
    for (int x = 0; x < 19; x++)
      for (int y = 0; y < 19; y++) {
	Board::t_tile **new_board = Board::makeNewBoard(board, 19, 19);
	new_board[x][y].p = player;
	ref.setBoard(new_board);
	if (ref.CanPlace(player, x, y)) {
	  t_vec tmp;
	  tmp = MiniMax(new_board, score, INVP(player), depth, lvl);
	  new_board[tmp.x][tmp.y].p = INVP(player);
	  ref.setBoard(new_board);
	  result[y * 19 + x] = EvalPos(new_board, tmp.x, tmp.y, score);
	} else result[y * 19 + x] = -1;
	Board::destroyBoard(new_board, 19, 19);
      }
  } else { // min
    for (int x = 0; x < 19; x++)
      for (int y = 0; y < 19; y++) {
	Board::t_tile **new_board = Board::makeNewBoard(board, 19, 19);
	new_board[x][y].p = player;
	ref.setBoard(new_board);
	if (ref.CanPlace(player, x, y)) {
	  if (depth) {
	    t_vec tmp;
	    tmp = MiniMax(new_board, score, INVP(player), depth - 1, lvl);
	    new_board[tmp.x][tmp.y].p = INVP(player);
	    ref.setBoard(new_board);
	    result[y * 19 + x] = EvalPos(new_board, tmp.x, tmp.y, score);
	  } else result[y * 19 + x] = EvalPos(new_board, x, y, score);
	} else result[y * 19 + x] = -1;
	Board::destroyBoard(new_board, 19, 19);
      }
  }
  return maxValue(result, lvl);
}

int AIMiniMax::EvalPos(Board::t_tile **board, int x, int y, int *score) {
  char p = board[x][y].p;
  char e = INVP(p);
  int ret = 0;
  for (int d = 0; d < 4; d++) {
    Board::t_tile *tmp = &board[x][y];
    int size = 0;
    int extrem = 0;
    while (tmp->sides[d] && tmp->sides[d]->p == p) {
      tmp = tmp->sides[d];
      size++;
    }
    extrem += (!board[x][y].sides[(d + 4) % 8]) + (!tmp->sides[d]);
    tmp = &board[x][y];
    if ((extrem || size == 5) && (ret < size * 10 + extrem))
      ret = size * 10 + extrem;
    if (tmp->sides[d] && tmp->sides[d]->p == e &&
	tmp->sides[d]->sides[d] && tmp->sides[d]->sides[d]->p == e &&
	tmp->sides[d]->sides[d]->sides[d] && tmp->sides[d]->sides[d]->sides[d]->p == p) {
      int new_ret = (score[(p == 1)] >= 8) ? 60 : 35;
      if (new_ret > ret) ret = new_ret;
    }
  }
  return ret;
}

t_vec AIMiniMax::think(Board::t_tile **board, int *score, int player, int lvl) {
  return MiniMax(board, score, player, 1, (lvl > 10) ? 10 : ((lvl < 1) ? 1 : lvl));
}
